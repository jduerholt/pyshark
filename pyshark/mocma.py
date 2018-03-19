#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, absolute_import
import numpy
from ctypes import *
from .wrapper import wrapper


class mocma(wrapper):
    """
    Class used to perform an optimization using the multi-objective CMA-ES
    algorithm as implemented in the Shark ML library.

    Args:
        mu (int): poulation size
        sigma (float): initial sigma
        maxiter (int): number of maximal iterations/generations
        ofunc (callable): objective function which should be optimized. It has
            to take as argument a 1D numpy array and has to return the fitness as
            float
        initials (numpy.ndarray): numpy array with start value for the optimizer
        n_objectives (int): number of object offered by ofunc


    Keyword Args:
        bounds (list): list with two numpy arrays representing the lower and upper
            bounds, default: [None, None]
    """

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

    def _callback(self, length, n_objectives, searchpoint, result):
        """
        Method passed to the Mocustom class for evaluating the objective
        function. It calls the objective function passed in the init.

        Args:
            length (int): dimension of the searchspace
            n_objectives (int): number of object offered by the objective function
            searchpoint(ctypes.POINTER): Pointer to the searchpoint
            searchpoint(ctypes.POINTER): Pointer the solution array
        """
        x = numpy.ctypeslib.as_array(searchpoint, (length,))
        y = numpy.ctypeslib.as_array(result, (n_objectives,))
        result = numpy.array(self.ofunc(x))
        y[:] = result[:]
        return

    def __call__(self):
        """
        Method to start the optimizer. During the optimization process a file
        called pareto.dat is written.

        Returns:
            numpy.ndarray holding the solutions found by the optimizer
        """
        # set type of callback function
        CMPFUNC = CFUNCTYPE(None, c_int, c_int, POINTER(c_double), POINTER(c_double))
        # try to initialize callback function
        callback = CMPFUNC(self._callback)
        # allocate solutions array
        solutions = numpy.zeros([self.mu*self.n_var])
        # prepare bounds
        if self.bounds[0] is None:
            lbound = None
        else:
            lbound = numpy.ctypeslib.as_ctypes(self.bounds[0])
        if self.bounds[1] is None:
            ubound = None
        else:
            ubound = numpy.ctypeslib.as_ctypes(self.bounds[1])
        # start the optimizer
        check = self.sharkwrapper.mocmaes(callback, self.n_var, self.n_objectives,
            numpy.ctypeslib.as_ctypes(self.initials), self.maxiter,
            lbound, ubound, self.mu, c_double(self.sigma),
            numpy.ctypeslib.as_ctypes(solutions))
        solutions = solutions.reshape(self.mu,self.n_var)
        return solutions
