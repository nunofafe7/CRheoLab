#include "DiferencialOperators.h"
#include "mathOperations.h"
#include "spmat.h"
#include <cmath>
#include<vector>

    //******************* Constructor() *******************
GradT::GradT(VolField<scalarField>& vf)
{
    gradCell.resize(vf.mesh().nCells_);
    for(unsigned int h= 0; h < gradCell.size(); h++)
    {
        gradCell[h] = {0, 0, 0};
    }

    analyticGradT.resize(vf.mesh().nCells_);
    for(unsigned int z= 0; z < gradCell.size(); z++)
    {
        analyticGradT[z] = {0, 0, 0};
    }
        
}

    //******************* Numeric Solution *******************
    //********************************************************

    //******************* Internal faces Contributions *******************
void GradT::gradientT(VolField<scalarField>& vf)
{   
    for(unsigned int i= 0; i < vf.mesh().nInteriorFaces_; i++)
    {   
        //getting the ID of the owner and neighbour for each face
        int ownInd = vf.mesh().faceList_[i].getOwner()->ID_; 
        int neiInd = vf.mesh().faceList_[i].getNeighbour()->ID_;

        //getting the face area vector and cell volume
        vector3 sf = vf.mesh().faceList_[i].getAreaVector();
        if (sf[0] < 0.000001) {sf[0] = 0;}
        if (sf[1] < 0.000001) {sf[1] = 0;}
        if (sf[2] < 0.000001) {sf[2] = 0;}

        //getting coordinates
        double xown =  vf.mesh().cellList_.at(ownInd).centerOfMass_[0];
        double yown =  vf.mesh().cellList_.at(ownInd).centerOfMass_[1];
        double down = sqrt((xown*xown)+(yown*yown));

        double xneigh =  vf.mesh().cellList_.at(neiInd).centerOfMass_[0];
        double yneigh =  vf.mesh().cellList_.at(neiInd).centerOfMass_[1];
        double dneigh = sqrt((xneigh*xneigh)+(yneigh*yneigh));

        double xface = vf.mesh().faceList_.at(i).centerOfMass_[0];
        double yface = vf.mesh().faceList_.at(i).centerOfMass_[1];
        double dface = sqrt((xface*xface)+(yface*yface));

        double d1 = dface - down;
        double d2 = dneigh - dface;
        double wFactor = d1 / (d1+d2);

        //calculate Temperature on the face
        double Tface = wFactor * vf.internalFieldRef().at(neiInd) + (1-wFactor)*vf.internalFieldRef().at(ownInd);

        //calculate grad of temperature for one face
        vector3 grad = (sf*Tface);  

        //add the gradient of temperature contribution to the total - need to update!!
        gradCell[ownInd] =  gradCell[ownInd] + grad;
        gradCell[neiInd] =  gradCell[neiInd] - grad;
    //    if (ownInd == 2) {std::cout<<"Cell id="<< ownInd << " gradientInterior:" << gradCell[ownInd]<< std::endl;}
    }
    //******************* Boundary Contributions *******************
    for ( long unsigned int patchI = 0; patchI < vf.mesh().nPatches_; patchI++)
    { 
        int sizeOfPatch( vf.mesh().patchList_[patchI].nFaces_ );
        int startPatchFaceID = vf.mesh().patchList_[patchI].startFace_;

        for (int faceI = 0; faceI < sizeOfPatch; faceI++)
        {
            int ownInd = vf.mesh().faceList_[startPatchFaceID+faceI].getOwner()->ID_;
            vector3 sf = vf.mesh().faceList_[startPatchFaceID+faceI].getAreaVector();
            if (sf[0] < 0.000001 && sf[0] > 0) {sf[0] = 0;}
            if (sf[1] < 0.000001 && sf[1] > 0) {sf[1] = 0;}
            if (sf[1] < 0.000001 && sf[1] > 0) {sf[2] = 0;}

            double xown2 = vf.mesh().cellList_.at(ownInd).centerOfMass_[0];
            double yown2 = vf.mesh().cellList_.at(ownInd).centerOfMass_[1];
            double down2 = sqrt((xown2*xown2)+(yown2*yown2));

            double xface2 = vf.mesh().faceList_[startPatchFaceID+faceI].centerOfMass_[0];
            double yface2 = vf.mesh().faceList_[startPatchFaceID+faceI].centerOfMass_[1];
            double dface2 = sqrt((xface2*xface2)+(yface2*yface2));

            if (sf[2] == 0)
            {
                double Tface = vf.internalFieldRef().at(ownInd)+(((dface2-down2) / (dface2-down2))*(10-vf.internalFieldRef().at(ownInd)));
                vector3 grad2 = (sf*Tface);
                gradCell[ownInd] = gradCell[ownInd] + grad2;
            }

            if (gradCell[ownInd][0] < 0.000001 && gradCell[ownInd][0] > -0.000001) {gradCell[ownInd][0] = 0;}
            if (gradCell[ownInd][1] < 0.000001 && gradCell[ownInd][1] > -0.000001) {gradCell[ownInd][1] = 0;}
            if (ownInd == 0) {std::cout<<"Cell id="<< ownInd << " gradientBoundary:" << gradCell[ownInd]<< std::endl;}
        }
    }

    //******************* Contributions divided by cell volumes *******************
    for (size_t cellI = 0; cellI < vf.mesh().nCells_; cellI++)
    {
        double vol =  vf.mesh().cellList_.at(cellI).getVolume();
        // std::cout << typeof(gradCell[cellI]) << std::endl;
        gradCell[cellI] = (gradCell[cellI])/vol;
    }

    std::cout << "numerical gradient of temperature in cells is: " << gradCell << std::endl;
}

    //******************* Analytic Solution *******************
    //********************************************************
void GradT::analyticGradientT(VolField<scalarField>& vf)
{
    for (size_t cellI = 0; cellI < vf.mesh().nCells_; cellI++)
    {
        double x =  vf.mesh().cellList_.at(cellI).centerOfMass_[0];
        //double y =  vf.mesh().cellList_.at(cellI).centerOfMass_[1]; 

        analyticGradT[cellI] = {0, 0, 0};
        //analyticGradT[cellI] = {2*x, 1, 0};

    }
    std::cout << "analytic gradient of temperature in cells is: " << analyticGradT << std::endl;
}

    //******************* Error Calculation *******************
    //********************************************************
void GradT::errorCalculation(VolField<scalarField>& vf)
{
    individualErrorX.resize(vf.mesh().nCells_);
    for(unsigned int h= 0; h < individualErrorX.size(); h++)
    {
        individualErrorX[h] = 0;
    }

    individualErrorY.resize(vf.mesh().nCells_);
    for(unsigned int h= 0; h < individualErrorY.size(); h++)
    {
        individualErrorY[h] = 0;
    }

    individualErrorZ.resize(vf.mesh().nCells_);
    for(unsigned int h= 0; h < individualErrorZ.size(); h++)
    {
        individualErrorZ[h] = 0;
    }

    //******************* Error In X *******************
    double sumX;
    double maxX = 0;
    double minX = 0; 
    

    for (size_t a = 0; a < vf.mesh().nCells_; a++)
    {   
        //get list of errors in position x for each element of the vector
        individualErrorX[a] = abs(gradCell[a][0] - analyticGradT[a][0]);
        sumX += individualErrorX[a];
        
        //get max value
        if (individualErrorX[a] > maxX) 
        {
            maxX = individualErrorX[a];
        }
        //get min value
        if (individualErrorX[a] < minX) 
        {
            minX = individualErrorX[a];
        }
    }

    double medErrorX = sumX / vf.mesh().nCells_;
    if (medErrorX < 0.000001){medErrorX = 0;}

    std::cout << "Medium quadratic error in x is: " << medErrorX << std::endl;
    std::cout << "Maximum quadratic error in x is: " << maxX << std::endl;
    std::cout << "Minimum quadratic error in x is: " << minX << std::endl;
    //std::cout << "Infinit error is: " << infiniteError << std::endl;
    

    //******************* Error In Y *******************
    double sumY;
    double maxY = 0;
    double minY = 0; 

    for (size_t b = 0; b < vf.mesh().nCells_; b++)
    {   
        //get list of errors in position x for each element of the vector
        individualErrorY[b] = abs(gradCell[b][1] - analyticGradT[b][1]);
        sumY += individualErrorY[b];
        
        //get max value
        if (individualErrorY[b] > maxY) 
        {
            maxY = individualErrorY[b];
        }
        //get min value
        if (individualErrorY[b] < minY) 
        {
            minY = individualErrorY[b];
        }
    }

    double medErrorY = sumY / vf.mesh().nCells_;
    if (medErrorY < 0.000001){medErrorY = 0;}

    std::cout << "Medium quadratic error in y is: " << medErrorY << std::endl;
    std::cout << "Maximum quadratic error in y is: " << maxY << std::endl;
    std::cout << "Minimum quadratic error in y is: " << minY << std::endl;

        //******************* Error In Z *******************
    double sumZ;
    double maxZ = 0;
    double minZ = 0; 

    for (size_t c = 0; c < vf.mesh().nCells_; c++)
    {   
        //get list of errors in position x for each element of the vector
        individualErrorZ[c] = abs(gradCell[c][2] - analyticGradT[c][2]);
        sumY += individualErrorZ[c];
        
        //get max value
        if (individualErrorZ[c] > maxZ) 
        {
            maxZ = individualErrorZ[c];
        }
        //get min value
        if (individualErrorZ[c] < minZ) 
        {
            minZ = individualErrorZ[c];
        }
    }

    double medErrorZ = sumZ / vf.mesh().nCells_;
    if (medErrorZ < 0.000001){medErrorZ = 0;}

    std::cout << "Medium quadratic error in z is: " << medErrorZ << std::endl;
    std::cout << "Maximum quadratic error in z is: " << maxZ << std::endl;
    std::cout << "Minimum quadratic error in z is: " << minZ << std::endl;
}


