#ifndef VOLFIELDOPERATIONS_H
#define VOLFIELDOPERATIONS_H

//Sumation
template< typename vectorType>
volField<vectorType> operator+(const volField<vectorType> & volF, const vectorType v2)
{
    //Create a copy of volF
    volField<vectorType> resVolField(volF);

    resVolField.fieldName_=resVolField.fieldName_+"shiftedSum";

    for(unsigned int i = 0 ; i < resVolField.internalField.size(); i++){
         resVolField.internalField[i] = resVolField.internalField[i] + v2;    
    }
    
    for(unsigned int i = 0 ; i < resVolField.mesh_.nPatches_; i++){
        if (resVolField.boundaryField_[i].valImposed) {
            for(unsigned int j = 0 ; j < resVolField.boundaryField_[i].fieldValue.size(); j++){
                resVolField.boundaryField_[i].fieldValue[j] =  resVolField.boundaryField_[i].fieldValue[j] + v2;
            }              
        }
    }

    return resVolField;
}


//Subtraction
template< typename vectorType>
volField<vectorType> operator-(const volField<vectorType> & volF, const vectorType v2)
{
    //Create a copy of volF
    volField<vectorType> resVolField(volF);

    resVolField.fieldName_=resVolField.fieldName_+"shiftedSub";

    for(unsigned int i = 0 ; i < resVolField.internalField.size(); i++){
         resVolField.internalField[i] = resVolField.internalField[i] - v2;    
    }
    
    for(unsigned int i = 0 ; i < resVolField.mesh_.nPatches_; i++){
        if (resVolField.boundaryField_[i].valImposed) {
            for(unsigned int j = 0 ; j < resVolField.boundaryField_[i].fieldValue.size(); j++){
                resVolField.boundaryField_[i].fieldValue[j] =  resVolField.boundaryField_[i].fieldValue[j] - v2;
            }              
        }
    }

    return resVolField;
}

//Scale
template< typename vectorType>
volField<vectorType> operator*(const volField<vectorType> & volF, const double scaleFactor)
{
    //Create a copy of volF
    volField<vectorType> resVolField(volF);

    resVolField.fieldName_=resVolField.fieldName_+"scaled";

    for(unsigned int i = 0 ; i < resVolField.internalField.size(); i++){
         resVolField.internalField[i] = resVolField.internalField[i]*scaleFactor;    
    }
    
    for(unsigned int i = 0 ; i < resVolField.mesh_.nPatches_; i++){
        if (resVolField.boundaryField_[i].valImposed) {
            for(unsigned int j = 0 ; j < resVolField.boundaryField_[i].fieldValue.size(); j++){
                resVolField.boundaryField_[i].fieldValue[j] =  resVolField.boundaryField_[i].fieldValue[j]*scaleFactor;
            }              
        }
    }

    return resVolField;
}

#endif