/*******************************************************************************

License: 
This software and/or related materials was developed at the National Institute
of Standards and Technology (NIST) by employees of the Federal Government
in the course of their official duties. Pursuant to title 17 Section 105
of the United States Code, this software is not subject to copyright
protection and is in the public domain. 

This software and/or related materials have been determined to be not subject
to the EAR (see Part 734.3 of the EAR for exact details) because it is
a publicly available technology and software, and is freely distributed
to any interested party with no licensing requirements.  Therefore, it is 
permissible to distribute this software as a free download from the internet.

Disclaimer: 
This software and/or related materials was developed to promote biometric
standards and biometric technology testing for the Federal Government
in accordance with the USA PATRIOT Act and the Enhanced Border Security
and Visa Entry Reform Act. Specific hardware and software products identified
in this software were used in order to perform the software development.
In no case does such identification imply recommendation or endorsement
by the National Institute of Standards and Technology, nor does it imply that
the products and equipment identified are necessarily the best available
for the purpose.

This software and/or related materials are provided "AS-IS" without warranty
of any kind including NO WARRANTY OF PERFORMANCE, MERCHANTABILITY,
NO WARRANTY OF NON-INFRINGEMENT OF ANY 3RD PARTY INTELLECTUAL PROPERTY
or FITNESS FOR A PARTICULAR PURPOSE or for any purpose whatsoever, for the
licensed product, however used. In no event shall NIST be liable for any
damages and/or costs, including but not limited to incidental or consequential
damages of any kind, including economic damage or injury to property and lost
profits, regardless of whether NIST shall be advised, have reason to know,
or in fact shall know of the possibility.

By using this software, you agree to bear all risk relating to quality,
use and performance of the software and/or related materials.  You agree
to hold the Government harmless from any claim arising from your use
of the software.

*******************************************************************************/


/*
* ======================================================================
* NIST Guide to Available Math Software.
* Source for module SDOT.C from package CBLAS.
* Retrieved from NETLIB on Tue Mar 14 10:55:27 2000.
* ======================================================================
*/

/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include <f2c.h>

doublereal sdot_(int *n, real *sx, int *incx, real *sy, int *incy)
{


    /* System generated locals */
    int i__1;
    real ret_val;

    /* Local variables */
    static int i, m;
    static real stemp;
    static int ix, iy, mp1;


/*     forms the dot product of two vectors.   
       uses unrolled loops for increments equal to one.   
       jack dongarra, linpack, 3/11/78.   
       modified 12/3/93, array(1) declarations changed to array(*)   


    
   Parameter adjustments   
       Function Body */
#define SY(I) sy[(I)-1]
#define SX(I) sx[(I)-1]


    stemp = 0.f;
    ret_val = 0.f;
    if (*n <= 0) {
	return ret_val;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        code for unequal increments or equal increments   
            not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i = 1; i <= *n; ++i) {
	stemp += SX(ix) * SY(iy);
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    ret_val = stemp;
    return ret_val;

/*        code for both increments equal to 1   


          clean-up loop */

L20:
    m = *n % 5;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i = 1; i <= m; ++i) {
	stemp += SX(i) * SY(i);
/* L30: */
    }
    if (*n < 5) {
	goto L60;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i = mp1; i <= *n; i += 5) {
	stemp = stemp + SX(i) * SY(i) + SX(i + 1) * SY(i + 1) + SX(i + 2) * 
		SY(i + 2) + SX(i + 3) * SY(i + 3) + SX(i + 4) * SY(i + 4);
/* L50: */
    }
L60:
    ret_val = stemp;
    return ret_val;
} /* sdot_ */

