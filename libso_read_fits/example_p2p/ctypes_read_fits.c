#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fitsio.h>
//----------------------------------------------------------------------------------
double *read_from_fits(char *source_fits) {

	fitsfile *fptr_in;
	int status,  nfound, anynull;
	long naxes[2],fpixel,npixels;

	double nullval;
	status = 0;

	fits_open_file(&fptr_in, source_fits, READONLY, &status);
	fits_read_keys_lng(fptr_in, "NAXIS", 1, 2, naxes, &nfound, &status);

	npixels  = naxes[0]*naxes[1];
	fpixel	 = 1;
	nullval  = 0;

	double *source_map = (double *)calloc(npixels,sizeof(double));
	fits_read_img(fptr_in, TDOUBLE, fpixel, npixels, &nullval,source_map, &anynull, &status);
	fits_close_file(fptr_in, &status);

	double *source_map_struct;
	source_map_struct = (double *)calloc((npixels+2),sizeof(double));

	source_map_struct[0] = (double)naxes[0];
	source_map_struct[1] = (double)naxes[1];

	long i,j,index;
	for (i=0;i<naxes[0];i++)for (j=0;j<naxes[1];j++) {
		index = i*naxes[1]+j;
		source_map_struct[index+2]=source_map[index];
	}
	free(source_map);

	return source_map_struct;
}
