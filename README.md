# NFIQ-JS
Web assembly transpilation of the old NIST-NFIQ project. 

You will need the emscripten compiler and associated tools.
## Clean up with
    emmake make clean -j3

## Generate Build configs with
    cd build
    emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

## Build with
    emmake make -j16

## Generate wasm and js
    emcc *.a -O3 -o output.mjs -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'getValue']" -s"EXPORTED_FUNCTIONS=['_free', '_main', '_computeNfiq', '_checkDuplicateFinger']" -sSINGLE_FILE ; mv ./output.mjs ../html/