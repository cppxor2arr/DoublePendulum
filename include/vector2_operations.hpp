#ifndef VECTOR2_OPERATIONS_HPP
#define VECTOR2_OPERATIONS_HPP

#include <SFML/System/Vector2.hpp>

template <typename T> sf::Vector2<T> length_squared(sf::Vector2<T> const &vec);

template <typename T> sf::Vector2<T> length(sf::Vector2<T> const &vec);

template <typename T>
sf::Vector2<T> dot(sf::Vector2<T> const &vec1, sf::Vector2<T> const &vec2);

template <typename T>
sf::Vector2<T> proj(sf::Vector2<T> const &vec, sf::Vector2<T> const &onto);

#endif // VECTOR2_OPERATIONS_HPP
