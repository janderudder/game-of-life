#include "ProjectPath.hpp"

fs::path ProjectPath::smPath = fs::path();


void // static
ProjectPath:: Init(const char* argv0) {
    smPath = fs::canonical(
        fs::canonical(fs::path(argv0))
        .remove_filename()
        / ".."
        / fs::path()
    );
}


fs::path // static
ProjectPath:: Get(const char* path) {
    return (path == "") ? smPath : smPath / path;
}
