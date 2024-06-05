#!/usr/bin/env bash

set -euo pipefail

ref=bisect-$(git rev-parse HEAD)
buildd=build-$ref

cmake -S . -B $buildd \
    -DBUILD_PYTHON=OFF \
    -DBUILD_TESTING=ON
cmake --build $buildd --parallel
cd $buildd
ctest --output-on-failure
