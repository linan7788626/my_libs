#/usr/bin/env python
import pylab as pl
import numpy as np
import pyfits
import sys

#def read_fits(fits_ind):
#
#   input_args =" "+str(fits_ind)
#
#   cmd = "./a.out "+input_args
#
#   out_tmp = np.array((sp.check_output(cmd,shell=True)).split(),dtype=np.float64)
#   out_tmp = out_tmp.reshape(len(out_tmp)/3,3)
#   nx = out_tmp[-1,0]
#   ny = out_tmp[-1,1]
#   print nx,ny
#   print len(out_tmp[:,2])
#
#   img = out_tmp[:,2].reshape((int(ny)+1,int(nx)+1))
#
#   return img

import ctypes as ct
rfits = ct.CDLL("./libreadfits.so")
rfits.read_shape_fits.argtypes = [ct.c_char_p]
rfits.read_shape_fits.restype  = ct.POINTER(ct.c_long)

rfits.read_data_fits.argtypes = [ct.c_char_p,ct.c_long,ct.c_long]
rfits.read_data_fits.restype  = ct.POINTER(ct.c_double)

def call_read_fits(fits_in):
    #tmp = rfits.read_fits(fits_in)

    ishape = rfits.read_shape_fits(fits_in)
    fshape = np.ctypeslib.as_array(ishape,(2,))
    print fshape
    nx = fshape[1]
    ny = fshape[0]
    out_tmp = rfits.read_data_fits(fits_in,ct.c_long(nx),ct.c_long(ny))
    arr = np.ctypeslib.as_array(out_tmp,(nx*ny,))

    #print int(fshape[0]*fshape[1])+2
    #print int(arr[0]),int(arr[1])
    #print int(arr[1])*int(arr[0])+2
    #print np.shape(arr)
    re_arr = arr.reshape((nx,ny))
    #img_out = out_tmp[2:].reshape((int(out_tmp[1]),int(out_tmp[0])))
    return re_arr

#import ctypes as ct
#rfits = ct.CDLL("./libreadfits.so")
##rfits.read_fits.argtypes = [ct.c_char_p,ct.POINTER(np.ctypeslib.ndpointer(dtype = ct.c_double))]
##rfits.read_fits.restype  = ct.c_void_p
#
#def call_read_fits(fits_in):
#   out_tmp = ct.POINTER(ct.c_double)()
#   #out_tmp = np.ctypeslib.ndpointer(dtype = ct.c_double)
#   rfits.read_fits(fits_in,ct.byref(out_tmp))
#   out_tmp = np.array(out_tmp)
#   img_out = out_tmp[2:(int(out_tmp[1])*int(out_tmp[0])+2)].reshape((int(out_tmp[1]),int(out_tmp[0])))
#   #img_out = out_tmp[2:].reshape((int(out_tmp[1]),int(out_tmp[0])))
#   return img_out



#from mpi4py import MPI
@profile
def main():

    img1 = call_read_fits(str(sys.argv[1]))
    #print "----------------------------------------"
    #img1 = read_fits(str(sys.argv[1]))
    img2 = pyfits.open(str(sys.argv[1]))[0].data
    #pl.figure()
    #pl.contourf(img1)
    #pl.colorbar()
    #pl.figure()
    #pl.contourf(img2)
    #pl.colorbar()

    #pl.show()
    #cmd = "ls ../gals_in_HUDF/masks/ |grep fits"
    #galaxyFilesToChooseFrom = sp.check_output(cmd,shell=True).split('\n')
    #
    #del galaxyFilesToChooseFrom[-1]
    #NumGalsHUDF = len(galaxyFilesToChooseFrom)
    #
    #for i in xrange(NumGalsHUDF):
    #   img1 = call_read_fits("../gals_in_HUDF/i/"+galaxyFilesToChooseFrom[i])
    #   img2 = pyfits.open("../gals_in_HUDF/i/"+galaxyFilesToChooseFrom[i])[0].data


    return 0
main()
