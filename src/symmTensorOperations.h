#ifndef SYMMTENSOROPERATIONS_H
#define SYMMTENSOROPERATIONS_H

// Output vectorField to screen
inline std::ostream& operator<<(std::ostream& os, const symmTensorField& t)
{
    os << "[" << std::endl;
    
    for (unsigned int i = 0; i < t.size(); ++i) {
        
        os << "\t";

        os << "[ ";

        for (unsigned int j=0; j< t[i].size(); j++)
        {
            os<< t[i][j] << " ";
        }
        os << "]" << std::endl;
    }

    os << "]\n";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symmTensor& t)
{
    os << "[ " ;
    
    for (unsigned int i = 0; i < t.size(); ++i)
    {

        os<< t[i] << " ";
    }

    os << " ]\n";
    return os;
}


// Math Operations

// At the symmTensor level

//storage 0-T11, 1-T12, 2-T13, 3-T22, 4-T23, 5-T33
// First Invariant T11+T22+T33
inline double I1(const symmTensor& t)
{
   double result;

   result= t[0]+t[3]+t[5];

   return result;
}
//storage 0-T11, 1-T12, 2-T13, 3-T22, 4-T23, 5-T33
// Second Invariant T11*T22+T11*T33+T22*T33-T12*T21-T23*T32-T13*T31
inline double I2(const symmTensor& t)
{
   double result;

   result= t[0]*t[3]+t[0]*t[6]+t[3]*t[5]-t[1]*t[1]-t[4]*t[4]-t[2]*t[2];

   return result;
}
//storage 0-T11, 1-T12, 2-T13, 3-T22, 4-T23, 5-T33
// Third Invariant -T13*T22*T31+T12*T23*T31+T13*T21*T32-T11*T23*T32-T12*T21*T33+T11*T22*T33
inline double I3(const symmTensor& t)
{
   double result;

   result= -t[2]*t[3]*t[2] + t[1]*t[4]*t[2] + t[2]*t[1]*t[4] - t[0]*t[4]*t[4] - t[1]*t[1]*t[6] + t[0]*t[3]*t[6];

   return result;
}



// Larger than
inline bool operator>(const symmTensor& t1, const symmTensor& t2)
{
   return (I2(t1)>I2(t2));
}

// Smaller than
inline bool operator<(const symmTensor& t1, const symmTensor& t2)
{
   return (I2(t1)<I2(t2));
}

// Summation
inline symmTensor operator+(const symmTensor& t1, const symmTensor& t2)
{
   symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] + t2[i];
    }

   return result;
}


// Subtraction
inline symmTensor operator-(const symmTensor& t1, const symmTensor& t2)
{
   symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] - t2[i];
    }

   return result;
}

// scalar multiplication
inline symmTensor operator*(const double& d1, const symmTensor& t1)
{
    symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

   return result;
}

inline symmTensor operator*(const symmTensor& t1,const double& d1)
{
    symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }
   return result;
}



// scalar division
inline symmTensor operator/(const symmTensor& t1, const double& d1)
{
    symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

   return result;
}

inline symmTensor  operator/(const double& d1, const symmTensor& t1)
{
    symmTensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }
   return result;
}


//storage 0-T11, 1-T12, 2-T13, 3-T22, 4-T23, 5-T33
// symmTensor vector3 product
vector3 operator&(const symmTensor& t1, const vector3& v1)
{  
   vector3 result;

   result[0] = t1[0]*v1[0]+ t1[1]*v1[1]+t1[2]*v1[2];
   result[1] = t1[1]*v1[0]+ t1[3]*v1[1]+t1[4]*v1[2];
   result[2] = t1[2]*v1[0]+ t1[4]*v1[1]+t1[5]*v1[2];

   return result;
}

// At the field level


inline symmTensorField operator*(const symmTensorField& t1, const double& d1)
{
    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline symmTensorField operator*( const double& d1, const symmTensorField& t1)
{

    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline symmTensorField operator*( const scalarField& s1, const symmTensorField& t1)
{

    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * s1[i];
    }

    return result;
}

inline symmTensorField operator/(const symmTensorField& t1, const double& d1)
{

    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

    return result;
}

inline symmTensorField operator/(const double& d1, const symmTensorField& t1)
{
    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }

    return result;
}

inline symmTensorField operator/(const symmTensorField& t1, const scalarField& s1)
{

    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / s1[i];
    }

    return result;
}


inline symmTensorField operator/(const scalarField& s1, const symmTensorField& t1)
{
    symmTensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = s1[i]/t1[i];
    }

    return result;
}


//return the maximum of the symmTensorField
// define new functions in symmTensorOperations.h
// inline bool operator>(const symmTensor& t1, const symmTensor& t2)

inline symmTensor maxField(const symmTensorField& t1)
{   
   
   symmTensor result = t1[0];
   
   for(unsigned int i = 1 ; i < t1.size(); i++)
   {
        if (t1[i] > result) result=t1[i];
   }
   return result;
}

//return the minimum of the symmTensorField
// define new functions in symmTensorOperations.h
// inline bool operator<(const symmTensor& t1, const symmTensor& t2)
inline symmTensor minField(const symmTensorField& t1)
{   
   
   symmTensor result = t1[0];
   
   for(unsigned int i = 1 ; i < t1.size(); i++)
   {
        if (t1[i] < result) result=t1[i];
   }
   return result;
}

#endif //SYMMTENSOROPERATIONS_H
