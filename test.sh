#!/usr/bin/env bash
if [ ! -d subprojects ]; then
    mkdir -p subprojects
    meson wrap install gtest
fi

rm -rf out
mkdir -p out
compilers="clang++ g++"
for compiler in $compilers; do
    outdir="out/$compiler"
    if [ ! -d "$outdir" ]; then
        CXX=$compiler \
        meson $outdir
    fi
    meson test -C $outdir --print-errorlogs
done
