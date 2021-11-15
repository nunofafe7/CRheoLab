#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H
#include<vector>
#include<array>


typedef std::array<double, 3>   vector3;
// Tensor stored by line, in the following order T11, T12, T13, T22, T23, T33
typedef std::array<double, 6>   symmTensor;
// Tensor stored by line, in the following order T11, T12, T13, T21, T22, T23, T31, T32, T33
typedef std::array<double, 9>   tensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor>     tensorField;

#include <cmath>   
#include "fieldOperations.h"
#include "scalarOperations.h"
#include "vectorOperations.h"
#include "tensorOperations.h"
#include "symmTensorOperations.h"
#endif


