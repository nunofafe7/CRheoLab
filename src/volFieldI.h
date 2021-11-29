#include "volField.h"

template< typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh& mesh, const RunTime& time)
:
    IODictionary(time.Path(), fileName),
    mesh_(mesh),
    runTime_(time),
    internalField(readInternalField()),
    fieldName_(fileName) 
{   
    // read boundary field
   for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        boundaryField_.push_back(readBoundaryField(mesh_.patchList_[i].name_));
    } 
}

//no args constructor
template< typename vectorType>
volField<vectorType>::volField()
{ }

//copy constructor
template< typename vectorType>
volField<vectorType>::volField(const volField<vectorType> &volFieldBase)
{ 
 //TODO CReate a copy contructor
}

#include "readVolField.h"
#include "fieldOperations.h"
#include "volFieldOperations.h"
