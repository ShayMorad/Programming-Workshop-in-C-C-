#include "Matrix.h"
#define OUTPUT_VALUE 0.1

// Constructors/Destructor

Matrix::Matrix (int rows, int cols) : _dimensions ({rows, cols})
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error ("Enter values bigger than 0.");
  }
  else
  {
    this->_dimensions = {rows, cols};
    create_matrix (rows, cols);
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        (*this) (i, j) = 0;
      }
    }
  }
}

Matrix::Matrix () : Matrix (1, 1)
{

}

Matrix::Matrix (const Matrix &m)
{
  this->_dimensions = {m._dimensions.rows, m._dimensions.cols};
  create_matrix (m._dimensions.rows, m._dimensions.cols);
  for (int i = 0; i < m._dimensions.rows; i++)
  {
    for (int j = 0; j < m._dimensions.cols; j++)
    {
      (*this) (i, j) = m (i, j);
    }
  }
}

Matrix::~Matrix ()
{
  dest ();
}

// Methods
float Matrix::sum () const
{
  float sum = 0;
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      sum += (*this) (i, j);
    }
  }
  return sum;
}

int Matrix::get_rows () const
{
  return this->_dimensions.rows;
}

int Matrix::get_cols () const
{
  return this->_dimensions.cols;
}

Matrix &Matrix::transpose ()
{
  int rows = this->_dimensions.cols, cols = this->_dimensions.rows;
  Matrix transposed_matrix (rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      transposed_matrix (i, j) = (*this) (j, i);
    }
  }
  (*this) = transposed_matrix;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  int rows = this->_dimensions.rows * this->_dimensions.cols;
  int cols = 1;
  Matrix vectorized_matrix (rows, cols);
  for (int i = 0; i < rows; i++)
  {
    vectorized_matrix[i] = (*this)[i];
  }
  (*this) = vectorized_matrix;
  return *this;
}

void Matrix::plain_print () const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot (const Matrix &m) const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  bool size_legit = false;
  if (rows == m._dimensions.rows && cols == m._dimensions.cols)
  {
    size_legit = true;
  }

  if (!size_legit)
  {
    throw std::length_error ("Can't use dot on matrices of different size.");
  }

  Matrix dot = *this;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      (dot) (i, j) *= (m) (i, j);
    }
  }
  return dot;
}

float Matrix::norm () const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  float sum = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      sum += std::pow ((*this) (i, j), 2);
    }
  }
  return (std::sqrt (sum));
}

int Matrix::argmax () const
{
  float max_value = (*this)[0];
  int k = 0;
  for (int i = 0; i < (this->_dimensions.rows * this->_dimensions.cols); i++)
  {
    if ((*this)[i] > max_value)
    {
      max_value = (*this)[i];
      k = i;
    }
  }
  return k;
}

// Operators

Matrix Matrix::operator+ (const Matrix &m) const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  bool size_legit = false;
  if (rows == m._dimensions.rows && cols == m._dimensions.cols)
  {
    size_legit = true;
  }

  if (!size_legit)
  {
    throw std::length_error ("Can't use dot on matrices of different size.");
  }

  Matrix copied_mat = *this;

  for (int i = 0; i < copied_mat._dimensions.rows; i++)
  {
    for (int j = 0; j < copied_mat._dimensions.cols; j++)
    {
      (copied_mat) (i, j) += (m) (i, j);
    }
  }

  return copied_mat;
}

Matrix &Matrix::operator= (const Matrix &m)
{
  if (this == &m)
  {
    return *this;
  }

  this->dest ();
  this->_dimensions.rows = m._dimensions.rows;
  this->_dimensions.cols = m._dimensions.cols;
  this->create_matrix (m._dimensions.rows, m._dimensions.cols);

  for (int i = 0; i < this->_dimensions.rows; i++)
  {
    for (int j = 0; j < this->_dimensions.cols; j++)
    {
      (*this) (i, j) = m (i, j);
    }
  }

  return *this;
}

Matrix Matrix::operator* (const Matrix &m) const
{
  if (this->_dimensions.cols != m._dimensions.rows)
  {
    throw std::length_error ("Can't multiply, cols != rows.");
  }

  int rows = this->_dimensions.rows;
  int cols = m._dimensions.cols;

  Matrix copied_mat (rows, cols);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      (copied_mat) (i, j) = 0;
      for (int l = 0; l < m._dimensions.rows; l++)
      {
        (copied_mat) (i, j) += (((*this) (i, l)) * (m (l, j)));
      }
    }
  }

  return copied_mat;
}

Matrix Matrix::operator* (float c) const
{
  Matrix copied_mat = *this;

  for (int i = 0; i < copied_mat._dimensions.rows; i++)
  {
    for (int j = 0; j < copied_mat._dimensions.cols; j++)
    {
      (copied_mat) (i, j) *= c;
    }
  }

  return copied_mat;
}

Matrix operator* (float c, const Matrix &m)
{
  return (m * c);
}

Matrix &Matrix::operator+= (const Matrix &m)
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  bool size_legit = false;
  if (rows == m._dimensions.rows && cols == m._dimensions.cols)
  {
    size_legit = true;
  }

  if (!size_legit)
  {
    throw std::length_error ("Can't operate += on matrices of different "
                             "size.");
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      (*this) (i, j) += m (i, j);
    }
  }

  return *this;
}

float &Matrix::operator() (int row, int col)
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  if (row < 0 || col < 0 || row >= rows || col >= cols)
  {
    throw std::out_of_range ("Row/Col index is out of matrix range.");
  }

  return (this->_val[row][col]);
}

float &Matrix::operator[] (int k)
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  if (k < 0 || k >= rows * cols)
  {
    throw std::out_of_range ("Index out of matrix range.");
  }

  int row = std::floor (k / this->_dimensions.cols);
  int col = k % cols;

  return this->_val[row][col];
}

float Matrix::operator() (int row, int col) const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  if (row < 0 || col < 0 || row >= rows || col >= cols)
  {
    throw std::out_of_range ("Index out of matrix range.");
  }

  return this->_val[row][col];
}

float Matrix::operator[] (int k) const
{
  int rows = this->_dimensions.rows, cols = this->_dimensions.cols;
  if (k < 0 || k >= rows * cols)
  {
    throw std::out_of_range ("Index out of matrix range.");
  }

  int row = std::floor (k / this->_dimensions.cols);
  int col = k % cols;

  return this->_val[row][col];
}

std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  if (!os)
  {
    return os;
  }

  for (int i = 0; i < m._dimensions.rows; i++)
  {
    for (int j = 0; j < m._dimensions.cols; j++)
    {
      if (m (i, j) > OUTPUT_VALUE)
      {
        os << "**";
      }
      else
      {
        os << "  ";
      }
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>> (std::istream &is, Matrix &m)
{
  // Check for valid input stream
  if (!is)
  {
    throw std::runtime_error ("Can't use input stream.");
  }
  // Check for input stream size
  unsigned int matrix_size_float_bytes = (m._dimensions.rows * m._dimensions
      .cols);
  // Seek to end of stream
  is.seekg (0, std::istream::end);
  unsigned int is_length_bytes = is.tellg ();
  unsigned int is_length_float_bytes = is_length_bytes / sizeof (float);

  if (is_length_float_bytes < matrix_size_float_bytes)
  {
    throw std::length_error ("Input stream size too small to operate.");
  }
  // Seek to start of stream
  is.seekg (0, std::istream::beg);
  // Create new buffer as the size of the stream
  char *buffer = new char[is_length_bytes];
  // Fill buffer
  is.read (buffer, is_length_bytes);
  // Create new pointer that is a float pointer and not char pointer...
  auto *values = reinterpret_cast<float *>(buffer);

  for (unsigned int i = 0; i < matrix_size_float_bytes; i++)
  {
    m[i] = values[i];
  }

  delete[] buffer;

  return is;
}

void Matrix::dest ()
{
  for (int i = 0; i < this->_dimensions.rows; i++)
  {
    delete[] this->_val[i];
  }
  delete[] this->_val;
}

void Matrix::create_matrix (int rows, int cols)
{
  this->_val = new float *[rows];
  for (int i = 0; i < rows; i++)
  {
    this->_val[i] = new (std::nothrow) float[cols];
    if (_val[i] == nullptr)
    {
      for (int j = 0; j < i; j++)
      {
        delete[] _val[j];
      }
      delete[] _val;
      throw std::bad_alloc ();
    }
  }
}

Matrix Matrix::rref() const
{
  Matrix result(_dimensions.rows, _dimensions.cols);
  for (int r = 0; r < _dimensions.rows; ++r)
  {
    if (_dimensions.cols <= r)
    {
      break;
    }
    int i = r;
    while (_val[i][r] == 0)
    {
      ++i;
      if (_dimensions.rows == i)
      {
        i = r;
        ++r;
        if (_dimensions.cols == r)
        {
          return result;
        }
      }
    }
    row_swap(i, r);
    float lv = _val[r][r];
    for (int j = 0; j < _dimensions.cols; ++j)
    {
      _val[r][j] /= lv;
    }
    for (int i = 0; i < _dimensions.rows; ++i)
    {
      if (i != r)
      {
        float lv = _val[i][r];
        for (int j = 0; j < _dimensions.cols; ++j)
        {
          _val[i][j] -= lv * _val[r][j];
        }
      }
    }
  }
  for (int i = 0; i < _dimensions.rows; ++i)
  {
    for (int j = 0; j < _dimensions.cols; ++j)
    {
      result._val[i][j] = _val[i][j];
    }
  }
  return result;
}

void Matrix::row_swap(int row1, int row2) const
{
  float* temp = _val[row1];
  _val[row1] = _val[row2];
  _val[row2] = temp;
}