#include "Face.h"

Cell::Cell()
:
ID_(-1),
volume_(-1),
centerOfMass_({-1,-1,-1}),
skewness_(-1),
cellFaces_()
{
}


void Cell::setCellID(const int& ID)
{
    ID_ = ID;
}

void Cell::setSkewness(const double skewness)
{
    skewness_ = skewness;
}


void Cell::setCellFaces(const vector<Face*>& cellFaces)
{
    // Deep copy of points
    cellFaces_=cellFaces;   
}


const vector3& Cell::getCenterOfMass() const
{
    return centerOfMass_;
}

const double Cell::getSkewness() const
{
    return skewness_;
}
