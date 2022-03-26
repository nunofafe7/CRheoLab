// Main file for testing

#include <iostream>
#include "csrSpmat.h"

int main(int argc, char const *argv[]) {

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<std::vector<double>> spMatTest //Sparse Matrix for Test
      {
        {1.0, 0.0, 2.0, 0.0},
        {0.0, 3.0, 0.0, 0.0},
        {0.0, 4.0, 0.0, 5.0},
        {0.0, 0.0, 0.0, 6.0}
      };

      for (unsigned int i = 0; i < spMatTest.size(); i++)
      {
            for (unsigned int j = 0; j < spMatTest[i].size(); j++)
            {
                  std::cout << spMatTest[i][j] << " ";
            }
            std::cout << std::endl;
      }

      //#############################################################

      /*spmat.columns_=
      {
            {0, 2},
            {1},
            {1, 3},
            {3}
      };

      spmat.values_=
      {
            {1.0, 2.0},
            {3.0},
            {4.0, 5.0},
            {6.0}
      };*/

      //#############################################################

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix construction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      Mesh mesh;

      // Declare and initialize a sparse matrix
      csrSpmat spmat = csrSpmat(mesh);

      // add values
      spmat.addValue(0,0,1.0);
      spmat.addValue(0,2,2.0);
      spmat.addValue(1,1,3.0);
      spmat.addValue(2,1,4.0);
      spmat.addValue(2,3,5.0);
      spmat.addValue(3,3,6.0);

      // add some garbage values
      spmat.addValue(2,2,100.0);
      spmat.addValue(3,2,100.0);

      // delete garbage values
      spmat.delValue(2,2);
      spmat.delValue(3,2);

      std::cout << "Columns values:" << std::endl;
      for (unsigned int i = 0; i < spmat.values_.size(); i++)
      {
            std::cout << spmat.values_[i] << " ";
      }
      std::cout << std::endl;

      std::cout << "Columns indexes:" << std::endl;
      for (unsigned int i = 0; i < spmat.columns_.size(); i++)
      {
            std::cout << spmat.columns_[i] << " ";
      }
      std::cout << std::endl;

      std::cout << "Row pointers:" << std::endl;
      for (unsigned int i = 0; i < spmat.row_ptr_.size(); i++)
      {
            std::cout << spmat.row_ptr_[i] << " ";
      }
      std::cout << std::endl;

      // std::cout << "#############################################################" << std::endl;
      // std::cout << "Test sparse matrix to dense format" << std::endl;
      // std::cout << "#############################################################" << std::endl;
      //
      // // Vector of vectors to store the sparse matrix in a dense format
      // std::vector< std::vector<double> > denseMatrix;
      //
      // // Returns the sparse matrix in a dense format as a vector of vectors
      // denseMatrix = spmat.dense();
      //
      // std::cout << "Dense matrix:" << std::endl;
      //
      // for (unsigned int i = 0; i < denseMatrix.size(); i++)
      // {
      //       for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
      //       {
      //             std::cout << denseMatrix[i][j] << " ";
      //       }
      //       std::cout << std::endl;
      // }

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix multiplication" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<double> vecPhi{ 1.0, 2.0, 3.0, 4.0};

      std::cout << "Phi vector for multiplication:" << std::endl;
      for (double valuePhi : vecPhi)
            std::cout << valuePhi << std::endl;

      std::vector<double> v(4); //Vector resulting from the matrix-vector product

      //Call the function that returns the product matrix-vector as a vector
      v = spmat.matMul(vecPhi);

      std::cout << "Vector resulting from the matrix-vector product:" << std::endl;
      for (double valueV : v)
            std::cout << valueV << std::endl;

      unsigned int rowMatVecProd = 2;

      //Call the function that calculates the product (row-of-matrix)-vector for a specific row of the matrix
      double ProdRowMatVec = spmat.vecMul(rowMatVecProd, vecPhi);

      std::cout << "Double resulting from the (row-of-matrix)-vector product:" << std::endl;
      std::cout << "For row: " << rowMatVecProd << ", Product: " << ProdRowMatVec << std::endl;

      return 0;
}
