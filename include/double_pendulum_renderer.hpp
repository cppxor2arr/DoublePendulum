#ifndef DOUBLE_PENDULUM_RENDERER_HPP
#define DOUBLE_PENDULUM_RENDERER_HPP

#include "double_pendulum.hpp"
#include <SFML/Graphics.hpp>

class DoublePendulumRenderer {
public:
    DoublePendulumRenderer(DoublePendulum const &double_pendulum,
                           sf::RenderTarget const &render_target,
                           sf::View const &view);

    void set_double_pendulum(DoublePendulum const &double_pendulum);

    void render_trail(sf::Color const &color);
    void render_trail(sf::RenderTarget &render_target);
    void render(sf::RenderTarget &render_target);
    void clear();

private:
    DoublePendulum const *m_double_pendulum;

    sf::RenderTexture m_render_texture;
    sf::Sprite m_texture_sprite;
    sf::RectangleShape m_limb;
    sf::CircleShape m_joint;
};

#endif // DOUBLE_PENDULUM_RENDERER_HPP
