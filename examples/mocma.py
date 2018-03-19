#!/usr/bin/env python
# -*- coding: utf-8 -*-
# optproblems needs do be installed for this example
import numpy
from pyshark import mocma
from optproblems import dtlz

# setup objective function
dt2 = dtlz.DTLZ2(2, 3)
initials = numpy.array([.5, .5, .5])
# setup mocmaes
bounds = [numpy.zeros([3]), numpy.ones([3])]
opt = mocma(mu=100, sigma=0.1, maxiter=2500, ofunc=dt2.__call__,
    initials=initials, n_objectives=2, bounds=bounds)
# run
solution = opt()
print solution
