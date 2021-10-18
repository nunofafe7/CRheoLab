#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "Mesh.h"
//#include "internalField.h"
//#include "boundaryField.h"

class internalField;
class boundaryField;

class volField<type>
{
    public:

        // Constructor
        volField();

        // Destructor
        virtual ~volField(){};

        // read/write functions
        void read();
        void write();
        void readHeader();
        void writeHeader();

        // Useful functions


    protected:

    private:

        // mesh associated to the volume field
        Mesh* refMesh_;

        // name of volume field
        std::string name_;

        // type of data (scalar, vector or tensor)
        std::string type_;

        // dimension of volume field
        std::vector<int> dimensions_(7);

        // internal field
        internalField<type> internalField_;

        // boundary field
        boundaryField<type> boundaryField_;

};

#endif // VOLFIELD_H
