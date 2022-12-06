#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "double_pendulum.hpp"
#include <SFML/System/Vector2.hpp>

class DpInputHandler {
public:
    DpInputHandler(DoublePendulum &dp);

    void press(sf::Vector2<double> const &pos);
    void release();
    void move(sf::Vector2<double> const &pos);

private:
    enum class State { FirstGrabbed, SecondGrabbed, NotInteracting };
    State m_state;
    double m_prev_angle;
    double m_dp_orig_angle1;
    double m_dp_orig_angle2;

    DoublePendulum &m_dp;
};

#endif // INPUT_HANDLER_HPP
