#ifndef TENSOROPERATIONS_H
#define TENSOROPERATIONS_H

// Output vectorField to screen
inline std::ostream& operator<<(std::ostream& os, const tensorField& t)
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

inline std::ostream& operator<<(std::ostream& os, const tensor& t)
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

// At the tensor level

// First Invariant T11+T22+T33
inline double I1(const tensor& t)
{
   double result;

   result= t[0]+t[4]+t[8];

   return result;
}

// Second Invariant T11*T22+T11*T33+T22*T33-T12*T21-T23*T32-T13*T31
inline double I2(const tensor& t)
{
   double result;

   result= t[0]*t[4]+t[0]*t[8]+t[8]*t[4]-t[1]*t[3]-t[5]*t[7]-t[2]*t[6];

   return result;
}

// Third Invariant -T13*T22*T31+T12*T23*T31+T13*T21*T32-T11*T23*T32-T12*T21*T33+T11*T22*T33
inline double I3(const tensor& t)
{
   double result;

   result= -t[2]*t[4]*t[6] + t[1]*t[5]*t[6] + t[2]*t[3]*t[7] - t[0]*t[5]*t[7] - t[1]*t[3]*t[8] + t[0]*t[4]*t[8];

   return result;
}



// Larger than
inline bool operator>(const tensor& t1, const tensor& t2)
{
   return (I2(t1)>I2(t2));
}

// Smaller than
inline bool operator<(const tensor& t1, const tensor& t2)
{
   return (I2(t1)<I2(t2));
}

// Summation
inline tensor operator+(const tensor& t1, const tensor& t2)
{
   tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] + t2[i];
    }

   return result;
}


// Subtraction
inline tensor operator-(const tensor& t1, const tensor& t2)
{
   tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] - t2[i];
    }

   return result;
}

// scalar multiplication
inline tensor operator*(const double& d1, const tensor& t1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

   return result;
}

inline tensor operator*(const tensor& t1,const double& d1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }
   return result;
}



// scalar division
inline tensor operator/(const tensor& t1, const double& d1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

   return result;
}

inline tensor  operator/(const double& d1, const tensor& t1)
{
    tensor result;

    for (unsigned int i = 0; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }
   return result;
}


/*//inner product / dot product
tensor operator&(const tensor& t1, const vector3& v1)
{  
   vector3 result;

    result = ( t1[0]*v1[0]+ 
                  
            )

   return result;
}
*/

// At the field level


inline tensorField operator*(const tensorField& t1, const double& d1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline tensorField operator*( const double& d1, const tensorField& t1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * d1;
    }

    return result;
}

inline tensorField operator*( const scalarField& s1, const tensorField& t1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] * s1[i];
    }

    return result;
}

inline tensorField operator/(const tensorField& t1, const double& d1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / d1;
    }

    return result;
}

inline tensorField operator/(const double& d1, const tensorField& t1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = d1 / t1[i];
    }

    return result;
}

inline tensorField operator/(const tensorField& t1, const scalarField& s1)
{

    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = t1[i] / s1[i];
    }

    return result;
}


inline tensorField operator/(const scalarField& s1, const tensorField& t1)
{
    tensorField result(t1.size());

    for(unsigned int i = 0 ; i < t1.size(); i++)
    {
        result[i] = s1[i]/t1[i];
    }

    return result;
}


//return the maximum of the tensorField
// define new functions in tensorOperations.h
// inline bool operator>(const tensor& t1, const tensor& t2)

inline tensor maxField(const tensorField& t1)
{   
   
   tensor result = t1[0];
   
   for(unsigned int i = 1 ; i < t1.size(); i++)
   {
        if (t1[i] > result) result=t1[i];
   }
   return result;
}

//return the minimum of the tensorField
// define new functions in tensorOperations.h
// inline bool operator<(const tensor& t1, const tensor& t2)
inline tensor minField(const tensorField& t1)
{   
   
   tensor result = t1[0];
   
   for(unsigned int i = 1 ; i < t1.size(); i++)
   {
        if (t1[i] < result) result=t1[i];
   }
   return result;
}

#endif
