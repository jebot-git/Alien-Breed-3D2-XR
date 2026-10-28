#!/bin/sh
# Asset authoring only; runtime and installation need no ImageMagick.
set -eu
ab2_root=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
ab2_icons="$ab2_root/native/assets/icons"
for ab2_size in 16 24 32 48 64 96 128 256 512 1024; do
 ab2_dest="$ab2_icons/hicolor/${ab2_size}x${ab2_size}/apps"
 mkdir -p "$ab2_dest"
 magick "$ab2_icons/alien-breed3d2-xr-master.png" -filter Lanczos -resize "${ab2_size}x${ab2_size}" -strip "PNG32:$ab2_dest/alien-breed3d2-xr.png"
done
