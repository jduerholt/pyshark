#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy
from sharkwrapper import cma


# objective function
def sphere(x):
    return numpy.linalg.norm(x)**2


# setup cmaes
initials = numpy.array([60.0, -15.0, 37.0])
opt = cma(maxiter=50, ofunc=sphere, initials=initials, sigma=0.5, lamb=5, mu=2)
# run
solution = opt()
print solution
