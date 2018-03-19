pyShark
=======

This project trys to provide a Python scripting interface for the CMA-ES and
MOCMA-ES algorithms implemented in the
`SHARK ML library. <http://image.diku.dk/shark/index.html>`_.

Getting Started
---------------

Prequesites
___________

In order to use this wrapper you have to have a working Shark installation.
Please make sure, that Shark is build as shared library. This wrapper has only
been tested with
`Shark release 3.1.4 (). <https://github.com/Shark-ML/Shark/releases/tag/v3.1.4>`_
In addition at least python 2.7 and including numpy and ctypes are needed. If
you want to use the provided example for the MO-CMAES the
`optproblems package <https://pypi.python.org/pypi/optproblems>`_ has to be installed.

Installation
____________

In order to install the code follow the following steps:

.. code-block:: bash

    git clone https://github.com/jduerholt/sharkwrapper.git
    cd sharkwrapper
    mkdir build
    cd build
    cmake "-DShark_DIR=/PATH/TO/SHARK" ../src/.
    make
    cd ../sharkwrapper
    ln -s ../build/libsharkwrapper .

In addition it has to made sure that the sharkwrapper directory is in the PYTHONPATH.

Using the code
--------------
Two examples showing how to use the code are given in the examples subdirectory.

CMA-ES
______

The file ``cma.py`` use CMA-ES to optimize a three dimensional sphere function.
Run the example by the help of the following command:

.. code-block:: bash

    python cma.py

At the end it will print the final solution after 500 iterations.

MO-CMA-ES
_________

The file ``mocma.py`` uses the multi-objective variant of CMA-ES to optimize
the DTLZ2 objecitve function in dimension three using two objectives. The example
can be run by executing te following command:

.. code-block:: bash

    python mocma.py

At the end it will print the solutions after 2500 iterations. In addition a file
calles ``pareto.dat`` is created holding the values of the optimal solutions.
