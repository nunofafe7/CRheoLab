#include "Mesh.h"


Mesh::Mesh()
: nPoints_(-1),
  nFaces_(-1),
  nInteriorFaces_(-1),
  nBoundaryFaces_(-1),
  nCells_(-1),
  nPatches_(-1)
{ 
    std::cout << "I am the mesh constructor" << std::endl;
    readMesh();

}


// Function to get the current working directory of the executable file
std::string Mesh::getExecutablePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );

  std::string executablePath ( result, (count > 0) ? count : 0 );

  executablePath=executablePath.substr(0, executablePath.find_last_of("/"));

  return executablePath+"/";
}



void Mesh::readMesh()
{
    std::string filePoints (getExecutablePath()+std::string("constant/")+std::string("polyMesh/points"));
    readPoints(filePoints);

    std::string fileFaces (getExecutablePath()+std::string("constant/")+std::string("polyMesh/faces"));
    readFaces(fileFaces);

    std::string fileOwners(getExecutablePath()+std::string("constant/")+std::string("polyMesh/owner"));

    std::string  fileNeighbours(getExecutablePath()+std::string("constant/")+std::string("polyMesh/neighbour"));

    updateCellAndFaceData(fileOwners, fileNeighbours);

    std::string fileBoundary(getExecutablePath()+std::string("constant/")+std::string("polyMesh/boundary"));
    readBoundary(fileBoundary);

    std::cout << "Mesh was read successfully!" << std::endl;
}


int Mesh::getNEntitites(std::ifstream& file)
{
  int nPoints ;
  bool findNPoints (true);
  std::string line;

  while (findNPoints)
  {
    std::getline(file, line );
    if ( std::stringstream( line ) >> nPoints) 
      findNPoints=false;
  }
  return nPoints;
}

void Mesh::readPoints(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of points in file
  nPoints_ = getNEntitites(in_file);

  pointList_.resize(nPoints_);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    char c; // Variable to catch "("
    double x, y, z; // Variables to store the x,y,z position of the points
    
    for ( int i = 0; i < nPoints_; i++ )
    {
      std::getline( in_file, line );

      std::stringstream(line ) >> c >> x >> y >> z;
      
      pointList_[i]= Point(x,y,z); // Node list
    }
  }
  // Close the file
  in_file.close();

}


void Mesh::readFaces(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of faces in file
  nFaces_ = getNEntitites(in_file);

  // Resize the vectors according to the number of faces
  faceList_.resize(nFaces_);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int nPointsInFace; // catch number of points in each Face
    char c; // Variable to catch "("


    for ( int i = 0; i < nFaces_; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> nPointsInFace >> c;


            
      std::vector<Point*> listOfPoints (nPointsInFace); // array to store the list of points
      int counter(0);
      int tmp;

      while(line_2 >> tmp)
      {
        listOfPoints[counter]=&pointList_[tmp];
        counter++;
      } 


      faceList_[i]=Face(nPointsInFace,listOfPoints);
      faceList_[i].setID(i);

    }
  }
  // Close the file
  in_file.close();

}

vector<int> Mesh::readOwners(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  // String to catch the file input
  std::string line;

  // Gets number of owners in file
  int nOwners = getNEntitites(in_file);

  vector<int> tmp_OwnersList(nOwners);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int tmp(0); // catch number of owner

    for ( int i = 0; i < nOwners; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      tmp_OwnersList[i]=tmp; 
    }
  }
  // Close the file
  in_file.close();

  return tmp_OwnersList;

}

vector<int> Mesh::readNeighbours(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  // String to catch the file input
  std::string line;

  // Gets number of faces in file
  int nNeighbours = getNEntitites(in_file);

  vector<int> tmp_NeighboursList(nNeighbours);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int tmp(0); // catch number of cell neighbour

    for ( int i = 0; i < nNeighbours; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      tmp_NeighboursList[i]=tmp;
    }
  }
  // Close the file
  in_file.close();

  return tmp_NeighboursList;
}


void Mesh::updateCellAndFaceData(std::string pathOwners, std::string pathNeighbours)
{
  // Reads owners
  const vector<int> ownersList = readOwners(pathOwners);
  
  // Reads neighbours
  const vector<int> neighboursList = readNeighbours(pathNeighbours);
  
  // Updates the number of interior faces and boundary faces
  nInteriorFaces_ = neighboursList.size();
  nBoundaryFaces_ = nFaces_ - nInteriorFaces_;
  
  // Updates the number of cells in the mesh
  nCells_ = *std::max_element(std::begin(neighboursList), std::end(neighboursList)) + 1 ;
  
  // Updates the size of cellList_
  cellList_.resize(nCells_);

  // Gets faces that constitute each cell
  vector<vector<Face*> > cellFaces(nCells_);

  // Loops over the interior faces
  for( int i = 0 ; i < nInteriorFaces_ ; i++)
  {    
    int tmp_owner = ownersList[i];
    int tmp_neighbour = neighboursList[i];

    cellFaces[tmp_owner].push_back(&faceList_[i]);
    cellFaces[tmp_neighbour].push_back(&faceList_[i]);

  }

  // Loops over the boundary faces
  for (int i = nInteriorFaces_; i < nFaces_; i++)
  {
    int tmp_owner = ownersList[i];
    
    cellFaces[tmp_owner].push_back(&faceList_[i]);
  }
  
  // Updates the vector<Face*> in for each cell
  for(unsigned int cellI = 0; cellI<cellList_.size(); cellI++)
  {
    cellList_[cellI].setCellFaces(cellFaces[cellI]);
    cellList_[cellI].setCellID(cellI);
  }

  // Assign the pointers to cell owners and neighbours for each face
  // Loops over the interior faces
  for(unsigned int faceI = 0; faceI< nFaces_; faceI++)
  {
    int tmp_owner = ownersList[faceI];
    faceList_[faceI].setOwner( cellList_[tmp_owner]  );

    if (faceI < nInteriorFaces_)
    {
      int tmp_neighbour = neighboursList[faceI];
      faceList_[faceI].setNeighbour( cellList_[tmp_neighbour]  );
    }


    // Update face parameters
    faceList_[faceI].computeArea();
    faceList_[faceI].computeCenterOfMass();
    faceList_[faceI].computeAreaVector();
    faceList_[faceI].computeWeightingFactor();
  }

}




void Mesh::readBoundary(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;   
  }

  std::string line;

  // Booleans to check file reading
  bool endInnerLoop = false;
  bool firstCurly = false;
  bool secondCurly = false;

  bool checkBoundaryName = false;
  bool checkType = false;
  bool checkNFaces = false;
  bool checkStartFace = false;

  std::string words;
  std::string words2;
  int values(-1);
  int countCurly (0);

  std::string name;
  std::string type;

  int nFaces;
  int startFace;

  nPatches_ = getNEntitites(in_file);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    for ( int i = 0; i < nPatches_; i++ )
    {
      endInnerLoop = false;

      while(!endInnerLoop && !in_file.eof())
      {
        std::getline( in_file, line );
        std::stringstream line_2(line); 

        // Extracts word from line
        line_2 >> words;

        if (words.at(0) == '{')
        {
          firstCurly = true;
          countCurly++;
        }

        if (firstCurly && words.back() == '}' && countCurly < 2)
        {
          secondCurly = true;
          countCurly = 0;
        }
        
        if (firstCurly && secondCurly)
          endInnerLoop = true;

        if(!checkBoundaryName && !firstCurly)
        {
           name = words;
           checkBoundaryName = true;
        }

        if(words == "type" && (line_2 >> words2) && words2.back() == ';' )
        {
           type = words2.substr(0, words2.size()-1);
           checkType = true;
           words2.clear();
        }

        if(words == "nFaces" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';') )
        {
           nFaces = values;
           checkNFaces = true;
           words2.clear();
        }

        if(words == "startFace" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';'))
        {
           startFace = values;
           checkStartFace = true;
        }

        // If the stringstream reaches the end of file some parameters are missing. 
        // Implement later
        if (endInnerLoop)
        {
            if ( !(checkBoundaryName  && checkType && checkNFaces && checkStartFace) )
            {
                throw  std::runtime_error("Some error in the boundaries");
            } 
        }

        if (in_file.eof() && !endInnerLoop)
        {
              throw  std::runtime_error("End of file!! You probably have problems with parentheses");
              
        }  
      }

      patchList_.push_back(Patch(name,type, nFaces,startFace)); //add a Patch object to the list

      checkBoundaryName = false;
      checkType = false;
      checkNFaces = false;
      checkStartFace = false;

      firstCurly = false;
      secondCurly = false;


    }
  }
  // Close the file
  in_file.close();


}
