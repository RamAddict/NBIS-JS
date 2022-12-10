#include <stdio.h>
#include <nfiq.h>
#include <emscripten/emscripten.h>

/***********************************************************************
************************************************************************
#cat: comp_nfiq - Routine computes NFIQ given an input image.
#cat:             This routine uses default statistics for Z-Normalization
#cat:             and default weights for MLP classification.

   Input:
      idata       - grayscale fingerprint image data
      iw          - image pixel width
      ih          - image pixel height
      id          - image pixel depth (should always be 8)
      ippi        - image scan density in pix/inch
                    If scan density is unknown (pass in -1),
                    then default density of 500ppi is used.
   Output:
      onfiq       - resulting NFIQ value
      oconf       - max output class MLP activation
   Return Code:
      Zero        - successful completion
      EMPTY_IMG   - empty image detected (feature vector set to 0's)
      TOO_FEW_MINUTIAE - too few minutiae detected from fingerprint image,
                    indicating poor quality fingerprint
      Negative    - system error
************************************************************************/
EMSCRIPTEN_KEEPALIVE int computeNfiq(unsigned char *idata,
              const int iw, const int ih, const int id, const int ippi)
{
    int *optflag = malloc(sizeof *optflag);
    *optflag = 0;
    int *oComputedNfiq = malloc(sizeof *oComputedNfiq);
    *oComputedNfiq = 0;
    int *oConfidence = malloc(sizeof *oConfidence);
    *oConfidence = 0;
    printf("Called compute NFIQ!\n");
    printf("Received parameters: \n nfiq score: %d \n", *oComputedNfiq);
    printf("confidence: %d \n", *oConfidence);
    printf("image data (size): %d \n", strlen(idata));
    printf("image width: %d \n", iw);
    printf("image height: %d \n", ih);
    printf("image depth: %d \n", id);
    printf("image ppi: %d \n", ippi);
    printf("flags: %d \n", *optflag);

    int ret = comp_nfiq(oComputedNfiq, oConfidence, idata, iw, ih, id, ippi, optflag);

    printf("FINISHED COMPUTING NFIQ!\n");
    printf("Computed NFIQ: %d \n", *oComputedNfiq);
    printf("Confidence: %d \n", *oConfidence);
    printf("Return code: %d \n", ret);
    printf("image data (size): %d \n", strlen(idata));
    printf("image width: %d \n", iw);
    printf("image height: %d \n", ih);
    printf("image depth: %d \n", id);
    printf("image ppi: %d \n", ippi);
    printf("flags: %d \n", *optflag);
    
    free(oComputedNfiq);
    free(oConfidence);
    free(optflag);
    return ret;
}

int main()
{
    printf("Nfiq-js has been loaded!\n");
    return 0;
}
