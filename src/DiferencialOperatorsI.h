#include "DiferencialOperators.h"
#include "mathOperations.h"

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

void GradT::gradientT(VolField<scalarField>& vf)
{   
    for(unsigned int i= 0; i < vf.mesh().nInteriorFaces_; i++)
    {   
        //getting the ID of the owner and neighbour for each face
        int ownInd = vf.mesh().faceList_[i].getOwner()->ID_;//->ID_ will be soon replaced with a getter // <----------------------(Owner index) 
        int neiInd = vf.mesh().faceList_[i].getNeighbour()->ID_;  // <------- (Neighbour index)

        //getting the face area vector and cell volume 
        vector3 sf = vf.mesh().faceList_[i].getAreaVector(); //<--------------Face area vector

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
        //vf.internalFieldRef().at(ownInd)+(((dface-down) / (dneigh-down))*(vf.internalFieldRef().at(neiInd)-vf.internalFieldRef().at(ownInd)));
        //(vf.internalFieldRef().at(ownInd)+vf.internalFieldRef().at(neiInd))*0.5;

        //calculate grad of temperature for one face
        vector3 grad = (sf*Tface);

        //add the gradient of temperature contribution to the total - need to update!!
        gradCell[ownInd] =  gradCell[ownInd] + grad;
        gradCell[neiInd] =  gradCell[neiInd] + grad;
        //grad = {0,0,0};
    }

    for(unsigned int i= 0; i < vf.mesh().nBoundaryFaces_; i++)
    {   
        //getting the ID of the owner and neighbour for each face
        int ownInd = vf.mesh().faceList_[i].getOwner()->ID_;//->ID_ will be soon replaced with a getter // <----------------------(Owner index) 
        //int neiInd = vf.mesh().faceList_[i].getNeighbour()->ID_;  // <------- (Neighbour index)

        //getting the face area vector and cell volume 
        vector3 sf = vf.mesh().faceList_[i].getAreaVector(); //<--------------Face area vector
        //double vol = vf.mesh().cellList_[ownInd].getVolume();

        //getting coordinates
        double xown2 =  vf.mesh().cellList_.at(ownInd).centerOfMass_[0];
        double yown2 =  vf.mesh().cellList_.at(ownInd).centerOfMass_[1];
        double down2 = sqrt((xown2*xown2)+(yown2*yown2));

        double xface2 = vf.mesh().faceList_.at(i).centerOfMass_[0];
        double yface2 = vf.mesh().faceList_.at(i).centerOfMass_[1];
        double dface2 = sqrt((xface2*xface2)+(yface2*yface2));

        //calculate Temperature on the face
        double Tface = vf.internalFieldRef().at(ownInd)+(((dface2-down2) / (dface2-down2))*(0-vf.internalFieldRef().at(ownInd)));
        //(vf.internalFieldRef().at(ownInd)+0)*0.5;

        //calculate grad of temperature for one face
        vector3 grad2 = (sf*Tface);

        //add the gradient of temperature contribution to the total - need to update!!
        gradCell[ownInd] = gradCell[ownInd] + grad2;
        //grad2 = {0,0,0};
    }

    for (size_t cellI = 0; cellI < vf.mesh().nCells_; cellI++)
    {
        double vol =  vf.mesh().cellList_.at(cellI).getVolume();
        
        gradCell[cellI] = (gradCell[cellI])/vol;
    }

    std::cout << "numerical gradient of temperature in cells is: " << gradCell << std::endl;
}

void GradT::analyticGradientT(VolField<scalarField>& vf)
{
    for (size_t cellI = 0; cellI < vf.mesh().nCells_; cellI++)
    {
        double x =  vf.mesh().cellList_.at(cellI).centerOfMass_[0];
        //double y =  vf.mesh().cellList_.at(cellI).centerOfMass_[1]; 

        analyticGradT[cellI] = {2*x, 1, 0};

    }
    std::cout << "analytic gradient of temperature in cells is: " << analyticGradT << std::endl;
}

void GradT::errorCalculation(VolField<scalarField>& vf)
{
    double sum;
    double max;
    double min; 

    for (size_t b = 0; b < vf.mesh().nCells_; b++)
    {   
        //get list of errors in position x for each element of the vector
        vector<double> individualError;
        individualError[b] = abs(gradCell[b][0] - analyticGradT[b][0]);
        sum += individualError[b];
        
        //get max value
        if (b == 0) 
        {
            individualError[b] = max;
        }
        if (individualError[b] > max) 
        {
            max = individualError[b];
        }
        //get min value
        if (b == 0) 
        {
            individualError[b] = min;
        }
        if (individualError[b] > min) 
        {
            min = individualError[b];
        }
    }

    double medError = sum / vf.mesh().nCells_;

    std::cout << "Medium quadratic error (L1) is: " << medError << std::endl;
    std::cout << "Maximum quadratic error is: " << max << std::endl;
    std::cout << "Minimum quadratic error is: " << min << std::endl;
    //std::cout << "Infinit error is: " << infiniteError << std::endl;
}


