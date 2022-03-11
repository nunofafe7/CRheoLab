#include "csrSpmat.h"
#include <iostream>

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
csrSpmat::csrSpmat(unsigned int numRows, unsigned int numCols, fvMesh mesh)
{
  // Store number of rows and columns
  numRows_ = numRows;
  numCols_ = numCols;

}

// Returns the sparsity of the matrix
double csrSpmat::sparsity()
{
  return 0.0;
}

// Adds a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::addValue(unsigned int i, unsigned int j, double val)
{

}

// Subtracts a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::subValue(unsigned int i, unsigned int j, double val)
{

}

// Deletes the value in position (i,j) if exists, otherwise does nothing
void csrSpmat::delValue(unsigned int i, unsigned int j)
{

}

// Returns the sparse matrix in a dense format as a vector of vectors
std::vector< std::vector<double> > csrSpmat::dense()
{
  std::vector< std::vector<double> > denseMatrix(numRows_);

  return denseMatrix;
}

// Function that returns the product matrix-vector as a vector
std::vector<double> csrSpmat::matMul(const std::vector<double> &vecPhi)
{
  std::vector<double> v(vecPhi.size());

  return v;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double csrSpmat::vecMul(const unsigned int i, const std::vector<double> &vecPhi)
{
  double sumProdRow = 0.0;

  return sumProdRow;
}
