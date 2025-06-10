// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <fstream>
#include <iostream>
#include <cmath>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * @brief Class representing a mathematical matrix.
 */
class Matrix
{
 public:

  // Constructors/Destructor

  /**
   * @brief Constructs a Matrix object with the specified number of rows
   * and columns.
   * @param rows The number of rows in the matrix.
   * @param cols The number of columns in the matrix.
   */
  Matrix (int rows, int cols);

  /**
   * @brief Default constructor. Constructs an empty Matrix object.
   */
  Matrix ();

  /**
   * @brief Copy constructor. Constructs a Matrix object by copying  another
   * Matrix object.
   * @param m The Matrix object to be copied.
   */
  Matrix (const Matrix &m);

  /**
   * @brief Destructor. Deallocates the memory occupied by the Matrix object.
   */
  ~Matrix ();


  // Methods

  /**
 * @brief Compute the Reduced Row Echelon Form (RREF) of the matrix.
 *
 * This function performs row reduction operations on the matrix to convert
 * it to Reduced Row Echelon Form. The original matrix remains unchanged,
 * and a new matrix representing the RREF is returned as the result.
 *
 * @return A new Matrix object that represents the Reduced Row Echelon Form
 * (RREF) of the original matrix.
 */
  Matrix rref() const;

  /**
   * @brief Sums all elements in the matrix.
   * @return Returns said sum.
   */
  float sum() const;

  /**
   * @brief Get the number of rows in the matrix.
   * @return The number of rows in the matrix.
   */
  int get_rows () const;

  /**
   * @brief Get the number of columns in the matrix.
   * @return The number of columns in the matrix.
   */
  int get_cols () const;

  /**
   * @brief Transpose the matrix.
   * @return A reference to the transposed matrix.
   */
  Matrix &transpose ();

  /**
   * @brief Vectorize the matrix.
   * @return A reference to the vectorized matrix.
   */
  Matrix &vectorize ();

  /**
   * @brief Print the matrix in plain format.
   */
  void plain_print () const;

  /**
   * @brief Perform matrix multiplication with another matrix.
   * @param m The matrix to be multiplied with.
   * @return The resulting matrix after the multiplication.
   */
  Matrix dot (const Matrix &m) const;

  /**
   * @brief Calculate the Frobenius norm of the matrix.
   * @return The Frobenius norm of the matrix.
   */
  float norm () const;

  /**
   * @brief Find the index of the maximum element in the matrix.
   * @return The index of the maximum element.
   */
  int argmax() const;


  // Operators

  /**
   * @brief Perform element-wise addition with another matrix.
   * @param m The matrix to be added.
   * @return The resulting matrix after the addition.
   */
  Matrix operator+ (const Matrix &m) const;

  /**
   * @brief Assign the values of another matrix to this matrix.
   * @param m The matrix to be assigned.
   * @return A reference to the assigned matrix.
   */
  Matrix &operator= (const Matrix &m);

  /**
   * @brief Perform matrix multiplication with another matrix.
   * @param m The matrix to be multiplied with.
   * @return The resulting matrix after the multiplication.
   */
  Matrix operator* (const Matrix &m) const;

  /**
   * @brief Multiply the matrix by a scalar value.
   * @param c The scalar value to multiply with.
   * @return The resulting matrix after the multiplication.
   */
  Matrix operator* (float c) const;

  /**
   * @brief Multiply a scalar value by a matrix.
   * @param c The scalar value to multiply with.
   * @param m The matrix to be multiplied.
   * @return The resulting matrix after the multiplication.
   */
  friend Matrix operator* (float c, const Matrix &m);

  /**
   * @brief Perform element-wise addition with another matrix and assign the
   * result to this matrix.
   * @param m The matrix to be added.
   * @return A reference to the modified matrix.
   */
  Matrix &operator+= (const Matrix &m);

  /**
  * @brief Access and modify an element of the matrix using parentheses syntax.
  * @param row The row index of the element.
  * @param col The column index of the element.
  * @return A reference to the accessed element.
  */
  float &operator() (int row, int col);

  /**
   * @brief Access and modify an element of the matrix using array-like syntax.
   * @param k The linear index of the element.
   * @return A reference to the accessed element.
   */
  float &operator[] (int k);

  /**
  * @brief Access an element of the matrix using parentheses syntax
   * (read-only).
  * @param row The row index of the element.
  * @param col The column index of the element.
  * @return The accessed element.
  */
  float operator() (int row, int col) const;

  /**
   * @brief Access an element of the matrix using array-like syntax
   * (read-only).
   * @param k The linear index of the element.
   * @return The accessed element.
   */
  float operator[] (int k) const;

  /**
   * @brief Overloaded output stream operator for printing the matrix.
   * @param os The output stream object.
   * @param m The matrix to be printed.
   * @return The modified output stream object.
   */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &m);

  /**
  * @brief Overloaded input stream operator for reading values into the matrix.
  * @param is The input stream object.
  * @param m The matrix to be filled with values.
  * @return The modified input stream object.
  */
  friend std::istream &operator>> (std::istream &os, Matrix &m);

 private:
  float **_val; // Pointer to the matrix data
  matrix_dims _dimensions; // Dimensions of the matrix

  /**
   * @brief Deallocate the memory occupied by the matrix.
   */
  void dest();

  /**
   * @brief Create a new matrix with the specified number of rows and columns.
   * @param rows The number of rows in the matrix.
   * @param cols The number of columns in the matrix.
   */
  void create_matrix(int rows, int cols);

  /**
   * @brief Swap between row1 and row2 of the matrix.
   * @param row1 The index of row1 in the matrix.
   * @param row2 The index of row2 in the matrix.
   */
  void row_swap(int row1, int row2) const;
};

#endif //MATRIX_H