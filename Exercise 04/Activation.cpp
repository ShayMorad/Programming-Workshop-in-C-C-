#include "Activation.h"

Matrix activation::relu (const Matrix &m)
{
  Matrix relu_matrix (m);
  long int size = m.get_rows () * m.get_cols ();
  for (int i = 0; i < size; i++)
  {
    if(relu_matrix[i] < 0)
    {
      relu_matrix[i] = 0;
    }
  }
  return relu_matrix;
}

Matrix activation::softmax (const Matrix &m)
{
  Matrix softmax_matrix (m);
  float sum = 0;
  long int size = m.get_rows () * m.get_cols ();
  for (int i = 0; i < size; i++)
  {
    sum += std::exp (softmax_matrix[i]);
  }
  float denominator = 1/sum;
  for (int i = 0; i < size; i++)
  {
    softmax_matrix[i] = denominator *  std::exp(softmax_matrix[i]);
  }
  return softmax_matrix;
}
