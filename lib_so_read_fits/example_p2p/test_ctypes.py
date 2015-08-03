#/usr/bin/env python
import pylab as pl
import numpy as np
import pyfits
import sys
import subprocess as sp
import ctypes as ct

rfits = ct.CDLL("./libreadfits.so")
rfits.read_fits.argtypes = [ct.c_char_p,ct.POINTER(ct.POINTER(ct.c_double))]
#rfits.read_fits.restype  = np.ctypeslib.ndpointer(dtype = ct.c_double,shape=(160000,))
rfits.read_fits.restype  = ct.c_void_p

def call_read_fits(fits_in):
	out = ct.POINTER(ct.c_double)()
	rfits.read_fits(fits_in,ct.byref(out))
	sizeofarray = int(out[0]*out[1])+2
	img_out = np.ctypeslib.as_array((ct.c_double * (sizeofarray)).from_address(ct.addressof(out.contents)))
	img_out = img_out[2:(int(img_out[1])*int(img_out[0])+2)].reshape((int(img_out[1]),int(img_out[0])))
	return img_out


#from mpi4py import MPI
@profile
def main():

	fits_in = sys.argv[1]
	out = ct.POINTER(ct.c_double)()
	rfits.read_fits(fits_in,ct.byref(out))
	sizeofarray = int(out[0]*out[1])+2
	img_out = np.ctypeslib.as_array((ct.c_double * (sizeofarray)).from_address(ct.addressof(out.contents)))
	img1 = img_out[2:(int(img_out[1])*int(img_out[0])+2)].reshape((int(img_out[1]),int(img_out[0])))
	#img1 = call_read_fits(str(sys.argv[1]))
	img2 = pyfits.open(fits_in)[0].data
	pl.figure()
	pl.contourf(img1)
	pl.colorbar()
	pl.figure()
	pl.contourf(img2)
	pl.colorbar()

	pl.show()
#	cmd = "ls ../../gals_in_HUDF/masks/ |grep fits"
#	galaxyFilesToChooseFrom = sp.check_output(cmd,shell=True).split('\n')
#
#	del galaxyFilesToChooseFrom[-1]
#	NumGalsHUDF = len(galaxyFilesToChooseFrom)
#
#	for i in xrange(NumGalsHUDF):
#	#for i in xrange(1000):
#		#img1 = call_read_fits("../../gals_in_HUDF/i/"+galaxyFilesToChooseFrom[i])
#
#		fits_in = "../../gals_in_HUDF/i/"+galaxyFilesToChooseFrom[i]
#
#		out = ct.POINTER(ct.c_double)()
#		rfits.read_fits(fits_in,ct.byref(out))
#		sizeofarray = int(out[0]*out[1])+2
#		img_out = np.ctypeslib.as_array((ct.c_double * (sizeofarray)).from_address(ct.addressof(out.contents)))
#		img1 = img_out[2:(int(img_out[1])*int(img_out[0])+2)].reshape((int(img_out[1]),int(img_out[0])))
#		#img2 = pyfits.open(fits_in)[0].data


	return 0
main()
