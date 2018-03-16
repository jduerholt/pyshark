//#ifndef SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_SPHERE_H
//#define SHARK_OBJECTIVEFUNCTIONS_BENCHMARK_SPHERE_H




/**
 * \brief Convex quadratic benchmark function.
 */
 #include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
 #include <shark/ObjectiveFunctions/BoxConstraintHandler.h>
 #include <iostream>


 /**
 * \brief Implements the benchmark function DTLZ2.
 *
 * See: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.7531&rep=rep1&type=pdf
 * The benchmark function exposes the following features:
 *	- Scalable w.r.t. the searchspace and w.r.t. the objective space.
 *	- Highly multi-modal.
 */
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

 	/// \brief From INameable: return the class name.
 	std::string name() const
 	{ return "Mocustom"; }

 	std::size_t numberOfObjectives()const{
 		return m_numberOfObjectives;
 	}
 	bool hasScalableObjectives()const{
 		return false;
 	}
 	/*void setNumberOfObjectives( std::size_t numberOfObjectives ){
 		m_numberOfObjectives = numberOfObjectives;
 	}*/

 	std::size_t numberOfVariables()const{
 		return m_handler.dimensions();
 	}

 	bool hasScalableDimensionality()const{
 		return true;
 	}

 	/// \brief Adjusts the number of variables if the function is scalable.
 	/// \param [in] numberOfVariables The new dimension.
 	/*void setNumberOfVariables( std::size_t numberOfVariables ){
		m_numberOfVariables = numberOfVariables;
 	}*/

    SearchPointType proposeStartingPoint() const {
        return m_startingPoint;
    }
		/*shark::RealVector x(m_numberOfVariables);

		for (std::size_t i = 0; i < x.size(); i++) {
			x(i) = 0.5;
		}
		return x;
	}*/

 	ResultType eval( const SearchPointType & x ) const {
 		m_evaluationCounter++;
		// transform SearchPointType to array
		double *parr = new double[x.size()];
        double *fitness = new double[m_numberOfObjectives];
        for (int i; i<x.size();i++) parr[i] = x[i];
		// call callback function
		//double *fitness = new double[m_numberOfObjectives];
        m_callback(x.size(),m_numberOfObjectives,parr, fitness);
        //std::cout << "mama" << std::endl;
        //std::cout << fitness[0] << std::endl;
        // put result from callback function into a RealVector object
 		shark::RealVector value( m_numberOfObjectives );
        for(int i; i<m_numberOfObjectives;i++) value[i] = fitness[i];
        // delete heap allocated arrays
        delete[] parr;
        delete[] fitness;
        // return value
        return value;
    }
 		/*std::size_t k = numberOfVariables() - numberOfObjectives() + 1 ;
 		double g = 0.0;
 		for( std::size_t i = numberOfVariables() - k; i < numberOfVariables(); i++ )
 			g += sqr( x( i ) - 0.5);

 		for (std::size_t i = 0; i < numberOfObjectives(); i++) {
 			value[i] = 1.0+g;
 			for( std::size_t j = 0; j < numberOfObjectives() - i -1; ++j)
 				value[i] *= std::cos(x( j ) * M_PI / 2.0);

 			if (i > 0)
 				value[i] *= std::sin(x(numberOfObjectives() - i -1) * M_PI / 2.0);
 		}

 		return value;
 	}*/
 private:
 	std::size_t m_numberOfObjectives;
	std::size_t m_numberOfVariables;
	void (*m_callback)(int,int, double *, double *);
 	shark::BoxConstraintHandler<SearchPointType> m_handler;
    shark::RealVector m_startingPoint;
 };
