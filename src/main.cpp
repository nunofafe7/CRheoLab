#include <iostream>
#include "Mesh.h"
#include "IODictionaryI.h"
#include "volField.h"

//  void write_csv(std::string filename, std::string , std::vector<double> );

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << std::endl;
    }
    os << "]\n";
    return os;
}

using namespace std;

int main()
{
        
    std::cout << "Current path is : " << getExecutablePath() << std::endl;

   checkCaseStructure();
    
    RunTime time;

    Mesh polyMesh;
    
    
    volField<double> p ("p", polyMesh, time);
    //volField<double> p1 ("p1", polyMesh, time);
    //volField<double> resultp ("resultp", polyMesh, time);

    //volField<vector3> U ("U", polyMesh, time);
    //volField<vector3> U1 ("U1", polyMesh, time);   
    //volField<vector3> resultU ("resultU", polyMesh, time);

    

    // shift field
    //p.shiftField(5);

    // scale field
    //p.scaleField(10);

    // sum two scalarfields
    //resultp = p+p1;
    //resultU = U+U1;
   // volField<vectorField> U ("U", polyMesh);

    std::cout << "Current path is : " << time.Path() << std::endl;

    std::string tst = "banana";
    time.setFolder(tst);

    std::cout << "Current path is : " << time.Path() << std::endl;

    //volField<vectorField> U("U", polyMesh, time);

    return 0;
}


