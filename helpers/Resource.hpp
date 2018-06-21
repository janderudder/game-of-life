/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef HELPER_RESOURCE_HPP
#define HELPER_RESOURCE_HPP
#include <utility>
#include <memory>
#include <string>
#include <filesystem>

/**
 * The Resource type
 */
template <class T>
using Resource = std::shared_ptr<T>;

/**
 * Factory functions
 */
template <class T, class... Args_T>
Resource<T> makeResource(Args_T&&... args) {
    return std::move(std::make_shared<T>(std::forward<Args_T>(args)...));
}


template <class T>
Resource<T> makeResource(std::filesystem::path&& filePath) {
    auto resource = std::make_shared<T>();
    resource->loadFromFile(filePath.generic_string());
    return resource;
}


template <class T>
Resource<T> makeResource(const char* filename) {
    auto resource = std::make_shared<T>();
    resource->loadFromFile(filename);
    return resource;
}


template <class T>
Resource<T> makeResource(const std::string& filename) {
    auto resource = std::make_shared<T>();
    resource->loadFromFile(filename);
    return resource;
}


#endif // HELPER_RESOURCE_HPP
