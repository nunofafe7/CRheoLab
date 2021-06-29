#ifndef CALCELLCENTERSVOLS_H
#define CALCELLCENTERSVOLS_H

#include "Mesh.h"
#include "Point.h"
#include "Cell.h"
#include "Face.h"
#include <vector>

class calCellCentersVols {

  private:
       const vectorField    fCtrs_ ;
       const vectorField    fAreas_ ;
       const vectorField    cellCenters_;
       const vector<double> cellVols_;    

  public:
        const vectorField&   fCtrs() const
            {
                return fCtrs_;
            }
        const vectorField&   fAreas() const
            {
                return fAreas_;
            }
        const vectorField&  cellCenters() const
            {
                return cellCenters_;
            }

        const vector<double>&  cellVols() const
            {
                return cellVols_; 
            }

        // Constructor
        calCellCentersVols(Mesh M);
        //calCellCentersVols();
        // Destructor 
        virtual ~calCellCentersVols(){};
   
};


#endif // CALCELLCENTERSVOLS_H
