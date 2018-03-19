#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function#, absolute_import
import numpy
from ctypes import *
import wrapper


class cma(wrapper.wrapper):

    def __init__(self, maxiter, ofunc, initials, sigma, lamb=None, mu=None):
        # initialize wrapper
        super(cma, self).__init__()
        # set attributes
        self.ofunc = ofunc
        self.mu = mu
        self.lamb = lamb
        self.sigma = sigma
        self.maxiter = maxiter
        self.initials = initials
        self.n_var = len(initials)
        return

    def callback(self, length, searchpoint):
        x = numpy.ctypeslib.as_array(searchpoint, (length,))
        return self.ofunc(x)

    def __call__(self):
        # set type of callback function
        CMPFUNC = CFUNCTYPE(c_double, c_int, POINTER(c_double))
        # try to initialize callback function
        callback = CMPFUNC(self.callback)
        # allocate solution array
        solution = numpy.zeros([self.n_var])
        # start the optimizer
        check = self.sharkwrapper.cmaes(callback, self.n_var,
            numpy.ctypeslib.as_ctypes(self.initials), self.maxiter,
            self.mu, self.lamb, c_double(self.sigma),
            numpy.ctypeslib.as_ctypes(solution))
        return solution
