
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
/**
 * @typedef actfunc
 * @brief Function pointer type for activation functions.
 */
typedef Matrix (*ActivationFunction) (const Matrix& m);

namespace activation
{
    /**
     * @brief Rectified Linear Unit (ReLU) activation function.
     *
     * ReLU activation sets all negative values in the matrix to zero
     * and keeps the positive values unchanged.
     *
     * @param m The input matrix.
     * @return The matrix after applying the ReLU activation function.
     */
    Matrix relu (const Matrix &m);

    /**
     * @brief Softmax activation function.
     *
     * Softmax activation computes the exponential of each element in the
     * matrix, normalizes the values by dividing each element by the sum of
     * all exponential values, and ensures the resulting values sum up to 1.
     *
     * @param m The input matrix.
     * @return The matrix after applying the Softmax activation function.
     */
    Matrix softmax (const Matrix &m);
}

#endif //ACTIVATION_H