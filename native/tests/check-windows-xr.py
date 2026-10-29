#!/usr/bin/env python3
"""Exercise a fresh Windows ZIP in Wine/WGL with a test-only OpenXR DLL.

Requires Wine and Xvfb. The mock replaces the loader only in the extracted test
copy; no system runtime, user Wine prefix or physical headset is used.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import zipfile

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--archive', type=Path, required=True)
p.add_argument('--mock', type=Path, required=True)
p.add_argument('--previous', type=Path, help='Optional earlier ZIP: reproduce its maximum-version rejection')
p.add_argument('--output', type=Path, required=True)
a = p.parse_args()
a.output.mkdir(parents=True, exist_ok=False)
a.output = a.output.resolve()
read, write = os.pipe()
with (a.output / 'xvfb.log').open('w') as log:
    server = subprocess.Popen(['Xvfb', '-displayfd', str(write), '-screen', '0',
                               '1600x1000x24', '-nolisten', 'tcp', '-noreset'],
                              pass_fds=(write,), stdout=log, stderr=log)
os.close(write)
with os.fdopen(read) as pipe:
    number = pipe.readline().strip()
assert number, 'Xvfb failed'
env = dict(os.environ, DISPLAY=':' + number, WINEPREFIX=str(a.output / 'wine'),
           WINEARCH='win64', WINEDEBUG='-all', SDL_AUDIODRIVER='dummy',
           LIBGL_ALWAYS_SOFTWARE='1',
           WINEDLLOVERRIDES='mscoree,mshtml=;libstdc++-6,libgcc_s_seh-1,libwinpthread-1,libopenxr_loader=n')
for key in ('WAYLAND_DISPLAY', 'WAYLAND_SOCKET', 'LD_PRELOAD', 'LD_LIBRARY_PATH',
            'SDL_VIDEODRIVER', 'XR_RUNTIME_JSON', 'MESA_GL_VERSION_OVERRIDE',
            'DE_XR_TEST_GL_MIN', 'DE_XR_TEST_GL_MAX', 'DE_XR_TEST_PREPARE_GL'):
    env.pop(key, None)
results = []


def extract(archive, name):
    folder = a.output / name
    with zipfile.ZipFile(archive) as z:
        z.extractall(folder)
    return folder / 'bin'


def run(folder, name, mode, extra, expected=0, diagnostic=None):
    report = folder / (name + '.json')
    assert not report.exists()
    args = ['wine', str(folder / 'alien-breed3d2-xr.exe'), mode,
            '--test-play', '--frames', '60', '--report', report.name]
    result = subprocess.run(args, cwd=folder, env=dict(env, **extra),
                            capture_output=True, text=True, timeout=90)
    text = result.stdout + result.stderr
    (a.output / (name + '.log')).write_text(text)
    assert result.returncode == expected, (name, result.returncode, text)
    if diagnostic:
        assert diagnostic in text, (name, text)
    record = dict(case=name, exit_code=result.returncode, passed=True)
    if expected == 0:
        data = json.loads(report.read_text())
        assert data['frames'] == 60 and data['missing_assets'] == 0, data
        assert data['audio_queue_failures'] == 0, data
        if mode == '--xr':
            assert data['xr'] and data['eye_frames'] == 120, data
        else:
            assert not data['xr'], data
            assert 'Requesting OpenGL 3.3 core context' in text, text
        record.update(frames=data['frames'], eye_frames=data['eye_frames'])
    results.append(record)
    print('PASS', name, flush=True)


try:
    subprocess.run(['wineboot', '-u'], env=env, stdout=subprocess.DEVNULL,
                   stderr=subprocess.DEVNULL, timeout=90, check=True)
    folder = extract(a.archive, 'current')
    # First exercise the actual packaged loader in desktop mode with no runtime.
    run(folder, 'desktop-packaged-loader', '--desktop', {})
    shutil.copy2(a.mock, folder / 'libopenxr_loader.dll')
    run(folder, 'xr-baseline', '--xr', {'DE_XR_TEST_PREPARE_GL': '1'})
    run(folder, 'xr-runtime-minimum', '--xr',
        {'DE_XR_TEST_PREPARE_GL': '1', 'DE_XR_TEST_GL_MIN': '4.5'},
        diagnostic='Requesting OpenGL 4.5 core context')
    run(folder, 'xr-newer-compatible', '--xr',
        {'DE_XR_TEST_PREPARE_GL': '1', 'DE_XR_TEST_GL_MAX': '3.3'},
        diagnostic='trying the compatible context')
    run(folder, 'xr-unavailable-context', '--xr',
        {'DE_XR_TEST_PREPARE_GL': '1', 'DE_XR_TEST_GL_MIN': '9.9',
         'DE_XR_TEST_GL_MAX': '9.9'}, expected=1,
        diagnostic='Cannot create OpenGL 9.9')
    if a.previous:
        old = extract(a.previous, 'previous')
        shutil.copy2(a.mock, old / 'libopenxr_loader.dll')
        run(old, 'previous-version-rejection', '--xr',
            {'DE_XR_TEST_GL_MAX': '3.3'}, expected=1,
            diagnostic="OpenGL version is outside the OpenXR runtime's supported range")
finally:
    subprocess.run(['wineserver', '-k'], env=env, stdout=subprocess.DEVNULL,
                   stderr=subprocess.DEVNULL)
    server.terminate()
    server.wait(timeout=5)
(a.output / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
