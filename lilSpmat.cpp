#include "lilSpmat.h"

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
lilSpmat::lilSpmat(unsigned int numRows, unsigned int numCols)
{
  // Store number of rows and columns
  numRows_ = numRows;
  numCols_ = numCols;

  // Allocate memory for the rows since any row might be accessed at any time
  // Do not do the same for each columns_[i] and values_[i] vector since their size
  // should only increase as new entries are added
  columns_.reserve(numRows_);
  values_.reserve(numRows_);
}

// Returns the sparsity of the matrix
double lilSpmat::sparsity()
{
  return 0.0;
}


//Conrado - Begin #############################################################

// Function that returns the product matrix-vector as a vector
std::vector<double> lilSpmat::matMul(const std::vector<double> &vecPhi)
{
  std::vector<double> v(vecPhi.size());
  unsigned int id_column = 0;

  //for(unsigned int i=0;i<spmat.getNumRows();i++)
  for(unsigned int i=0;i<columns_.size();i++)
  {
    v[i] = 0.0;
    
    for(unsigned int j=0;j<columns_[i].size();j++)
    {

      id_column = columns_[i][j];
      v[i] += values_[i][j] * vecPhi[id_column];

    }
  }

  return v;
}

/*std::vector<double> lilSpmat::matMul(const std::vector<double> &vecPhi)
{
  //std::vector<double> v(vecPhi.size());
  std::vector<double> v;
  //v.reserve(vecPhi.size());
  //v.resize(vecPhi.size());

  unsigned int id_column = 0;

  //for(unsigned int i=0;i<spmat.getNumRows();i++)
  for(unsigned int i=0;i<columns_.size();i++)
  {
    //v[i] = 0.0;
    double val = 0.0;

    for(unsigned int j=0;j<columns_[i].size();j++)
    {

      id_column = columns_[i][j];

      //v[i] += values_[i][j] * vecPhi[id_column];
      val += values_[i][j] * vecPhi[id_column];

    }
    v.push_back(val);
  }

  return v;
}*/

double lilSpmat::vecMul(const unsigned int i, const std::vector<double> &vecPhi)
{

  double sumProdRow = 0.0;
  unsigned int id_column = 0;

  for(unsigned int j=0;j<columns_[i].size();j++)
  {

    id_column = columns_[i][j];

    sumProdRow += values_[i][j] * vecPhi[id_column];

  }

  return sumProdRow;
}


//Conrado - End #############################################################
