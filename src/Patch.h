#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <cstring>

class Patch
{
    public:
        // Constructor
        Patch(std::string, std::string, int, int);

        // Destructor
        virtual ~Patch(){};

        const std::string& name() const;

        int nFaces() const;

        int startFace_;
        
        int nFaces_;

    protected:

    private:
        std::string name_;
        std::string type_;

};

#endif // PATCH_H
