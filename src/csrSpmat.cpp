#include "csrSpmat.h"
#include "Mesh.h"
#include <iostream>

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
csrSpmat::csrSpmat(unsigned int numRows, unsigned int numCols, Mesh &mesh)
{
  // Store number of rows and columns
  numRows_ = numRows;
  numCols_ = numCols;

  // Allocate memory for the rows since any row might be accessed at any time
  // Do not do the same for each columns_[i] and values_[i] vector since their size
  // should only increase as new entries are added
  columns_.resize(numRows_);
  values_.resize(numRows_);

  // determine the total number of non-zeros values (number of cells plus its neighbours)
  unsigned int nz = 0;
  const Cell* neigh_ptr;
  for (unsigned int j=0;j++;j<mesh.cellList_[i].cellFaces_.size()) // getter?
  {
    neigh_ptr = mesh.cellList_[i].cellFaces_[j].getNeighbour()
    if(neigh_ptr)
    {
       nz += 1;
    }
  }

  // fill-in the sparse matrix with positions of non-null values (number of cells plus its neighbours)
  unsigned int nz = 0;
  const Cell* neighbour;
  for (unsigned int j=0;j++;j<mesh.cellList_[i].cellFaces_.size()) // getter?
  {
    neigh_ptr = mesh.cellList_[i].cellFaces_[j].getNeighbour()
    if(neigh_ptr)
    {
       nz += 1;
    }
  }



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

// Returns the value in position (i,j) if exists, otherwise returns 0
double lilSpmat::getValue(unsigned int i, unsigned int j);
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

  unsigned int j = 0;

  for(unsigned int i = 0; i < numRows_; i++)
  {

    v[i] = 0.0;

    while (j < row_ptr_[i+1])
    {

      v[i] += values_[j] * vecPhi[columns_[j]];

      j += 1;//++j;
    }

  }

  return v;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double csrSpmat::vecMul(const unsigned int i, const std::vector<double> &vecPhi)
{
  double sumProdRow = 0.0;

  unsigned int j = 0;

  while (j < row_ptr_[i+1])
  {

    sumProdRow += values_[j] * vecPhi[columns_[j]];

    j += 1;//++j;

  }

  return sumProdRow;
}
