#ifndef PROJECT_PATH_HPP
#define PROJECT_PATH_HPP
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

class ProjectPath
{
    static fs::path  smPath;
    static bool      smIsInit;

public:
    ProjectPath() = delete;

    static void      Init(const char* argv0);
    static fs::path  Get(const char* subPath = "");

};


#endif // PROJECT_PATH_HPP
