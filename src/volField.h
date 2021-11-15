#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "IODictionary.h"
#include "RunTime.h"
#include "Mesh.h"
#include <vector>

typedef std::array<double, 3>   vector3;
//storage 0-T11, 1-T12, 2-T13, 3-T21, 4-T22, 5-T23, 6-T31, 7-T32, 8-T33
typedef std::array<double, 9>   tensor;
//storage 0-T11, 1-T12, 2-T13, 3-T22, 4-T23, 5-T33
typedef std::array<double, 6>   symmTensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<tensor>     tensorField;
typedef std::vector<symmTensor>  symmTensorField;

template< typename vectorType>
class volField
:
    public IODictionary
{
    public:
        // Default constructor
        volField(std::string fileName, const Mesh& mesh, const RunTime& time);

        // No args constructor
        volField();

        // Destructor
        virtual ~volField(){} ;

        // Member Functions
        vectorType readInternalField();
        void shiftField(const vectorType& shiftQuantity);
        void scaleField(const double& scaleQuantity);
        void shiftMaxField();
        void shiftMinField();        
        void projectField(const vector3& projectVector);
        scalarField I1ofTensor();
        scalarField I2ofTensor();
        scalarField I3ofTensor();
        vectorField projectTensorField(const vector3& v1);
        
        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Boundary condition structure
        struct patchBoundaryConditions
        {
            std::string type; 
            vectorType fieldValue; 
            std::map<std::string, std::string> otherInfo; 
            bool valImposed;
        };

        // Read boundary field
        patchBoundaryConditions readBoundaryField(std::string& patchName);
        
    private:
        const Mesh&     mesh_;
        const RunTime&  runTime_;
        vectorType internalField;
        std::string fieldName_;
        std::vector<patchBoundaryConditions> boundaryField_;
           
};

#endif 