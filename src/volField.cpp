#include "volField.h"

// constructor
volField::volField(std::string& path, const Mesh& refMesh)
{
      // set reference mesh
      refMesh_ = &refMesh;

      // read volume field
      read(path);
}

// read header of volume field file
void volField::read(std::string& path)
{
      // read header
      readHeader(path);

      // read internal field
      internalField_.read(path);

      // read boundary field
      boundaryField_.read(path);
}

// write volume field file
void volField::write(std::string& path)
{
      // write header
      writeHeader(path);

      // write internalField
      internalField_.write(path);

      // write boundaryField
      boundaryField_.write(path);
}

// read header of volume field file
void volField::readHeader()
{

      name_ = ???;

      type_ = ???;

      dimensions_ = ???;

}

// write header of volume field file
void volField::writeHeader()
{

}

// Useful functions
