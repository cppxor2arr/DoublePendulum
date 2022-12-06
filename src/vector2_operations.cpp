#include "vector2_operations.hpp"
#include <cmath>

template <typename T>
sf::Vector2<T> length_squared(sf::Vector2<T> const &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

template <typename T> sf::Vector2<T> length(sf::Vector2<T> const &vec) {
    return std::sqrt(length_squared(vec));
}

template <typename T>
sf::Vector2<T> dot(sf::Vector2<T> const &vec1, sf::Vector2<T> const &vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

template <typename T>
sf::Vector2<T> proj(sf::Vector2<T> const &vec, sf::Vector2<T> const &onto) {
    return dot(vec, onto) / onto.length_squared() * onto;
}
