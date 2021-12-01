#ifndef VOLFIELDI_H
#define VOLFIELDI_H

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

///////////////////////////////
// volumeField Class methods //
///////////////////////////////
template< typename vectorType>
void volField<vectorType>::shiftField(const vectorType& shiftQuantity)
{   
    
    for(unsigned int i = 0 ; i < internalField.size(); i++){
         internalField[i] = internalField[i] + shiftQuantity;    
    }

    
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        if (boundaryField_[i].valImposed) {
            for(unsigned int j = 0 ; j < boundaryField_[i].fieldValue.size(); j++){
                boundaryField_[i].fieldValue[j] =  boundaryField_[i].fieldValue[j] + shiftQuantity;
            }              
        }
    }     
}

template< typename vectorType>
void volField<vectorType>::scaleField(const double& scaleQuantity)
{   
    
    for(unsigned int i = 0 ; i < internalField.size(); i++){
         internalField[i] = internalField[i] * scaleQuantity;    
    }

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        if (boundaryField_[i].valImposed) {
            for(unsigned int j = 0 ; j < boundaryField_[i].fieldValue.size(); j++){
                boundaryField_[i].fieldValue[j] =  boundaryField_[i].fieldValue[j] * scaleQuantity;
            }
        }
    }     
}

// shift max field
template< typename vectorType>
void volField<vectorType>::shiftMaxField()
{
        // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    vectorType maxInFieldValue = maxField(internalField); 
    vectorType maxBndFieldValue = maxInFieldValue;
    vectorType maxFieldValue = maxInFieldValue;
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        if (boundaryField_[i].valImposed) {
            maxBndFieldValue = maxField(boundaryField_[i].fieldValue);
            if (maxBndFieldValue > maxInFieldValue) maxFieldValue=maxBndFieldValue;
            shiftField(maxFieldValue);
        }
    }
}

// shift min field
template< typename vectorType>
void volField<vectorType>::shiftMinField()
{
    // New operations defined into scalarOperations.h 
        // inline double minField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 minField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor minField(const tensorField& t1)
    vectorType minInFieldValue = minField(internalField); 
    vectorType minBndFieldValue = minInFieldValue;
    vectorType minFieldValue = minInFieldValue;
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        if (boundaryField_[i].valImposed) { 
            minBndFieldValue = minField(boundaryField_[i].fieldValue);
            if (minBndFieldValue > minInFieldValue) minFieldValue=minBndFieldValue;
            shiftField(minFieldValue);
        }
    }
}

// project vector field
template< typename vectorType>
void volField<vectorType>::projectVectorField(const vector3& projectVector)
{   

    if (typeid(internalField).hash_code()==typeid(projectVector).hash_code()) {
        vector3 normProjectVector = projectVector / mag(projectVector);
        // New operation defined into vectorOperations.h 
        // inline vectorField operator*( const scalarField& s1, const vector3& v1)
        // inline scalarField operator&(const vectorField& v1, const vector3& v2)
        internalField = (internalField & normProjectVector) * normProjectVector;

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
            if (boundaryField_[i].valImposed) {       
                boundaryField_[i].fieldValue =  (boundaryField_[i].fieldValue & normProjectVector) * normProjectVector;                     
            }
        }  
    }   
}


// calculate a scalar field to store the 1st Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I1ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
        // TODO this fileName should be based on the baseField fileName
        std::string I1FieldFname="I1of"+fieldName_;
                
        result.fieldName_=I1FieldFname;
        result.runTime_=runTime_;        
        
        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField.push_back(I1(internalField[i]));            
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField_[i].type = "fixedValue";
                result.boundaryField_[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField_[i].fieldValue.size(); j++){
                    result.boundaryField_[i].fieldValue.push_back(I1(boundaryField_[i].fieldValue[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I1ofTensor called for a non tensor Field";
    }    
    return result;
}


// calculate a scalar field to store the 2nd Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I2ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
       // TODO this fileName should be based on the baseField fileName
        std::string I2FieldFname="I2of"+fieldName_;
        
        result.fieldName_=I2FieldFname;
        result.runTime_=runTime_;

        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField.push_back(I2(internalField[i]));   
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField_[i].type = "fixedValue";
                result.boundaryField_[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField_[i].fieldValue.size(); j++){
                    result.boundaryField_[i].fieldValue.push_back(I2(boundaryField_[i].fieldValue[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I2ofTensor called for a non tensor Field";
    }      
    return result;
}

// calculate a scalar field to store the 3rd Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I3ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
        // TODO this fileName should be based on the baseField fileName
        std::string I3FieldFname="I3of"+fieldName_;
        
        result.fieldName_=I3FieldFname;
        result.runTime_=runTime_;        

        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField.push_back(I3(internalField[i]));    
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField_[i].type = "fixedValue";
                result.boundaryField_[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField_[i].fieldValue.size(); j++){
                    result.boundaryField_[i].fieldValue.push_back(I3(boundaryField_[i].fieldValue[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I3ofTensor called for a non tensor Field";
    }   
    return result;
}

// Create a vector field with component of the tensor in one direction
template< typename vectorType>
vectorField volField<vectorType>::projectTensorField(const vector3& v1)
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
        // TODO this fileName should be based on the baseField fileName
        std::string projFieldFname="Projof"+fieldName_;
        
        result.fieldName_=projFieldFname;
        result.runTime_=runTime_;   
        
        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField.push_back(internalField[i] & v1);    
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField_[i].type = "fixedValue";
                result.boundaryField_[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField_[i].fieldValue.size(); j++){
                    result.boundaryField_[i].fieldValue.push_back(boundaryField_[i].fieldValue[j] & v1);
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::projectTensorField called for a non tensor Field";
    }        
    return result;
}


#include "readVolField.h"
#include "fieldOperations.h"
#include "volFieldOperations.h"

#endif
