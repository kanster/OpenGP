#ifndef LIKELIHOOD_FUNCTION_GAUSSIAN_WITH_DERIVATIVE_OBSERVATIONS_HPP
#define LIKELIHOOD_FUNCTION_GAUSSIAN_WITH_DERIVATIVE_OBSERVATIONS_HPP

#include <cmath>

#include "../../util/macros.hpp"
#include "../../data/DerivativeTrainingData.hpp"
#include "../../data/TestData.hpp"

namespace GPOM{

template<Scalar>
class LikGauss
{
// define matrix types
protected:	TYPE_DEFINE_VECTOR(Scalar);

// define hyperparameters
public:		TYPE_DEFINE_HYP(Scalar, 2); // sigma_nf, sigma_nd

	// diagonal vector
	static VectorPtr lik(const Hyp &logHyp, const DerivativeTrainingData<Scalar> derivativeTrainingData, const int pdHypIndex = -1)
	{
		assert(pdHypIndex < logHyp.size());

		// some constants
		const int N  = derivativeTrainingData.N();
		const int Nd = derivativeTrainingData.Nd();
		const int D  = derivativeTrainingData.D();
		const int NN = derivativeTrainingData.NN();

		// number of training data
		VectorPtr pD(new Vector(NN));

		const Scalar snf2 = exp(static_cast<Scalar>(2.f) * logHyp(0));
		const Scalar snd2 = exp(static_cast<Scalar>(2.f) * logHyp(1));

		// derivatives w.r.t log(hyperparameter)
		// K =  FF,  FD1,  FD2,  FD3
      //       -, D1D1, D1D2, D1D3
      //       -,    -, D2D2, D2D3
		//       -,    -,    -, D3D3
		switch(pdHypIndex)
		{
		case 0:
			{
				pD->head(N).fill(static_cast<Scalar>(2.f) * snf2);
				pD->tail(Nd*D).setZero();
				break;
			}

		case 1:
			{
				pD->head(N).setZero();
				pD->tail(Nd*D).fill(static_cast<Scalar>(2.f) * snd2);
				break;
			}

		default:
			{
				pD->head(N).fill(snf2);
				pD->tail(Nd*D).fill(snd2);
			}
		}

		return pD;
	}

	//// diagonal matrix
	//MatrixPtr operator()(MatrixConstPtr pX, const Hyp &logHyp, const int pdIndex = -1) const
	//{
	//	// number of training data
	//	const int N = getN();
	//	MatrixPtr pD(new Matrix(N, N));
	//	pD->setZero();

	//	// derivatives w.r.t sn
	//	if(pdIndex == 0)			pD->diagonal().fill(((Scalar) 2.f) * exp((Scalar) 2.f * logHyp(0)));

	//	// likelihood
	//	else								pD->diagonal().fill(exp((Scalar) 2.f * logHyp(0)));

	//	return pD;
	//}
};

}

#endif