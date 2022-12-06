#include "double_pendulum.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

DoublePendulum::DoublePendulum(sf::Vector2<double> const &anchor,
                               double const gravity_acc, double const mass,
                               double const length, double const angle1,
                               double const angle2)
    : m_anchor(anchor), m_gravity_acc(gravity_acc), m_mass(mass),
      m_length(length), m_angle1(angle1), m_angle2(angle2), m_angle1_d(0.0),
      m_angle2_d(0.0) {
}

void DoublePendulum::update(double const dt) {
    double const angle1_dd =
        (-m_gravity_acc * (2.0 * m_mass + m_mass) * std::sin(m_angle1) -
         m_mass * m_gravity_acc * std::sin(m_angle1 - 2.0 * m_angle2) -
         2.0 * std::sin(m_angle1 - m_angle2) * m_mass *
             (m_angle2_d * m_angle2_d * m_length +
              m_angle1_d * m_angle1_d * m_length *
                  std::cos(m_angle1 - m_angle2))) /
        (m_length * (2.0 * m_mass + m_mass -
                     m_mass * std::cos(2.0 * m_angle1 - 2.0 * m_angle2)));
    double const angle2_dd =
        (2.0 * std::sin(m_angle1 - m_angle2) *
         (m_angle1_d * m_angle1_d * m_length * (m_mass + m_mass) +
          m_gravity_acc * (m_mass + m_mass) * std::cos(m_angle1) +
          m_angle2_d * m_angle2_d * m_length * m_mass *
              std::cos(m_angle1 - m_angle2))) /
        (m_length * (2.0 * m_mass + m_mass -
                     m_mass * std::cos(2.0 * m_angle2 - 2.0 * m_angle2)));

    m_angle1_d += angle1_dd * dt;
    m_angle2_d += angle2_dd * dt;

    m_angle1 += m_angle1_d * dt;
    m_angle2 += m_angle2_d * dt;
}
