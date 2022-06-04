#!/bin/bash

set -uex

rm -rf dist
npm install
tsc
cp ./wasm/*.wasm ./dist/wasm/
echo "Done."