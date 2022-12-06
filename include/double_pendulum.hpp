#ifndef DOUBLE_PENDULUM_HPP
#define DOUBLE_PENDULUM_HPP

#include <SFML/Graphics.hpp>

class DoublePendulum {
public:
    DoublePendulum() = default;
    DoublePendulum(sf::Vector2<double> const &anchor, double gravity_acc,
                   double mass, double length, double angle1, double angle2);

    void update(double dt);

    sf::Vector2<double> m_anchor;
    double m_gravity_acc;
    double m_mass;
    double m_length;
    double m_angle1;
    double m_angle2;
    double m_angle1_d;
    double m_angle2_d;
};

#endif // DOUBLE_PENDULUM_HPP
