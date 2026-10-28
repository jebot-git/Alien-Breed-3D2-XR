#!/bin/sh
# Run the build, tests and staged verification as the regular user first.
set -eu
[ "$(id -u)" -eq 0 ] || { echo 'Run only this installation step with sudo -A.' >&2; exit 1; }
ab2_build=${1:?Usage: install-system.sh RELEASE_BUILD_DIRECTORY}
[ -f "$ab2_build/CMakeCache.txt" ] || { echo 'Missing configured build.' >&2; exit 1; }
[ "$(sed -n 's/^CMAKE_BUILD_TYPE:STRING=//p' "$ab2_build/CMakeCache.txt")" = Release ] || { echo 'Release build required.' >&2; exit 1; }
umask 022
cmake --install "$ab2_build"
ab2_prefix=$(sed -n 's/^CMAKE_INSTALL_PREFIX:PATH=//p' "$ab2_build/CMakeCache.txt")
if command -v update-desktop-database >/dev/null 2>&1; then update-desktop-database "$ab2_prefix/share/applications"; fi
if command -v gtk-update-icon-cache >/dev/null 2>&1; then gtk-update-icon-cache --force --ignore-theme-index "$ab2_prefix/share/icons/hicolor"; fi
