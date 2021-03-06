
#pragma once


// The functions in the following block are our C interface.
// Function names are not subject to C++ name mangling. If we
// restrict the parameters to plain C types, then the functions
// can be called from C, and hence through Python's ctypes
// module.
#ifdef __cplusplus
extern "C" {
#endif


int cmaes(double (*callback)(int, double *), unsigned int dim,
    double *initial, int maxiter, int mu,
    int lambda, double sigma, double *solutions);
int mocmaes(void (*callback)(int,int, double *, double*), unsigned int dim,
    unsigned int numObjectives, double *initial, int maxiter,
    double *lowerBound, double *upperBound, int mu, double sigma, double *solutions);


#ifdef __cplusplus
} // extern "C"
#endif
