#include "volField.h"

// Constructor
template <typename T>
volField<T>::volField(std::string path, std::string filename, const Mesh& refMesh)
{
      // Set path
      path_ = path;

      // Set reference mesh
      refMesh_ = &refMesh;
      
      // initialize IODictionary
      dict_ = IODictionary (path, fileName);

      // Read volume field
      read(path, filename);
}

// Read header of volume field file
template <typename T>
void volField<T>::read(std::string path, std::string filename)
{
      // Read header
      dict_.readHeader(path, filename);
   
      // Read dimensions
      readDimensions(path, filename);

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
      dict_.writeHeader(path, filename);
      
      // Write Dimensions
      writeDimensions(path, fileName);

      // Write internalField
      internalField_.write(path, filename);

      // Write boundaryField
      boundaryField_.write(path, filename);
}

//write dimensions
template <typename T>
void volField<T>::writeDimensions(std::string path, std::string filename)
 {
     if(dimensions_.size() == 7){
      std::cout<<"dimensions\t[";
      for (int i = 0; i < 7; i++){
        std::cout << dimensions_[i];
        if(i<6) std::cout<< ' ';
      }
      std::cout<<"];\n\n"<<std::endl;

    }else{
      std::cout<<"not valid data!"<<std::endl;
    }
  }

// Useful functions
