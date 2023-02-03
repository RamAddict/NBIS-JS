# **NBIS-JS**

Web assembly transpilation of some functions from the old NIST-NBIS project. Currently the functions we implemented are finger Matching, with Mindtct and Bozorth, and NFIQ 1.0 score.

## **Building**

You will need the [emscripten compiler and associated tools](https://emscripten.org/docs/getting_started/downloads.html).

### Generate Build configs with

    mkdir build; cd build
    emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

### Build with

    emmake make -j16

### Generate wasm and mjs

    emcc *.a  -O3 -o output.mjs -sEXPORT_ES6=1 -sMODULARIZE=1 -sEXPORT_NAME=loadWasm -sINITIAL_MEMORY=128MB -sALLOW_MEMORY_GROWTH -sNO_EXIT_RUNTIME=1 -s"EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'getValue']" -s"EXPORTED_FUNCTIONS=['_free', '_main', '_computeNfiq', '_checkDuplicateFinger', '_malloc']" -sSINGLE_FILE

### Clean up with

    emmake make clean -j3

### Generate nfiq-js lib (you can use npm also)

    cd nbis-js
    pnpm i
    pnpm run build
    pnpm run copy-to-examples # copy .js from dist to /examples

The dist folder should now have the ES6 browser-compatible js library named nbis-js.js.

## Examples

To run the examples, you will need to move the generated nbis-js to the examples directory then run vscode live-server or whihchever other web hosting service to your liking.

### Useful Flags

If you would like to link with the file system and be able to reference files, generate the web assembly files with `-lnodefs.js -lnoderawfs.js`

You may also run the memory profiler by passing `--memoryprofiler`

Running with `-sASSERTIONS` enables more debugging logs

For more information please refer to the emscripten docs.
