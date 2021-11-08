#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "Mesh.h"
//#include "internalField.h"
//#include "boundaryField.h"

class internalField;
class boundaryField;

// typename should be scalar, vector3 or tensor
template <typename T>
class volField
{
    public:

        // Constructor
        volField(std::string,std::string,const Mesh&);

        // Destructor
        virtual ~volField(){};

        // Getters
        const Mesh* getRefMesh() const;
        const std::string& getName() const;
        const std::string& getPath() const;
        const std::string& getType() const;
        const std::vector<int>& getDimensions() const;
        const internalField<T>* getInternalField() const;
        const boundaryField<T>* getBoundaryField() const;

        // Read/write functions
        void read(std::string, std::string);
        void write(std::string, std::string);
        void readHeader(std::string, std::string);
        void writeHeader(std::string, std::string);
        void writeDimensions(std::string, std::string);

        // Useful functions
        // ???

    protected:

    private:

        // Reference mesh
        Mesh* refMesh_;

        // Path
        std::string path_;

        // Name
        std::string name_;

        // Type of data (scalar, vector or tensor)
        std::string type_;

        // Dimensions
        std::vector<int> dimensions_(7);

        // Internal field
        internalField<T> internalField_;

        // Boundary field
        boundaryField<T> boundaryField_;

};

#endif // VOLFIELD_H
