
#include <shark/Algorithms/DirectSearch/MOCMA.h>
#include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>
#include <shark/Algorithms/DirectSearch/CMA.h>

#include <iostream>
#include <vector>
#include "socustom.h"
#include "sharkwrapper.h"

using namespace std;


#ifdef __cplusplus
extern "C" {
#endif

double test(int length, double *inp)
{
	// it gets and std::vector and returns an double
	return inp[0]*inp[0];
}


unsigned int do_stuff_with_shark(unsigned int evaluations)
{
	// The C caller does not know or care for what we do inside the
	// function. In particular, we can execute C++ code. Of course, we
	// have to limit ourselves to C return types.

	// We use Shark to run MO-CMA-ES on the DTLZ-2 problem for the number
	// of iterations given by the parameter. THIS IS A DUMMY, here you do
	// whatever it takes to solve your problem.
	shark::DTLZ2 dtlz2;
	dtlz2.setNumberOfVariables( 3 );
	shark::MOCMA mocma;
	dtlz2.init();
	mocma.init(dtlz2);
	while (dtlz2.evaluationCounter() < evaluations) mocma.step(dtlz2);

	// We return the number of Pareto optimal solutions.
	return mocma.solution().size();
}



unsigned int cmaes()
{
	shark::CMA cma;
	cma.setInitialSigma(0.1);
	//shark::Sphere sphere(2);
	Socustom sphere(1);
	sphere.init(test);
	cma.init(sphere, sphere.proposeStartingPoint());
	do {
        cma.step( sphere );

        // Report information on the optimizer state and the current solution to the console.
        cout << sphere.evaluationCounter() << " " << cma.solution().value << " " << cma.solution().point << " " << cma.sigma() << endl;
	} while(cma.solution().value > 1E-20 );
	//cma.init(sphere, sphere.proposeStartingPoint());
	return 0;
}

double* custom_cmaes(double (*callback)(int, double *), unsigned int dim,
	double *initial, double sigma, int maxiter)
{

	//shark::Sphere sphere(2);
	Socustom sphere(dim);
	sphere.init(callback);
	shark::CMA cma;
	//cma.setInitialSigma(0.1);
	cma.setInitialSigma(sigma);
	// make Searchpoint out of initial array
	shark::RealVector x(dim);
	for (int i = 0; i < x.size(); i++) {
		x(i) = initial[i];
	}
	//cma.init(sphere, sphere.proposeStartingPoint());
	cma.init(sphere, x);
	cout << "lambda: " << cma.lambda() << " mu: " << cma.mu() << endl;
	for(int i = 0; i<maxiter; i++)
	{
		cma.step( sphere );
        // Report information on the optimizer state and the current solution to the console.
        cout << sphere.evaluationCounter() << " " << cma.solution().value << " " << cma.solution().point << " " << cma.sigma() << endl;
	}
	// copy cma.solution.point to an heap allocated array
	double *solution = new double[dim];
	for(int i = 0; i < dim; i++) solution[i] = cma.solution().point[i];
	/*do {
        cma.step( sphere );

        // Report information on the optimizer state and the current solution to the console.
        cout << sphere.evaluationCounter() << " " << cma.solution().value << " " << cma.solution().point << " " << cma.sigma() << endl;
	} while(cma.solution().value > 1E-20 );*/
	return solution;
}




#ifdef __cplusplus
} // extern "C"
#endif
