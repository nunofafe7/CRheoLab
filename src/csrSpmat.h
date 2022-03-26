#ifndef CSRSPMAT_H
#define CSRSPMAT_H

#include "spmat.h"
#include "Mesh.h"
#include <vector>

// Class to implement a list of lists for a sparse matrix
// The std::vector structure is used to implement the list

class csrSpmat : public spmat {

public: // change to private later

  // Number of non-null values
  unsigned int numNZ_;

  // Vector of vector for the values
  std::vector<double> values_;

  // Vector of vector for the columns
  std::vector<unsigned int> columns_;

  // Vector of vector for the row pointers
  std::vector<unsigned int> row_ptr_;

public:

  // Constructor
  csrSpmat(Mesh &mesh);

  // Destructor
  virtual ~csrSpmat(){};

  // Returns the sparsity of the matrix
  double sparsity();

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  void addValue(unsigned int i, unsigned int j, double val);

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  void subValue(unsigned int i, unsigned int j, double val);

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  void delValue(unsigned int i, unsigned int j);

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(unsigned int i, unsigned int j);

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense();

  // Returns the product matrix-vector as a vector
  std::vector<double> matMul(const std::vector<double> &vecPhi);

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecMul(const unsigned int i, const std::vector<double> &vecPhi);

};

#endif // CSRSPMAT_H
