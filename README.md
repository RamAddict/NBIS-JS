# NFIQ-JS
Web assembly transpilation of the old NIST-NFIQ project. 

## Clean up with
    make clean -j3

## Generate Build configs with
    emcmake cmake .

## Build with
    emmake make -j4

## Generate wasm and js
emcc *.a -o output.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"