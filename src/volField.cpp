#include "volField.h"

// Constructor
template <typename T>
volField<T>::volField(std::string path, std::string filename, const Mesh& refMesh)
{
      // Set path
      path_ = path;

      // Set reference mesh
      refMesh_ = &refMesh;

      // Read volume field
      read(path, filename);
}

// Read header of volume field file
template <typename T>
void volField<T>::read(std::string path, std::string filename)
{
      // Read header
      readHeader(path, filename);

      // Read internal field
      internalField_.read(path, filename);

      // Read boundary field
      boundaryField_.read(path, filename);
}

// Write volume field file
template <typename T>
void volField<T>::write(std::string path, std::string filename)
{
      // Write header
      writeHeader(path, filename);

      // Write internalField
      internalField_.write(path, filename);

      // Write boundaryField
      boundaryField_.write(path, filename);
}

// Read header of volume field file
template <typename T>
void volField<T>::readHeader(std::string path, std::string filename)
{
      // TO DO: read header to get name, type and dimensions of volume field
      name_ = ???;
      type_ = ???;
      dimensions_ = ???;
}

// Write header of volume field file
template <typename T>
void volField<T>::writeHeader(std::string path, std::string filename)
{
      // TO DO: write back header to a file    
    std::cout<<'{'<<std::endl;
    std::cout<<"typeName"<<std::endl;
    std::cout<<'\t'<< typeName.name()<<std::endl;
    std::cout<<"\t;"<<std::endl;
}

// Useful functions
