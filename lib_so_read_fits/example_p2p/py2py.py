import numpy as np
from ctypes import CDLL, POINTER, c_int, byref
import ctypes as ct

dll = ct.CDLL('./libp2p.so')

data1 = ct.POINTER(ct.c_int)()
data2 = ct.POINTER(ct.c_int)()
out = ct.POINTER(ct.c_int)()

dll.test(ct.byref(data1), ct.byref(data2))

dll.return_m(ct.byref(out))

sizeofarray = data1[0]+1

print sizeofarray
#print data1[5], data2[1]
#print data1.contents, data2[1]
print np.ctypeslib.as_array((ct.c_int * (sizeofarray)).from_address(ct.addressof(data1.contents)))
sizeofarray = out[0]+1
print sizeofarray
#print data1[5], data2[1]
#print data1.contents, data2[1]
print np.ctypeslib.as_array((ct.c_int * (sizeofarray)).from_address(ct.addressof(out.contents)))
