#include "ProjectPath.hpp"
#include <cassert>
// fs = std::filesystem;

// Define static members
fs::path ProjectPath::smPath    =  fs::path();
bool     ProjectPath::smIsInit  =  false;


void // static
ProjectPath:: Init(const char* argv0) {
    smPath = fs::canonical(
        fs::canonical(fs::path(argv0))
        .remove_filename()
        / ".."
        / fs::path()
    );
    
    smIsInit = true;
}


fs::path // static
ProjectPath:: Get(const char* path) {
    assert(ProjectPath::smIsInit);
    return (path == "") ? smPath : smPath / path;
}
