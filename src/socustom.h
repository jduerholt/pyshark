#pragma once
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <iostream>
#include <vector>


struct Socustom : public shark::SingleObjectiveFunction {

	Socustom(std::size_t numberOfVariables):
        m_numberOfVariables(numberOfVariables)
    {
		//m_features |= CAN_PROPOSE_STARTING_POINT;
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
		return false;
	}


	double eval(const SearchPointType &p) const {
        //increase counter
		m_evaluationCounter++;
        // transform SearchPointType to array
        double *parr = new double[p.size()];
        for (int i; i<p.size();i++) parr[i] = p[i];
        // call callback function and returns its value as double
        double fitness = m_callback(p.size(), parr);
        delete[] parr;
        return fitness;
	}

private:
	std::size_t m_numberOfVariables;
    double (*m_callback)(int, double *);
};



//#endif
