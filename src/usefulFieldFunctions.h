////////////////////////////////////////
// volField usefull functions add fields
////////////////////////////////////////

// sum two volFields
template <typename T>
inline volField<T> operator+(const volField<T> & vf1, const volField<T> & vf2)
{    
    volField<T> result(vf1.internalField.size());
    
    result.internalField = vf1.internalField + vf2.internalField;
    
    if (boundaryField_[i].valImposed) {
        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
            result.boundaryField_[i] = vf1.boundaryField_[i].fieldValue + vf2.boundaryField_[i].fieldValue        
        }  
    }

    return result;
}

// subtraction of two volFields
template <typename T>
inline volField<T> operator-(const volField<T> & vf1, const volField<T> & vf2)
{    
    volField<T> result(vf1.internalField.size());
    
    result.internalField = vf1.internalField - vf2.internalField;
    
    if (boundaryField_[i].valImposed) {
        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
            result.boundaryField_[i] = vf1.boundaryField_[i].fieldValue - vf2.boundaryField_[i].fieldValue        
        }    
    }
    return result;
}

#endif
