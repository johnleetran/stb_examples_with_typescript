#!/bin/bash
set -x
set -e

build_type=${1:-Release}
wasm_optimization_level="-g2"
app_name="stb"
if [ "$build_type" = "Debug" ]; then
    echo "<<<<<< ${build_type} <<<<<<"
    wasm_optimization_level="-gseparate-dwarf=${app_name}.debug.wasm"
fi

pushd .
rm -rf build
mkdir -p build
cd build
emcmake cmake -DCMAKE_BUILD_TYPE=${build_type} -DWASM=1 ..
emmake make
em++ ${wasm_optimization_level} libstb-image.a -o ${app_name}.js -embind --bind -lidbfs.js -s ALLOW_MEMORY_GROWTH=1 -s MAXIMUM_MEMORY=4GB -s FORCE_FILESYSTEM=1 -s -s MODULARIZE=1 -s 'EXPORT_NAME="STBModule"' -s EXPORT_ES6=1 -s 'EXTRA_EXPORTED_RUNTIME_METHODS=["FS", "IDBFS"]'
cp ${app_name}.* ../docs
cp ${app_name}.* ../sandbox-typescript/wasm
popd 