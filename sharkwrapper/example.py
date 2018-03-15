
import platform
from ctypes import *
import numpy
from numpy.ctypeslib import ndpointer


def sphere(length, searchpoint):
    x = numpy.ctypeslib.as_array(searchpoint, (length,))
    return numpy.linalg.norm(x)**2


CMPFUNC = CFUNCTYPE(c_double, c_int, POINTER(c_double))
callback = CMPFUNC(sphere)


dllname = ""
if platform.system() == "Windows":
    dllname = "./libsharkwrapper.dll"
elif platform.system() == "Linux":
    dllname = "./libsharkwrapper.so"
elif platform.system() == "Darwin":
    dllname = "./libsharkwrapper.dylib"
else:
    sys.exit("unknown platform")

sharkwrapper = CDLL(dllname)
sharkwrapper.do_stuff_with_shark.restype = c_int
sharkwrapper.custom_cmaes.restype = POINTER(c_double)

#n = sharkwrapper.do_stuff_with_shark(500)
#print("MO-CMA-ES has found " + str(n) + " non-dominated solutions.")
#n = sharkwrapper.cmaes()
start = numpy.array([5.,5.,5.])
psol = sharkwrapper.custom_cmaes(callback, 3, numpy.ctypeslib.as_ctypes(start), c_double(0.1), 500)
solution = numpy.ctypeslib.as_array(psol, (3,))

print solution
