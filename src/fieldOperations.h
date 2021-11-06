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

// sum two volField type: T
template <typename T>
inline volField<T> operator+(const volField<T> & vf1, const volField<T> & vf2)
{    
    volField<T> result(internalFi1.size());
    
    result.internalField = vf1.internalField + vf2.internalField;
    

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        result.boundaryField_[i] = vf1.boundaryField_[i] + vf2.boundaryField_[i]       
    }    

    return result;
}


// ATENTION -> all next func may be declared as member functions (like readVolField.h)
// shift volFiel by a quantity
template< typename vectorType>
void volField<vectorType>::shiftField(const vectorType& shiftQuantity)
{   
    
    for(unsigned int i = 0 ; i < this->internalField.size(); i++){
         this->internalField[i] = this->internalField[i] + shiftQuantity;    
    }

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        for(unsigned int j = 0 ; j < this->boundaryField_[i].fieldValue.size(); j++){
            boundaryField_[i].fieldValue[j] =  boundaryField_[i].fieldValue[j] + shiftQuantity;
        }              
    }     
}

template< typename T>
void volField<T>::scaleField(const T& scaleQuantity)
{
    volField<T> result(this->internalField.size());
    
    result.internalField = this->internalField + scaleQuantity;    

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        result.boundaryField_[i] = this->boundaryField_[i] * scaleQuantity       
    }    

    return result;
}

// shift max field
template <typename T>
inline void shiftMaxField()
{
    // do something

}

// shift min field
template <typename T>
inline void shiftMinField()
{
    // do something
    
}

// project field
template <typename T>
inline void projectField(vector3, projectVector)
{
    switch (typeof(T)) {  // Conceptual only; not C++
    case vector3:
      // projectVector1 = unit vector of projectVector
	  // claculate internal product of this.internalField.data and projectVector1
	  // this.internalField.data = (this.internalField.data & projectVector1)* projectVector1
    break;
	default:
      // error
     break;
	this.internalField.data * projectVector;
    };    
}