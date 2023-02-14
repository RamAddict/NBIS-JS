// @ts-ignore
import loadWasm from "../../build/output.mjs";

interface NbisModule extends EmscriptenModule {
    ccall: typeof ccall;
    getValue: typeof getValue;
};

let emscriptenModule: NbisModule;

/**
 * Matching threshold used by Bozorth in finger duplication checking.
 * To increase likeliness of match, decrease this number.
 * To decrease matching results, increase this number.
 * @default 40
 */
export let BOZORTH_MATCH_THRESHOLD = 40;

// Write this on your cjs file to be able to use this lib in node
// import { fileURLToPath } from "url";
// import { dirname } from "path";
// globalThis.__dirname = dirname(fileURLToPath(import.meta.url));

async function getWasmModule() {
    if (!emscriptenModule) {
        emscriptenModule = await loadWasm();
    }
    return emscriptenModule;
}

/**
 * Returns wether 2 fingers are a match.
 * @param finger1 wsq base64
 * @param finger2 wsq base64
 * @returns wether the fingers match
 */
export async function checkDuplicateFingerFromBase64(
    finger1: string,
    finger2: string
): Promise<boolean> {
    // convert to from base64 to char*
    const data1 = Uint8Array.from(atob(finger1), (c) => c.charCodeAt(0));
    const data2 = Uint8Array.from(atob(finger2), (c) => c.charCodeAt(0));
    const module = await getWasmModule();
    let matchScorePointer = module._malloc(4);

    const response = module.ccall(
        "checkDuplicateFinger",
        "number",
        ["array", "number", "array", "number", "number"],
        [data1, data1.byteLength, data2, data2.byteLength, matchScorePointer]
    );

    const matchScore = module.getValue(matchScorePointer, "i32");
    module._free(matchScorePointer);

    if (response !== 0) {
        throw new Error(
            `Wasm Wrapper: Received error code ${response} from emscripten`
        );
    }
    if (matchScore >= BOZORTH_MATCH_THRESHOLD) {
        // Match!
        return true;
    }
    return false;
}

/**
 * Calculates the nfiq quality of a fingerprint.
 * @param finger wsq base64
 * @param type finger file type (only `WSQ` supported for now)
 * @returns the score
 */
export async function getNfiqScoreFromBase64(
    finger: string, type: "WSQ"
): Promise<number> {
    // convert to from base64 to char*
    const module = await getWasmModule();
    const data = Uint8Array.from(atob(finger), (c) => c.charCodeAt(0));

    const nfiqPointer = module._malloc(4);
    const response = module.ccall(
      "computeNfiq",
      "number",
      ["array", "number", "string", "number"],
      [data, data.byteLength, type, nfiqPointer]
    );
    const nfiqResult = module.getValue(nfiqPointer, "i32");
    module._free(nfiqPointer);

    if (response !== 0) {
        throw new Error(
            `Wasm Wrapper: Received error code ${response} from emscripten`
        );
    }
    
    return nfiqResult;
}
