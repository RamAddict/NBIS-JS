#include <stdio.h>
#include <stdarg.h>
#include <nfiq.h>
#include <wsq.h>
#include <bozorth.h>

const int BOZORTH_THRESHOLD = 40;

int max_minutiae = DEFAULT_BOZORTH_MINUTIAE;
int min_computable_minutiae = MIN_COMPUTABLE_BOZORTH_MINUTIAE;

FILE *errorfp = FPNULL;

int m1_xyt = 0;
int verbose_main = 0;
int verbose_load = 0;
int verbose_bozorth = 0;
int verbose_threshold = 0;
void debugf(const char *str, ...);

/**
 *  List of improvements that can be done to this script:
 *  - NFIQ:
 *    - Allow JPEG, NIST, and other file types
 *  - BOZORTH + MINDTCT:
 *    - The best optimization would be to export the xyt files directly to
 *      bozorth, which would require the implementation of a specific loader.
 *      That way we wouldn't need to link with RAWFS, or read and write to 'files'.
 *    - Add support for a list of fingers (gallery)
 *    - Support for other file types
 *    - Call the specific function to generate just the xyt
 */

/**
 * Calculates the nfiq of an image
 * @param inputImg Takes the input image bytes (binary)
 * @param bufferLength the size of the byteArray
 * @param fileType The type of the file (for now only wsq)
 * @param ouputNfiq The resulting nfiq
 * @return The error code if there is one, 0 otherwise
 */
int computeNfiq(char *inputImg, int bufferLength, const char *fileType, int *ouputNfiq)
{
   unsigned char *decodedOutput;
   int ret, optflag, oComputedNfiq;
   float *oConfidence;
   int w, h, d, ppi, lossyflag, intrlvflag = 0, n_cmpnts;

   debugf("Called compute NFIQ!\n");
   debugf("Received parameters: \n nfiq score: %d \n", oComputedNfiq);
   debugf("image data (size): %d \n", bufferLength);
   debugf("file type: %s \n", fileType);

   // before computing nfiq, we must run the read utilty

   debugf("Running wsq decode mem !\n");

   if (strcmp("WSQ", fileType) == 0 || !fileType)
   {
      if ((ret = wsq_decode_mem(&decodedOutput, &w, &h, &d, &ppi, &lossyflag,
                                inputImg, bufferLength)))
      {
         debugf("ERROR \n");
         return (ret);
      }
   }
   else
   {
      // TODO: implement jpeg file support
      // if ((ret = jpegl_decode_mem(&decodedOutput, &w, &h, &d, &ppi, &lossyflag,
      //                         inputImg, bufferLength)))
      // {
      //    debugf("ERROR \n");
      //    return (ret);
      // }
      debugf("ERROR JPEG UNIMPLEMENTED\n");
      return (1);
   }
   debugf("found following stats about image: \n");
   debugf("image width: %d \n", w);
   debugf("image height: %d \n", h);
   debugf("image depth: %d \n", d);
   debugf("image ppi: %d \n", ppi);
   debugf("flags: %d \n", optflag);

   debugf("computing nfiq!: \n");
   if ((ret = comp_nfiq(&oComputedNfiq, oConfidence, decodedOutput, w, h, d, ppi, &optflag)))
   {
      debugf("ERROR \n");
      return (ret);
   }

   debugf("FINISHED COMPUTING NFIQ!\n");
   debugf("Resulting NFIQ: %d \n", oComputedNfiq);
   debugf("Confidence: %f \n", *oConfidence);
   debugf("Return code: %d \n", ret);

   free(decodedOutput);

   *ouputNfiq = oComputedNfiq;
   return ret;
}

// files should be wsq for now
int checkDuplicateFinger(char *inputImg1, int bufferLength1, char *inputImg2, int bufferLength2, int *ouputNfiq)
{
   debugf("checkDuplicateFinger!\n");
   // first of all we have to decode the images
   unsigned char *decodedOutput1, *decodedOutput2;
   int ret, optflag;
   float *oConfidence;
   int w1, h1, d1, ppi1, lossyflag1, intrlvflag1 = 0, n_cmpnts1;
   int w2, h2, d2, ppi2, lossyflag2, intrlvflag2 = 0, n_cmpnts2;

   if ((ret = wsq_decode_mem(&decodedOutput1, &w1, &h1, &d1, &ppi1, &lossyflag1,
                             inputImg1, bufferLength1)))
   {
      debugf("ERROR Img1\n");
      return (ret);
   }
   if ((ret = wsq_decode_mem(&decodedOutput2, &w2, &h2, &d2, &ppi2, &lossyflag2,
                             inputImg2, bufferLength2)))
   {
      debugf("ERROR Img2\n");
      return (ret);
   }
   debugf("Decoded both successfully!\n");
   // then we have to compute the fingerprint minutiae files
   MINUTIAE *minutiae1, *minutiae2;
   int *direction_map, *low_contrast_map, *low_flow_map;
   int *high_curve_map, *quality_map;
   int map_w, map_h;
   unsigned char *bdata;
   // xyt files struct
   struct xyt_struct *pstruct = XYT_NULL;
   struct xyt_struct *gstruct = XYT_NULL;
   // output width hight and depth of binarized img
   int bw, bh, bd;
   // scan resolution (in pixels/mm) of the grayscale image
   double ippmm;
   // the resulting score
   int match_score;

   if (ppi1 == UNDEFINED)
      ippmm = DEFAULT_PPI / (double)MM_PER_INCH;
   else
      ippmm = ppi1 / (double)MM_PER_INCH;
   // calculate minutiae map
   if ((ret = (get_minutiae(&minutiae1, &quality_map, &direction_map,
                            &low_contrast_map, &low_flow_map, &high_curve_map,
                            &map_w, &map_h, &bdata, &bw, &bh, &bd,
                            decodedOutput1, w1, h1, d1, ippmm, &lfsparms_V2))))
   {
      exit(ret);
   }
   free(direction_map);
   free(low_contrast_map);
   free(low_flow_map);
   free(high_curve_map);
   free(quality_map);

   free(decodedOutput1);
   debugf("Got minutiae1!\n");

   const char *finger1OutputFile = "finger1.xyt";
   // write results to vfs
   if ((ret = (write_minutiae_XYTQ(finger1OutputFile, NIST_INTERNAL_XYT_REP,
                                   minutiae1, bw, bh))))
   {
      return (ret);
   }

   debugf("Wrote to file1!\n");

   if (ppi2 == UNDEFINED)
      ippmm = DEFAULT_PPI / (double)MM_PER_INCH;
   else
      ippmm = ppi2 / (double)MM_PER_INCH;

   // calculate minutiae map
   // we overwrite the quality_map, direction map and everything else except the minutiae
   if ((ret = (get_minutiae(&minutiae2, &quality_map, &direction_map,
                            &low_contrast_map, &low_flow_map, &high_curve_map,
                            &map_w, &map_h, &bdata, &bw, &bh, &bd,
                            decodedOutput2, w2, h2, d2, ippmm, &lfsparms_V2))))
   {
      exit(ret);
   }
   free(direction_map);
   free(low_contrast_map);
   free(low_flow_map);
   free(high_curve_map);
   free(quality_map);
   free(decodedOutput2);
   debugf("Got minutiae2!\n");

   const char *finger2OutputFile = "finger2.xyt";
   // write results to vfs
   if ((ret = (write_minutiae_XYTQ(finger2OutputFile, NIST_INTERNAL_XYT_REP,
                                   minutiae2, bw, bh))))
   {
      return (ret);
   }
   debugf("Wrote to file2!\n");

   // read them back to bozorth
   pstruct = bz_load(finger1OutputFile);
   if (pstruct == XYT_NULL)
   {
      debugf("failed to open file 1\n");
      return 1;
   }
   debugf("loaded file1 back to bozorth!\n");
   gstruct = bz_load(finger2OutputFile);
   if (gstruct == XYT_NULL)
   {
      debugf("failed to open file 2\n");
      return 1;
   }
   debugf("loaded file2 back to bozorth!\n");
   // finally run the bozorth algorithm
   int n = bozorth_main(pstruct, gstruct);

   debugf("SCORE: %d \n", n);
   if (n > BOZORTH_THRESHOLD)
   {
      debugf("MATCH!\n");
   }
   else
   {
      debugf("NO MATCH\n");
   }
   // clean up
   if ((remove(finger1OutputFile)) == 0)
   {
      debugf("file1 removed! \n");
   }
   if ((remove(finger2OutputFile)) == 0)
   {
      debugf("file2 removed! \n");
   }
   free(pstruct);
   free(gstruct);
   *ouputNfiq = n;
   return ret; 
}

void debugf(const char *str, ...)
{
#ifndef NDEBUG
   va_list ap;
   va_start(ap, str);
   vprintf(str, ap);
   va_end(ap);
#endif // !NDEBUG
}

int main()
{
   debugf("NFIQ WASM loaded!\n");
   return 0;
}
