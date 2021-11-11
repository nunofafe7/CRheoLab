#ifndef FIELDOPERATIONS_H
#define FIELDOPERATIONS_H

#include "volField.h"

// Check if both vectors have the same size
template <typename T1>
inline void checkSize(const std::vector<T1>& v1, const std::vector<T1>& v2)
{
    if(v1.size() != v2.size() )
    {
        throw std::length_error("Vectors do not have the same dimensions");
    }
}

// Math Operations

// At the field level
// Summation
template <typename T>
inline std::vector<T> operator+(const std::vector<T> & v1, const std::vector<T> & v2)
{

    checkSize(v1,v2);
   
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] + v2[i];
   }

   return result;
}


template <typename T>
inline std::vector<T> operator-(const std::vector<T> & v1, const std::vector<T> & v2)
{

    checkSize(v1,v2);
   
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] - v2[i];
   }

   return result;
}

#endif

////////////////////////////////////////
// volField usefull functions add fields
////////////////////////////////////////

// sum two volFields
template <typename T>
inline volField<T> operator+(const volField<T> & vf1, const volField<T> & vf2)
{    
    volField<T> result(vf1.internalField.size());
    
    result.internalField = vf1.internalField + vf2.internalField;
    
    // ToDo -> apply just if the boundary value is imposed
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        result.boundaryField_[i] = vf1.boundaryField_[i].fieldValue + vf2.boundaryField_[i].fieldValue        
    }    

    return result;
}

// subtraction of two volFields
template <typename T>
inline volField<T> operator-(const volField<T> & vf1, const volField<T> & vf2)
{    
    volField<T> result(vf1.internalField.size());
    
    result.internalField = vf1.internalField - vf2.internalField;
    
    // ToDO -> apply just if the boundary value is imposed
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        result.boundaryField_[i] = vf1.boundaryField_[i].fieldValue - vf2.boundaryField_[i].fieldValue        
    }    

    return result;
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
        // ToDO -> apply just if the boundary value is imposed
        for(unsigned int j = 0 ; j < boundaryField_[i].fieldValue.size(); j++){
            boundaryField_[i].fieldValue[j] =  boundaryField_[i].fieldValue[j] + shiftQuantity;
        }              
    }     
}

template< typename vectorType>
void volField<vectorType>::scaleField(const double scaleQuantity)
{   
    
    for(unsigned int i = 0 ; i < internalField.size(); i++){
         internalField[i] = internalField[i] * scaleQuantity;    
    }

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // ToDO -> apply just if the boundary value is imposed
        for(unsigned int j = 0 ; j < boundaryField_[i].fieldValue.size(); j++){
            boundaryField_[i].fieldValue[j] =  boundaryField_[i].fieldValue[j] * scaleQuantity;
        }              
    }     
}

// shift max field
template< typename vectorType>
void volField<vectorType>::shiftMaxField()
{
    vectorType maxFieldValue;
    // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    vectorType maxInFieldValue = maxField(internalField); 
    vectorType maxBndFieldValue = maxInFieldValue;
    vectorType maxFieldValue = maxInFieldValue;
    // ToDO -> apply just if the boundary value is imposed 
    maxBndFieldValue = maxField(boundarylField_);
    if (maxBndFieldValue > maxInFieldValue) maxFieldValue=maxBndFieldValue;
    shiftField(maxFieldValue);
}

// shift min field
template< typename vectorType>
void volField<vectorType>::shiftMinField()
{
    vectorType minFieldValue;
    // New operations defined into scalarOperations.h 
        // inline double minField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 minField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor minField(const tensorField& t1)
    vectorType minInFieldValue = minField(internalField); 
    vectorType minBndFieldValue = minInFieldValue;
    vectorType minFieldValue = minInFieldValue;
    // ToDO -> apply just if the boundary value is imposed 
    minBndFieldValue = minField(boundarylField_);
    if (minBndFieldValue > minInFieldValue) minFieldValue=minBndFieldValue;
    shiftField(minFieldValue);
}

// project field
template< typename vectorType>
void volField<vectorType>::projectField(const vector3& projectVector)
{   
    // ToDO -> apply just if the volumeField is of type vector3 
    
    vector3 normProjectVector = projectVector / mag(projectVector);
    // New operation defined into vectorOperations.h 
    // inline vectorField operator*( const scalarField& s1, const vector3& v1)
    // inline scalarField operator&(const vectorField& v1, const vector3& v2)
    internalField = (internalField & normProjectVector) * normProjectVector;

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // ToDO -> apply just if the boundary value is imposed       
        boundaryField_[i].fieldValue =  (boundaryField_[i].fieldValue & normProjectVector) * normProjectVector;                     
    }     
}