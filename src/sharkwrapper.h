
#pragma once


// The functions in the following block are our C interface.
// Function names are not subject to C++ name mangling. If we
// restrict the parameters to plain C types, then the functions
// can be called from C, and hence through Python's ctypes
// module.
#ifdef __cplusplus
extern "C" {
#endif


unsigned int do_stuff_with_shark(unsigned int evaluations);
unsigned int cmaes();
double* custom_cmaes(double (*callback)(int, double *), unsigned int dim,
    double *inital, double sigma, int maxiter);


#ifdef __cplusplus
} // extern "C"
#endif
