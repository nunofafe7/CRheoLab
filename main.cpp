// Main file for testing

#include <iostream>
#include "lilSpmat.h"

int main(int argc, char const *argv[]) {

      // Declare and initialize a sparse matrix
      lilSpmat spmat = lilSpmat(10,10);

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

      return 0;
}
