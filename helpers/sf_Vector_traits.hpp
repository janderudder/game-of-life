#ifndef SF_VECTOR_TRAIT_HPP
#define SF_VECTOR_TRAIT_HPP
#include <SFML/System.hpp>
#include <utility>
#include <cmath>
#include <cstdio>
#include <string>

/**
 * Print integer 2D vector
 */
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value,
int> printVector(const sf::Vector2<T>& v) {
    return std::printf("%s, %s", std::to_string(v.x).c_str(), std::to_string(v.y).c_str());
}

/**
 * Print real 2D vector
 */
template <typename T>
typename std::enable_if_t<std::is_floating_point<T>::value,
int> printVector(const sf::Vector2<T>& v) {
    return std::printf(std::floor(v.x) == v.x ? "%.1f, " : "%g, ", v.x)
        + std::printf(std::floor(v.y) == v.y ? "%.1f" : "%g", v.y);
}

/**
 * Make a 2D vector from a single numeric value
 */
template <typename T>
sf::Vector2<T> makeVector(const T& n) {
    return sf::Vector2<T>(n, n);
}

/**
 * Make a vector of a certain type from a single numeric value of another tyoe
 */
template <typename T, typename U>
sf::Vector2<T> makeVector(const U& n) {
    return sf::Vector2<T>( static_cast<T>(n), static_cast<T>(n) );
}

/**
 * Copy a vector and invert the sign
 */
template <typename T>
typename std::enable_if<std::is_signed<T>::value,
sf::Vector2<T>> makeOppositeVector(const sf::Vector2<T>& v) {
    return {-v.x, -v.y};
}

/**
 * Make a vector from a single value, invert the value's sign
 */
template <typename T>
sf::Vector2<T> makeOppositeVector(const T& n) {
    return sf::Vector2<T>(-n, -n);
}

/**
 * Make a vector of a certain type from a single value
 * of another type, invert the value's sign
 */
template <typename T, typename U>
sf::Vector2<T> makeOppositeVector(const U& n) {
    return sf::Vector2<T>( static_cast<T>(-n), static_cast<T>(-n) );
}

/**
 * Copy the vector and invert the values (1/v)
 */
template <typename T>
typename std::enable_if_t<std::is_floating_point<T>::value, 
sf::Vector2<T>> makeInverseVector(const sf::Vector2<T>& v) {
    return { (T)(1) / v.x, (T)(1) / v.y };
}

/**
 * Make a vector from the inverse of a single value
 */
template <typename T>
typename std::enable_if_t<std::is_floating_point<T>::value, 
sf::Vector2<T>> makeInverseVector(const T& n) {
    auto value = (T)(1) / n;
    return sf::Vector2<T>(value, value);
}

template <typename T, typename U>
typename std::enable_if_t<std::is_floating_point<T>::value && std::is_floating_point<U>::value, 
sf::Vector2<T>> makeInverseVector(const U& n) {
    auto value = (T)(1) / static_cast<T>(n);
    return sf::Vector2<T>(value, value);
}


template <typename T, typename U>
double distanceBetween(const sf::Vector2<T>& p1, const sf::Vector2<U>& p2)
{
    return std::sqrt(std::pow(static_cast<double>(p2.x) - static_cast<double>(p1.x), 2) 
                    + std::pow(static_cast<double>(p2.y) - static_cast<double>(p1.y), 2));
}

template <typename T, typename U>
sf::Vector2<T> operator / (const sf::Vector2<T>& v1, const sf::Vector2<U>& v2) {
    return sf::Vector2<T>(v1.x / static_cast<T>(v2.x), v1.y / static_cast<T>(v2.y));
}

template <typename T, typename U>
sf::Vector2<T> operator * (const sf::Vector2<T>& v1, const sf::Vector2<U>& v2) {
    return sf::Vector2<T>(static_cast<T>(v1.x) * static_cast<T>(v2.x), static_cast<T>(v1.y) * static_cast<T>(v2.y));
}


template <typename T, typename U>
sf::Vector2<T> operator * (const sf::Vector2<T>& v, const U& f) {
    return { v.x * f, v.y * f};
}


template <typename T, typename U>
sf::Vector2<T> operator / (const sf::Vector2<T>& v, const U& f) {
    if ( sizeof(T) <= sizeof(U) )
        return { v.x / static_cast<T>(f), v.y / static_cast<T>(f) };
    else
        return { static_cast<U>(v.x) / f, static_cast<U>(v.y) / f };
}


template <typename T>
sf::Vector2<T> operator + (const sf::Vector2<T> v, const T& n) {
    return sf::Vector2<T>(v.x + n, v.y + n);
}

template <typename T, typename N>
sf::Vector2<T> operator + (const sf::Vector2<T> v, const N& n) {
    return sf::Vector2<T>(v.x + static_cast<T>(n), v.y + static_cast<T>(n));
}


#endif // SF_VECTOR_TRAIT_HPP
