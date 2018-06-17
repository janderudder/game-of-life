/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include <utility>
#include <memory>
#include <string>

/**
 * The Resource type
 */
template <class T>
using Resource = std::shared_ptr<T>;

/**
 * Factory function
 */
template <class T, class... Args_T>
Resource<T> make_resource(Args_T&&... args) {
    return std::move(std::make_shared<T>(std::forward<Args_T>(args)...));
}

template <class T>
Resource<T> make_resource(const char* filename) {
    auto resource = std::make_shared<T>();
    resource->loadFromFile(filename);
    return resource;
}

template <class T>
Resource<T> make_resource(const std::string& filename) {
    auto resource = std::make_shared<T>();
    resource->loadFromFile(filename);
    return resource;
}

#endif // RESOURCE_HPP
