#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import print_function, absolute_import
import numpy
from ctypes import *
from .wrapper import wrapper


class cma(wrapper):
    """
    Class used to perform an optimization using the single objective CMA-ES
    algorithm as implemented in the Shark ML library.

    Args:
        maxiter (int): number of maximal iterations/generations
        ofunc (callable): objective function which should be optimized. It has
            to take as argument a 1D numpy array and has to return the fitness as
            float
        initials (numpy.ndarray): numpy array with start value for the optimizer
        sigma (float): initial sigma

    Keyword Args:
        lamb (int): Populations size, if None is given the optimizer is choosing
        the poulation size by itself, default: None
        mu (int): Number of individuals taken into account for creating the
        offspring, default: None
    """

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

    def _callback(self, length, searchpoint):
        """
        Method passed to the Socustom class for evaluating the objective
        function. It calls the objective function passed in the init.

        Args:
            length (int): dimension of the searchspace
            searchpoint(ctypes.POINTER): Pointer to the searchpoint

        Returns:
            fitness as float
        """
        x = numpy.ctypeslib.as_array(searchpoint, (length,))
        return self.ofunc(x)

    def __call__(self):
        """
        Method to start the optimizer.

        Returns:
            numpy.ndarray holding the solution found by the optimizer
        """
        # set type of callback function
        CMPFUNC = CFUNCTYPE(c_double, c_int, POINTER(c_double))
        # try to initialize callback function
        callback = CMPFUNC(self._callback)
        # allocate solution array
        solution = numpy.zeros([self.n_var])
        # start the optimizer
        check = self.sharkwrapper.cmaes(callback, self.n_var,
            numpy.ctypeslib.as_ctypes(self.initials), self.maxiter,
            self.mu, self.lamb, c_double(self.sigma),
            numpy.ctypeslib.as_ctypes(solution))
        return solution
