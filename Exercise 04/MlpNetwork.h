//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork
{
 public:
  /**
   * @brief Constructs an MLP network with given weight matrices, bias
   * matrices, and activation functions.
   * @param w An array of weight matrices for each layer in the network.
   * @param b An array of bias matrices for each layer in the network.
   */
  MlpNetwork(const Matrix w[MLP_SIZE], const Matrix b[MLP_SIZE]);

  /**
   * @brief Apply the MLP network operation to an input matrix and return
   * the output digit.
   * @param m The input matrix.
   * @return The output digit produced by the MLP network.
   */
  digit operator()(const Matrix &m) const;

 private:
  Dense _layer1;
  Dense _layer2;
  Dense _layer3;
  Dense _layer4;
};

#endif // MLPNETWORK_H