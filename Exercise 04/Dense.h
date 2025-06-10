#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"


/**
 * @class Dense
 * @brief Represents a dense layer in a neural network.
 *
 * The Dense class encapsulates the weights, biases, and activation function
 * for a dense layer in a neural network. It provides methods to access the
 * layer parameters and apply the layer operation to an input matrix.
 */
class Dense
{
 public:

  /**
   * @brief Constructs a Dense layer with given weights, biases, and
   * activation function.
   * @param w The weight matrix of the layer.
   * @param b The bias matrix of the layer.
   * @param actfunc The activation function to be applied by the layer.
   */
  Dense (const Matrix &w, const Matrix &b, ActivationFunction actfunc);

  /**
   * @brief Get the weight matrix of the layer.
   * @return The weight matrix.
   */
  const Matrix &get_weights () const;

  /**
   * @brief Get the bias matrix of the layer.
   * @return The bias matrix.
   */
  const Matrix &get_bias () const;

  /**
   * @brief Get the activation function of the layer.
   * @return The activation function.
   */
  ActivationFunction get_activation () const;

  /**
   * @brief Apply the dense layer operation to an input matrix.
   * @param m The input matrix.
   * @return The output matrix after applying the dense layer operation.
   */
  Matrix operator() (const Matrix &m) const;

 private:
  Matrix _w; // Weight matrix
  Matrix _b; // Bias matrix
  ActivationFunction _actfunc; // Activation function

};

#endif //DENSE_H
