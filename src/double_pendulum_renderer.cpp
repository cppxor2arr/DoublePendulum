#include "double_pendulum_renderer.hpp"
#include "constants.hpp"
#include <cmath>

DoublePendulumRenderer::DoublePendulumRenderer(
    DoublePendulum const &double_pendulum,
    sf::RenderTarget const &render_target, sf::View const &view) {
    m_render_texture.create(render_target.getSize().x,
                            render_target.getSize().y);
    m_render_texture.setView(view);
    m_texture_sprite.setTexture(m_render_texture.getTexture());

    set_double_pendulum(double_pendulum);
}

void DoublePendulumRenderer::set_double_pendulum(
    DoublePendulum const &double_pendulum) {
    m_double_pendulum = &double_pendulum;

    m_limb.setSize({static_cast<float>(double_pendulum.m_length / 15.0),
                    static_cast<float>(double_pendulum.m_length)});
    m_limb.setOrigin(m_limb.getSize().x / 2.0f, 0.0f);
    m_limb.setFillColor(sf::Color::Black);

    m_joint.setRadius(m_limb.getSize().x);
    double const pixel_radius =
        (m_render_texture.mapCoordsToPixel({m_joint.getRadius(), 0.0}) -
         m_render_texture.mapCoordsToPixel({0.0, 0.0}))
            .x;
    m_joint.setPointCount(static_cast<std::size_t>(2.0 * PI * pixel_radius));
    m_joint.setOrigin(m_joint.getRadius(), m_joint.getRadius());
}

double radians_to_degrees(double const radians) {
    return 180.0 / PI * radians;
}

void DoublePendulumRenderer::render_trail(sf::Color const &color) {
    auto const x1 = static_cast<float>(
        m_double_pendulum->m_anchor.x +
        m_double_pendulum->m_length *
            std::cos(m_double_pendulum->m_angle1 + PI / 2.0));
    auto const y1 = static_cast<float>(
        m_double_pendulum->m_anchor.y +
        m_double_pendulum->m_length *
            std::sin(m_double_pendulum->m_angle1 + PI / 2.0));
    auto const x2 = static_cast<float>(
        x1 + m_double_pendulum->m_length *
                 std::cos(m_double_pendulum->m_angle2 + PI / 2.0));
    auto const y2 = static_cast<float>(
        y1 + m_double_pendulum->m_length *
                 std::sin(m_double_pendulum->m_angle2 + PI / 2.0));

    m_joint.setFillColor(color);
    m_joint.setPosition(x2, y2);
    m_joint.setScale(0.4f, 0.4f);
    m_render_texture.draw(m_joint);
    m_joint.setScale(1.0f, 1.0f);
}

void DoublePendulumRenderer::render_trail(sf::RenderTarget &render_target) {
    m_render_texture.display();
    render_target.setView(render_target.getDefaultView());
    render_target.draw(m_texture_sprite);
}

void DoublePendulumRenderer::render(sf::RenderTarget &render_target) {
    auto const x1 = static_cast<float>(
        m_double_pendulum->m_anchor.x +
        m_double_pendulum->m_length *
            std::cos(m_double_pendulum->m_angle1 + PI / 2.0));
    auto const y1 = static_cast<float>(
        m_double_pendulum->m_anchor.y +
        m_double_pendulum->m_length *
            std::sin(m_double_pendulum->m_angle1 + PI / 2.0));
    auto const x2 = static_cast<float>(
        x1 + m_double_pendulum->m_length *
                 std::cos(m_double_pendulum->m_angle2 + PI / 2.0));
    auto const y2 = static_cast<float>(
        y1 + m_double_pendulum->m_length *
                 std::sin(m_double_pendulum->m_angle2 + PI / 2.0));

    render_target.setView(m_render_texture.getView());

    m_limb.setPosition(static_cast<sf::Vector2f>(m_double_pendulum->m_anchor));
    m_limb.setRotation(
        static_cast<float>(radians_to_degrees(m_double_pendulum->m_angle1)));
    render_target.draw(m_limb);

    m_limb.setPosition(x1, y1);
    m_limb.setRotation(
        static_cast<float>(radians_to_degrees(m_double_pendulum->m_angle2)));
    render_target.draw(m_limb);

    m_joint.setFillColor(sf::Color::Black);

    m_joint.setPosition(
        static_cast<sf::Vector2f>(m_double_pendulum->m_anchor));
    render_target.draw(m_joint);

    m_joint.setFillColor(sf::Color::Blue);

    m_joint.setPosition(x1, y1);
    render_target.draw(m_joint);
    m_joint.setPosition(x2, y2);
    render_target.draw(m_joint);
}

void DoublePendulumRenderer::clear() {
    m_render_texture.clear(sf::Color::Transparent);
}
