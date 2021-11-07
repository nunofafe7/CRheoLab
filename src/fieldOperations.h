#ifndef FIELDOPERATIONS_H
#define FIELDOPERATIONS_H

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
        result.boundaryField_[i] = vf1.boundaryField_[i] + vf2.boundaryField_[i]       
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
        result.boundaryField_[i] = vf1.boundaryField_[i] - vf2.boundaryField_[i]       
    }    

    return result;
}

// ATENTION -> all next func may be declared as member functions (like readVolField.h)

// Shift volFiel by a quantity, apply just if the boundary value is imposed
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

// Scale volFiel by a quantity, apply just if the boundary value is imposed
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
    double maxField;
    // New operation defined into scalarOperations.h 
    // inline double maxScalarField(const scalarField& v1)
    // inline scalarField mag(const scalarField& v1)    
    // ToDo create mag function for tensor field in tensor operations (do it by calculating invariants of the tensor, I1, I2, I3, and magnitude is I2)
    // if type or define mag func for scalar    
    maxField = maxScalarField(mag(internalField)) // scalar nao correr, vector ok, tensor magnitude not defined yet
    boundaryField_));
    shiftField(max);
}

// shift min field
template< typename vectorType>
void volField<vectorType>::shiftMinField()
{
    // New operation defined into scalarOperations.h 
    // inline double minScalarField(const scalarField& v1)
    vectorType min = minScalarField(internalField, boundaryField_);
    shiftField(min);
}

// project field
template< typename vectorType>
void volField<vectorType>::projectField(const vector3& projectVector)
{   
    
    vector3 normProjectVector = projectVector / mag(projectVector);
    // New operation defined into vectorOperation.h 
    // inline vectorField operator*( const scalarField& s1, const vector3& v1)
    // inline scalarField operator&(const vectorField& v1, const vector3& v2)
    internalField = (internalField & normProjectVector) * normProjectVector;

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // ToDO -> apply just if the boundary value is imposed       
        boundaryField_[i].fieldValue =  (boundaryField_[i].fieldValue & normProjectVector) * normProjectVector;                     
    }     
}