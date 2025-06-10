#include "Dense.h"

Dense::Dense (const Matrix &w, const Matrix &b, ActivationFunction actfunc)
{
  this->_actfunc = actfunc;
  this->_w = w;
  this->_b = b;
}

const Matrix &Dense::get_weights () const
{
  return this->_w;
}

const Matrix &Dense::get_bias () const
{
  return this->_b;
}

ActivationFunction Dense::get_activation () const
{
  return this->_actfunc;
}

Matrix Dense::operator()(const Matrix& m) const
{
  Matrix output = get_activation()((this->_w * m) + this->_b);
  return output;
}