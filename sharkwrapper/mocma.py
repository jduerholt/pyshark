#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function#, absolute_import
import numpy
from ctypes import *
import wrapper


class mocma(wrapper.wrapper):

    def __init__(self, mu, sigma, maxiter, ofunc, initials, n_objectives, bounds=[None, None]):
        # initialize wrapper
        super(mocma, self).__init__()
        # set attributes
        self.ofunc = ofunc
        self.mu = mu
        self.sigma = sigma
        self.maxiter = maxiter
        self.initials = initials
        self.n_objectives = n_objectives
        self.n_var = len(initials)
        self.bounds = bounds
        return

    def callback(self, length, n_objectives, searchpoint, result):
        x = numpy.ctypeslib.as_array(searchpoint, (length,))
        y = numpy.ctypeslib.as_array(result, (n_objectives,))
        result = numpy.array(self.ofunc(x))
        y[:] = result[:]
        return

    def __call__(self):
        # set type of callback function
        CMPFUNC = CFUNCTYPE(None, c_int, c_int, POINTER(c_double), POINTER(c_double))
        # try to initialize callback function
        callback = CMPFUNC(self.callback)
        # start the optimizer
        n = self.sharkwrapper.mocmaes(callback, self.n_var, self.n_objectives,
            numpy.ctypeslib.as_ctypes(self.initials), 25000,
            numpy.ctypeslib.as_ctypes(self.bounds[0]),
            numpy.ctypeslib.as_ctypes(self.bounds[1]))
        return
