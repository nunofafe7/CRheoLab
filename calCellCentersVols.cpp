#include "calCellCentersVols.h"
#include <vector>

//Function to calculate volumes and centers of the elements(polyhedrons)

calCellCentersVols::calCellCentersVols(Mesh M)
{
   vectorField                         fCtrs;  //face Centers
   vectorField                         fAreas;     // faceArea Vectors  
   vectorField                         cellCenters(M.nCells_, {0,0,0}); // cellCenters, a array of cordinate points
   vector<double>                      cellVols(M.nCells_,0.0);   //cell Volumes, a array of doubles all as zero by default  

  // 1.0e-37 is the value of VSMALL constant in OpenFOAM it will be used in the sequel to avoid Zero Volumes ---> Zero Divisors
  double VSMALL = 1.0e-37;

//---*****************************Computing the estimated cells***************************---//

// Getting the face centers array (assuming that the face Centers are already known)
for (int i = 0 ; i < M.faceList_.size(); i++) {
    fCtrs[i] = M.faceList_[i].getCenterOfMass();
}

// Getting the face area vectors array 

for (int i = 0 ; i < M.faceList_.size(); i++) {
    fAreas[i] = M.faceList_[i].getAreaVector();
}
/*
Now notice that:
- The number of owners  =  total number of faces = interior + boundary faces 
- The number of neighbours  =  number of interior faces
*/
//Listing adresses of the owners and the neighbours
  //---owners----//

vector<int> own ; // (cell) owners addresses array

for (int i = 0 ; i < M.faceList_.size(); i++){
    own[i] = M.faceList_[i].faceOwner();
}

vector<int> nei; //(cell)neighbours addresses array
for (int i = 0 ; i < M.faceList_.size(); i++){
    nei[i] = M.faceList_[i].faceNeighbour();
}
     
//Listing the geometric centers X_G
vectorField cEst(M.nCells_,{0,0,0});
vector<int> nCellFaces(M.nCells_,0);           
        
for(int face_index = 0; face_index < own.size();face_index++)
    {     
     cEst[own[face_index]] = cEst[own[face_index]] + fCtrs[own[face_index]];
     nCellFaces[own[face_index]] += 1 ;
    }

for(int face_index = 0; face_index < nei.size();face_index++)
    {     
     cEst[nei[face_index]] = cEst[nei[face_index]] + fCtrs[nei[face_index]];
     nCellFaces[nei[face_index]] += 1 ;
    }

for(int cell_index = 0; cell_index < cEst.size();cell_index++)
    {     
     cEst[cell_index] = cEst[cell_index]/nCellFaces[cell_index];
    }


//---*****************************Calculating cell centers and volumes***************************---//


    for(int face_index = 0; face_index < own.size();face_index++){
       //To Calculate Triangular Volume 
       double pyrVol =  std::max(fAreas[face_index] & (fCtrs[face_index]-cEst[own[face_index]]),VSMALL)/3;
             // & stands for the inner product 
             // max is to avoid zero volumes 
       
       //To Calculate face-pyramid centre
       vector3 pyrc = (0.75)*fCtrs[face_index] + (0.25)*cEst[own[face_index]];

       //Accumulate volume-weighted face-pyramid center
       cellCenters[own[face_index]] = cellCenters[own[face_index]] + pyrVol*pyrc;

       //Accumulate face-pyramid volume
       cellVols[own[face_index]] += pyrVol;
    }

    

    for(int face_index = 0; face_index < nei.size();face_index++){
       //To Calculate Pyramid Volume 
       double pyrVol =  std::max(fAreas[face_index] & (fCtrs[face_index]-cEst[nei[face_index]]),VSMALL)/3;
             // & stands for the inner product 
       
       //To Calculate face-pyramid centre
       vector3 pyrc = (0.75)*fCtrs[face_index] + (0.25)*cEst[nei[face_index]];

       //Accumulate volume-weighted face-pyramid center
       cellCenters[nei[face_index]] = cellCenters[nei[face_index]] + pyrVol*pyrc;

       //Accumulate face-pyramid volume
       cellVols[nei[face_index]] += pyrVol;
    }


//-------------------********************* Notice that ************************************-----//

/*
In the above code, fCtrs stands for the X_CE . "cEst-fCtrs" corresponds to the distance vector d_Gf .
*/

//---*************************-The final values of cells centroids (and volumes)***************************---//
   cellCenters  = cellCenters/cellVols;
   //cellVols are already the final volumes of the cells .
}


