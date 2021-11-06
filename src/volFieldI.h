#include "volField.h"

template< typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh& mesh, const RunTime& time)
:
    IODictionary(mesh.runTime().Path(), fileName),
    mesh_(mesh),
    runTime_(time),
    internalField( readInternalField() )
{   
   for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        boundaryField_.push_back(readBoundaryField(mesh_.patchList_[i].name_);
    } 
}


#include "readVolField.h"
#include "fieldOperations.h" //pc