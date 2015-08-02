#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fitsio.h>
//----------------------------------------------------------------------------------
double *read_from_fits(char *source_fits, long *nsx, long *nsy) {

    fitsfile *fptr_in;
	int status,  nfound, anynull;
    long naxes[2],fpixel,npixels;

    double nullval;
    status = 0;

    fits_open_file(&fptr_in, source_fits, READONLY, &status);
    fits_read_keys_lng(fptr_in, "NAXIS", 1, 2, naxes, &nfound, &status);

	*nsx = naxes[0];
	*nsy = naxes[1];

    npixels  = naxes[0]*naxes[1];
    fpixel   = 1;
    nullval  = 0;

	double *source_map = (double *)calloc(npixels,sizeof(double));
    fits_read_img(fptr_in, TDOUBLE, fpixel, npixels, &nullval,source_map, &anynull, &status);

    fits_close_file(fptr_in, &status);

	return source_map;
}
//----------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    char *input_file = argv[1];
	long nsx = 0;
	long nsy = 0;

	double *source_map;
	source_map = read_from_fits(input_file, &nsx, &nsy);

	double *source_map_str;
	source_map_str = (double *)calloc((nsx*nsy+2),sizeof(double));

	long i,j,index;
	printf("%ld %ld ",nsx,nsy);
	source_map_str[0] = nsx;
	source_map_str[1] = nsx;
	for (i=0;i<nsx;i++)for (j=0;j<nsy;j++) {
		index = i*nsy+j;
		//printf("%ld %ld %lf ",i,j,source_map[index]);
		printf("%lf ",source_map[index]);
	}

    return 0;
}
