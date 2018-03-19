#pragma once
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
#include <iostream>


 struct Mocustom : public shark::MultiObjectiveFunction
 {
 	Mocustom(std::size_t numberOfVariables, std::size_t numOfObjectives,
        shark::BoxConstraintHandler<SearchPointType> handler, shark::RealVector startingPoint) :
        m_numberOfVariables(numberOfVariables),m_numberOfObjectives(numOfObjectives),
        m_handler(handler), m_startingPoint(startingPoint)
    {
        m_features |= CAN_PROPOSE_STARTING_POINT;
        announceConstraintHandler(&m_handler);
    }

	void init(void (*callback)(int,int, double *, double *)){
        m_evaluationCounter=0;
        m_callback = callback;
    }

 	std::string name() const
 	{ return "Mocustom"; }

 	std::size_t numberOfObjectives()const{
 		return m_numberOfObjectives;
 	}
 	bool hasScalableObjectives()const{
 		return false;
 	}

 	std::size_t numberOfVariables()const{
 		return m_handler.dimensions();
 	}

 	bool hasScalableDimensionality()const{
 		return true;
 	}

    SearchPointType proposeStartingPoint() const {
        return m_startingPoint;
    }

 	ResultType eval( const SearchPointType & x ) const {
 		m_evaluationCounter++;
		// transform SearchPointType to array
		double *parr = new double[x.size()];
        double *fitness = new double[m_numberOfObjectives];
        for (int i; i<x.size();i++) parr[i] = x[i];
		// call callback function
        m_callback(x.size(),m_numberOfObjectives,parr, fitness);
        // put result from callback function into a RealVector object
 		shark::RealVector value( m_numberOfObjectives );
        for(int i; i<m_numberOfObjectives;i++) value[i] = fitness[i];
        // delete heap allocated arrays
        delete[] parr;
        delete[] fitness;
        // return value
        return value;
    }

 private:
 	std::size_t m_numberOfObjectives;
	std::size_t m_numberOfVariables;
	void (*m_callback)(int,int, double *, double *);
 	shark::BoxConstraintHandler<SearchPointType> m_handler;
    shark::RealVector m_startingPoint;
 };
