#!/usr/bin/env bash
if ! meson --version; then
    pip3 install meson
    #pip3 install --user meson
    #export PATH=$PATH:~/.local/bin
fi
if [ ! -d subprojects ]; then
    mkdir -p subprojects
    meson wrap install gtest
fi

rm -rf out
meson out
meson test -C out --print-errorlogs
