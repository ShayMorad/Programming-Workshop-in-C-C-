#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (const Matrix w[MLP_SIZE], const Matrix b[MLP_SIZE]) :
    _layer1 (Dense (w[0], b[0], activation::relu)),
    _layer2 (Dense (w[1], b[1], activation::relu)),
    _layer3 (Dense (w[2], b[2], activation::relu)),
    _layer4 (Dense (w[3], b[3], activation::softmax))
{
}

digit MlpNetwork::operator() (const Matrix &m) const
{
  Matrix run_mlp (m);
  run_mlp.vectorize ();
  Matrix matrix1 = _layer1 (run_mlp);
  Matrix matrix2 = _layer2 (matrix1);
  Matrix matrix3 = _layer3 (matrix2);
  Matrix matrix4 = _layer4 (matrix3);
  int max_num_index = matrix4.argmax ();
  digit result = {(unsigned int) max_num_index, matrix4[max_num_index]};
  return result;
}
