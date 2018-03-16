#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import *


class wrapper(object):

    def __init__(self):
        # try to import dll and setup the ObjectiveFunctions
        self.sharkwrapper = CDLL("./libsharkwrapper.so")
        self.sharkwrapper.custom_cmaes.restype = POINTER(c_double)
        self.sharkwrapper.mocmaes.restype = POINTER(c_double)
        return
