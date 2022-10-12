
#include <iostream>
#include "Mesh.h"
#include "IODictionary.h"
#include "IODictionaryw.h"
#include "VolField.h"
#include "difOperator.h"

using namespace std;

int main()
{

    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();

    RunTime time;

    Mesh mesh(time);


    // Dictionary& banana2 = field.mesh().lookup<Dictionary>( "transportProperties");
    // double d1 = banana2.lookup<double>("abc");
    VolField<scalarField>  Temperature
    (
        IOObject
        (
            "Temperature",
            time.timeName(),
            mesh,
            fileAction::NO_READ,
            fileAction::NO_WRITE,
            false
        ),
        (double)0.0
    );

    for (size_t cellI = 0; cellI < Temperature.internalField().size(); cellI++)
    {
        double x =  mesh.cellList_.at(cellI).centerOfMass_[0];
        double y =  mesh.cellList_.at(cellI).centerOfMass_[1];
        double z =  mesh.cellList_.at(cellI).centerOfMass_[2];
        
        //Temperature.internalFieldRef().at(cellI) = (x*x)+y ;
        //Temperature.internalFieldRef().at(cellI) = 0 ;
        Temperature.internalFieldRef().at(cellI) = 10 ;
    }

    GradT test0(Temperature);


    test0.gradientT(Temperature);
    test0.analyticGradientT(Temperature);
    test0.errorCalculation(Temperature);
}

