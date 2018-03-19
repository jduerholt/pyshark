
#include <shark/Algorithms/DirectSearch/MOCMA.h>
#include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
#include <shark/Algorithms/DirectSearch/CMA.h>

#include <iostream>
#include <fstream>
#include <vector>
#include "socustom.h"
#include "mocustom.h"
#include "sharkwrapper.h"

using namespace std;


#ifdef __cplusplus
extern "C" {
#endif


int mocmaes(void (*callback)(int,int, double *, double *), unsigned int dim, unsigned int numObjectives,
	double *initial, int maxiter, double *lowerBound, double *upperBound, int mu, double sigma, double *solutions)
{
    // setup constraint m_handler
    shark::BoxConstraintHandler<shark::RealVector> handler;
    if(lowerBound)
    {
        // pass data from arrays to searchPoint type
        shark::RealVector lower(dim);
        for(int i = 0; i<dim; i++) lower[i] = lowerBound[i];
        shark::RealVector upper(dim);
        for(int i = 0; i<dim; i++) upper[i] = upperBound[i];
        handler.setBounds(lower, upper);
    }
	// make Searchpoint out of initial array
	shark::RealVector x(dim);
	for (int i = 0; i < x.size(); i++) {
		x(i) = initial[i];
	}
    // setup objective function
	Mocustom custom(dim, numObjectives, handler, x);
	custom.init(callback);
	// setup mocma
	shark::MOCMA mocma;
    if (mu) mocma.mu() = mu;
    mocma.initialSigma() = sigma;
	mocma.init(custom);
	// optimize
	while (custom.evaluationCounter() < maxiter) mocma.step(custom);
	// write the pareto front to pareto.dat
    std::ofstream fpareto;
    fpareto.open ("pareto.dat");
	for( std::size_t i = 0; i < mocma.solution().size(); i++ ) {
        for( std::size_t j = 0; j < numObjectives; j++ ) {
                fpareto<< mocma.solution()[ i ].value[j]<<" ";
        }
        fpareto << "\n";
	}
    fpareto.close();
    // write the solutions xvalues to file
    //std::ofstream fsolutions;
    //solutions.open("solutions.dat");
    for( std::size_t i = 0; i < mocma.solution().size(); i++ )
    {
        for(int j = 0; j < dim; j++)
        {
            solutions[i*dim+j]=mocma.solution()[i].point[j];
            //fsolutions << mocma.solution()[i].point[j]<<" ";
        }
        //fsolutions << "\n";
	}
    //fsolutions.close();
    // put all solution in a heap allocated array
    //double **solutions = new double*[mocma.solution().size()];
    //for(int i = 0; i < numObjectives; i++) solutions[i] = new double[dim];
    /*for(int i = 0; i < mocma.solution().size(); i++)
    {
        //solutions[i] = new double[dim];
        for(int j = 0; j < dim; j++)
        {
            solutions[i*dim+j]=mocma.solution()[i].point[j];
        }
    }*/
	return 0;
}

int cmaes(double (*callback)(int, double *), unsigned int dim,
    double *initial, int maxiter, int mu,
    int lambda, double sigma, double *solutions)
{
    // make Searchpoint out of initial array
	shark::RealVector x(dim);
	for (int i = 0; i < x.size(); i++) {
		x(i) = initial[i];
	}
	//shark::Sphere sphere(2);
	Socustom custom(dim);
	custom.init(callback);
    // initialize the cma
	shark::CMA cma;
	cma.setInitialSigma(sigma);
    if (lambda)
    {
        cma.setLambda(lambda);
        if (mu) cma.setMu(mu);
    }
	cma.init(custom, x);
    cout << "(" << cma.mu()<<","<<cma.lambda()<<")-CMA-ES in dimension "<<dim<<endl;
    // optimize
    //fout.open("outcmaesfit.dat");
	for(int i = 0; i<maxiter; i++)
	{
		cma.step( custom );
        //fout<<custom.evaluationCounter() << " " << cma.condition() << " "
        //    << cma.sigma << " " << cma.solution().calue
	}

	// copy cma.solution.point to python allocated solution pointer
	for(int i = 0; i < dim; i++) solutions[i] = cma.solution().point[i];
	return 0;
}




#ifdef __cplusplus
} // extern "C"
#endif
