#include "constants.hpp"
#include "double_pendulum.hpp"
#include "double_pendulum_renderer.hpp"
#include "input_handler.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window({800, 600}, "Double Pendulum");
    window.setFramerateLimit(144);

    // for user interaction
    DoublePendulum dp1({0.0, 0.0}, 9.81, 1.0, 1.0, 7.0 / 8.0 * PI, 0.0);
    // for seeing how pendulum actually moves
    DoublePendulum dp2 = dp1;
    // for computing trail
    DoublePendulum dp3 = dp1;

    sf::View const view({0.0, 0.0},
                        {4.2f * static_cast<float>(window.getSize().x) /
                             static_cast<float>(window.getSize().y),
                         4.2f});
    DoublePendulumRenderer dp_renderer(dp1, window, view);

    DpInputHandler input_handler(dp1);
    bool play = false;

    sf::Clock clock;
    while (window.isOpen()) {
        for (sf::Event event; window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == 0) {
                    input_handler.press(static_cast<sf::Vector2<double>>(
                        window.mapPixelToCoords(
                            {event.mouseButton.x, event.mouseButton.y},
                            view)));
                    play = false;
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == 0) {
                    input_handler.release();
                }
                break;
            case sf::Event::MouseMoved:
                input_handler.move(
                    static_cast<sf::Vector2<double>>(window.mapPixelToCoords(
                        {event.mouseMove.x, event.mouseMove.y}, view)));
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::P) {
                    play = true;
                    dp2 = dp1;
                    clock.restart();
                }
                break;
            default:
                break;
            }
        }

        dp3 = dp1;
        dp_renderer.set_double_pendulum(dp3);
        dp_renderer.clear();

        double constexpr SIM_TIME = 5.0;
        double constexpr DT = 0.0001;
        double render_elapsed = 0.0;
        for (double elapsed = 0.0; elapsed < SIM_TIME; elapsed += DT) {
            dp3.update(DT);
            if (render_elapsed > 1.0 / 144.0) {
                render_elapsed = 0.0;
                dp_renderer.render_trail(
                    {static_cast<sf::Uint8>(255.0 * (elapsed / SIM_TIME)), 0,
                     static_cast<sf::Uint8>(255.0 *
                                            (1.0 - elapsed / SIM_TIME)),
                     170});
            }
            render_elapsed += DT;
        }

        if (play) {
            for (double elapsed = clock.restart().asSeconds() / 2.0;
                 elapsed > 0.0; elapsed -= DT) {
                dp2.update(DT);
            }
        }

        window.clear(sf::Color::White);

        dp_renderer.set_double_pendulum(dp3);
        dp_renderer.render_trail(window);

        dp_renderer.set_double_pendulum(dp1);
        dp_renderer.render(window);

        if (play) {
            dp_renderer.set_double_pendulum(dp2);
            dp_renderer.render(window);
        }

        window.display();
    }
}
