#ifndef _GAUSSIAN_PROCESSES_HPP_
#define _GAUSSIAN_PROCESSES_HPP_

#include "Trainer.hpp"

namespace GP{
template<typename Scalar, 
			template<typename> class MeanFunc, 
			template<typename> class CovFunc, 
			template<typename> class LikFunc,
			template <typename, 
						 template<typename> class,
						 template<typename> class,
						 template<typename> class> class InfMethod>
class GP : public InfMethod<Scalar, MeanFunc, CovFunc, LikFunc>
{
public:
	// train hyperparameters
	template<class SearchStrategy, class StoppingStrategy, template<typename> class GeneralTrainingData>
	static void train(typename InfMethod<Scalar, MeanFunc, CovFunc, LikFunc>::Hyp	&logHyp,
							const GeneralTrainingData<Scalar>	&generalTrainingData,
							const int									maxIter = 0,
							const double								minValue = 1e-7)
	{
		assert(generalTrainingData.N() > 0);
		if(generalTrainingData.N() <= 0) return;

		Trainer<Scalar, MeanFunc, CovFunc, LikFunc, InfMethod, GeneralTrainingData> trainer(generalTrainingData);
		trainer.train<SearchStrategy, StoppingStrategy>(logHyp, maxIter, minValue);
	}
};

}

#endif