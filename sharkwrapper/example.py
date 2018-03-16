
import platform
from ctypes import *
import numpy
import math
from numpy.ctypeslib import ndpointer
from optproblems import dtlz


def sphere(length, searchpoint):
    x = numpy.ctypeslib.as_array(searchpoint, (length,))
    return numpy.linalg.norm(x)**2


CMPFUNC = CFUNCTYPE(c_double, c_int, POINTER(c_double))
callback = CMPFUNC(sphere)


#def dtlz2(length, n_objectives, searchpoint, result):
#    x = numpy.ctypeslib.as_array(searchpoint, (length,))
#    y = numpy.ctypeslib.as_array(result, (n_objectives,))
#    k = length - n_objectives
#    g = sum((xi-0.5)**2 for xi in x[n_objectives-1:])
#    for i in range(n_objectives):
#        y[i] = 1.0+g
#        for j in range(n_objectives-i-1):
#            y[i] *= math.cos(0.5*math.pi*x[j])
#        if i > 0:
#            y[i] *= math.sin(0.5*math.pi*x[n_objectives-i-1])
#    return

def test(length, n_objectives, searchpoint):
    y = result = numpy.zeros([n_objectives])
    x = searchpoint
    k = length - n_objectives
    g = sum((xi-0.5)**2 for xi in x[n_objectives-1:])
    for i in range(n_objectives):
        y[i] = 1.0+g
        for j in range(n_objectives-i-1):
            y[i] *= math.cos(0.5*math.pi*x[j])
        if i > 0:
            y[i] *= math.sin(0.5*math.pi*x[n_objectives-i-1])
    return result





def dtlz2(length, n_objectives, searchpoint, result):
    x = numpy.ctypeslib.as_array(searchpoint, (length,))
    y = numpy.ctypeslib.as_array(result, (n_objectives,))
    dt2 = dtlz.DTLZ2(n_objectives, length)
    y[:] = numpy.array(dt2(x))[:]
    #print length, n_objectives, x, y
    return


CMPFUNC2 = CFUNCTYPE(None, c_int, c_int, POINTER(c_double), POINTER(c_double))
callback2 = CMPFUNC2(dtlz2)


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
sharkwrapper.mocmaes.restype = c_int

#n = sharkwrapper.do_stuff_with_shark(2500)
#print("MO-CMA-ES has found " + str(n) + " non-dominated solutions.")
#n = sharkwrapper.cmaes()

#start = numpy.array([5.,5.,5.])
#psol = sharkwrapper.custom_cmaes(callback, 3, numpy.ctypeslib.as_ctypes(start), c_double(0.1), 500)
#solution = numpy.ctypeslib.as_array(psol, (3,))
#print solution

start = numpy.array([.5, .5, .5])
n = sharkwrapper.mocmaes(callback2, 3, 2, numpy.ctypeslib.as_ctypes(start), 25000)
#print n
