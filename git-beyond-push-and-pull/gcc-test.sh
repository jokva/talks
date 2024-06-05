#!/bin/bash

set -euo pipefail

red='\033[0;31m'
green='\033[0;32m'
nc='\033[0m'

bisectdir=bisect-$(git rev-parse HEAD)

if [ ! -d "$bisectdir" ]; then
    mkdir -p $bisectdir
    pushd $bisectdir
    ../configure --enable-languages=c,c++ --disable-libsanitizer --disable-bootstrap --disable-multilib
    make -j$(nproc) > /dev/null
    popd
fi

pushd $bisectdir
set +e
make -k check-gcc RUNTESTFLAGS="analyzer.exp=g++.dg/analyzer/pr100244.C" | grep "unexpected failures"
if [ $? -eq 0 ]; then
    printf "$red$bisectdir is bad$nc\n"
    exit 1
fi

printf "$green$bisectdir is good$nc\n"
