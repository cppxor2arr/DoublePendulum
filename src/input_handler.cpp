#include "input_handler.hpp"
#include "constants.hpp"
#include <cmath>

DpInputHandler::DpInputHandler(DoublePendulum &dp)
    : m_state(State::NotInteracting), m_dp(dp) {
}

void DpInputHandler::press(sf::Vector2<double> const &pos) {
    auto const x1 =
        m_dp.m_anchor.x + m_dp.m_length * std::cos(m_dp.m_angle1 + PI / 2.0);
    auto const y1 =
        m_dp.m_anchor.y + m_dp.m_length * std::sin(m_dp.m_angle1 + PI / 2.0);
    auto const x2 = x1 + m_dp.m_length * std::cos(m_dp.m_angle2 + PI / 2.0);
    auto const y2 = y1 + m_dp.m_length * std::sin(m_dp.m_angle2 + PI / 2.0);

    auto const dist1_squared =
        std::pow(pos.x - x1, 2) + std::pow(pos.y - y1, 2);
    auto const dist2_squared =
        std::pow(pos.x - x2, 2) + std::pow(pos.y - y2, 2);

    if (dist1_squared < dist2_squared) {
        m_state = State::FirstGrabbed;
        m_prev_angle =
            std::atan2(pos.y - m_dp.m_anchor.y, pos.x - m_dp.m_anchor.x);
    } else {
        m_state = State::SecondGrabbed;
        m_prev_angle = std::atan2(pos.y - y1, pos.x - x1);
    }

    m_dp_orig_angle1 = m_dp.m_angle1;
    m_dp_orig_angle2 = m_dp.m_angle2;
}

void DpInputHandler::release() {
    m_state = State::NotInteracting;
}

void DpInputHandler::move(sf::Vector2<double> const &pos) {
    auto const x1 = m_dp.m_anchor.x;
    auto const y1 = m_dp.m_anchor.y;
    auto const x2 = x1 + m_dp.m_length * std::cos(m_dp.m_angle1 + PI / 2.0);
    auto const y2 = y1 + m_dp.m_length * std::sin(m_dp.m_angle1 + PI / 2.0);

    switch (m_state) {
    case State::FirstGrabbed: {
        auto const curr_angle = std::atan2(pos.y - y1, pos.x - x1);
        auto const delta_angle = curr_angle - m_prev_angle;
        m_dp.m_angle1 = m_dp_orig_angle1 + delta_angle;
        m_dp.m_angle2 = m_dp_orig_angle2 + delta_angle;
        break;
    }
    case State::SecondGrabbed: {
        auto const curr_angle = std::atan2(pos.y - y2, pos.x - x2);
        auto const delta_angle = curr_angle - m_prev_angle;
        m_dp.m_angle2 = m_dp_orig_angle2 + delta_angle;
        break;
    }
    case State::NotInteracting:
        break;
    }
}
