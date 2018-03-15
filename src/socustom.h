//#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_SPHERE_H
//#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_SPHERE_H

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <iostream>
#include <vector>


/**
 * \brief Convex quadratic benchmark function.
 */
struct Socustom : public shark::SingleObjectiveFunction {

	Socustom(std::size_t numberOfVariables = 5):m_numberOfVariables(numberOfVariables) {
		m_features |= CAN_PROPOSE_STARTING_POINT;
	}

    void init(double (*callback)(int, double *)){
        m_evaluationCounter=0;
        m_callback = callback;
    }

	std::string name() const
	{ return "Socustom"; }

	std::size_t numberOfVariables()const{
		return m_numberOfVariables;
	}

	bool hasScalableDimensionality()const{
		return true;
	}

	void setNumberOfVariables( std::size_t numberOfVariables ){
		m_numberOfVariables = numberOfVariables;
	}

	SearchPointType proposeStartingPoint() const {
		shark::RealVector x(numberOfVariables());

		for (std::size_t i = 0; i < x.size(); i++) {
			x(i) = shark::Rng::gauss(0,1);
		}
		return x;
	}

	double eval(const SearchPointType &p) const {
        //increase counter
		m_evaluationCounter++;
        // transform SearchPointType to std::vector
        double *parr = new double[p.size()];
        for (int i; i<p.size();i++) parr[i] = p[i];
        /*std::vector<double> pvec;
        for (int i; i<p.size(); i++)
        {
            pvec.push_back(p[i]);
        }*/
        // call callback function and returns its value as double
        double fitness = m_callback(p.size(), parr);
        delete[] parr;
        return fitness;

        //return fit;
		//return norm_sqr(p);
	}
private:
	std::size_t m_numberOfVariables;
    double (*m_callback)(int, double *);
    //funktionspointer to callback function
};



//#endif
