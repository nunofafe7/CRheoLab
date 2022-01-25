// Main file for testing

#include <iostream>
#include "lilSpmat.h"

int main(int argc, char const *argv[]) {

      // Declare and initialize a sparse matrix
      lilSpmat spmat = lilSpmat(4,4);

      // Display the number of elements in each row
      for(unsigned int i=0;i<spmat.getNumRows();i++)
      {
            std::cout << spmat.columns_[i].size() << std::endl;
      }

      std::cout << " " << std::endl;

      // Display the number of elements in each row
      // Should provide the same as above since both columns_ and values_ should
      // have the same size
      for(unsigned int i=0;i<spmat.getNumRows();i++)
      {
            std::cout << spmat.values_[i].size() << std::endl;
      }

      std::cout << " " << std::endl;

      // Display the columns in each row
      std::vector<unsigned int>::iterator iit;
      for(unsigned int i=0;i<spmat.getNumRows();i++)
      {
            for(iit = spmat.columns_[i].begin(); iit != spmat.columns_[i].end(); ++iit)
            {
                  std::cout << *iit;
            }
            std::cout << std::endl;
      }

      std::cout << " " << std::endl;

      // Display the columns in each row
      std::vector<double>::iterator dit;
      for(unsigned int i=0;i<spmat.getNumRows();i++)
      {
            for(dit = spmat.values_[i].begin(); dit != spmat.values_[i].end(); ++dit)
            {
                  std::cout << *dit;
            }
            std::cout << std::endl;
      }


      //Conrado - Begin #############################################################
      std::vector<std::vector<double>> spMatTest //Sparse Matrix for Test
      {
        {1.0, 0.0, 2.0, 0.0},
        {0.0, 3.0, 0.0, 0.0},
        {0.0, 4.0, 0.0, 5.0},
        {0.0, 0.0, 0.0, 6.0}
      };

      std::cout << "Sparse matrix:" << std::endl;

      for (int i = 0; i < spMatTest.size(); i++)
      {
            for (int j = 0; j < spMatTest[i].size(); j++)
            {
                  std::cout << spMatTest[i][j] << " ";
            }
            std::cout << std::endl;
      }

      spmat.columns_=
      {
            {0, 2},
            {1},
            {1, 3},
            {3}
      };
      
      std::cout << "Columns indexes:" << std::endl;

      for (int i = 0; i < spmat.columns_.size(); i++)
      {
            for (int j = 0; j < spmat.columns_[i].size(); j++)
            {
                  std::cout << spmat.columns_[i][j] << " ";
            }   
            std::cout << std::endl;
      }

      spmat.values_=
      {
            {1.0, 2.0},
            {3.0},
            {4.0, 5.0},
            {6.0}
      };

      std::cout << "Columns values:" << std::endl;

      for (int i = 0; i < spmat.values_.size(); i++)
      {
            for (int j = 0; j < spmat.values_[i].size(); j++)
            {
                  std::cout << spmat.values_[i][j] << " ";
            }   
            std::cout << std::endl;
      }

      std::vector<double> vecPhi{ 1.0, 2.0, 3.0, 4.0 }; //std::vector< double > vecPhi_(spmat.getNumRows()); //vecPhi_(numRows_);

      std::cout << "Phi vector for multiplication:" << std::endl;

      for (double valuePhi : vecPhi)
            std::cout << valuePhi << " ";
      std::cout << std::endl;

      std::vector<double> v(4); //Vector resulting from the matrix-vector product

      //Call the function that returns the product matrix-vector as a vector
      v = spmat.matMul(vecPhi);
      
      std::cout << "Vector resulting from the matrix-vector product:" << std::endl;

      for (double valueV : v)
            std::cout << valueV << " ";
      std::cout << std::endl;

      unsigned int rowMatVecProd = 2;

      //Call the function that calculates the product (row-of-matrix)-vector for a specific row of the matrix
      double ProdRowMatVec = spmat.vecMul(rowMatVecProd, vecPhi);

      std::cout << "Double resulting from the (row-of-matrix)-vector product:" << std::endl;    
      std::cout << "For row: " << rowMatVecProd << ", Product: " << ProdRowMatVec << std::endl;
      //Conrado - End #############################################################

      return 0;
}

