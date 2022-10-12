#ifndef GRADT_H
#define GRADT_H

#include "IODictionary.h"
#include "RunTime.h"
#include "BoundaryField.h"
#include "VolField.h"

class GradT
{
    public:

        //Data Members
        std::vector<vector3> gradCell;
        std::vector<vector3> analyticGradT;
        std::vector<double> individualErrorX;
        std::vector<double> individualErrorY;
        std::vector<double> individualErrorZ;
        vector3 nuno;

        // Constructor
        GradT(VolField<scalarField>& vf);

        //member function
        void gradientT(VolField<scalarField>& vf);
        void analyticGradientT(VolField<scalarField>& vf);
        void errorCalculation(VolField<scalarField>& vf);

        // Destructor
        virtual ~GradT(){};

    private:

};

#include "DiferencialOperatorsI.h"

#endif
