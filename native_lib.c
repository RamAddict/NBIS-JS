#include <stdio.h>
#include <nfiq.h>
#include <emscripten/emscripten.h>

EMSCRIPTEN_KEEPALIVE int computeNfiq() {
    int computedNfiq = -2;
    float oConfig = 1;
    int optFlag = 1;
    printf("Hello!\n");
    int ret = comp_nfiq(&computedNfiq, &oConfig, NULL, (int) 231, (int) 231, 8, -1, &optFlag);
    printf("%d\n", computedNfiq);
    printf("%d\n", oConfig);
    return ret;
}


int main() {
    int status = computeNfiq();
    printf("Status code: %d\n ", status);
    return 0;
}

