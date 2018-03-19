#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import *
import os


class wrapper(object):
    """
    Base class used for wrapping shark with ctypes. It reads libsharkwrapper.so
    and sets the returntypes for the wrapped cmaes and wrapped mocmaes.
    """

    def __init__(self):
        # try to import dll and setup the ObjectiveFunctions
        self.sharkwrapper = CDLL(os.path.join(os.path.dirname(__file__),
            "libsharkwrapper.so"))
        self.sharkwrapper.cmaes.restype = c_int
        self.sharkwrapper.mocmaes.restype = c_int
        return
