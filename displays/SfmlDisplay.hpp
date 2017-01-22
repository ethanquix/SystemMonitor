//
// Created by szterg on 21/01/17.
//

#ifndef CPP_GKRELLM_SFML_HPP
#define CPP_GKRELLM_SFML_HPP

#include <SFML/Graphics.hpp>
#include "IMonitorDisplay.hpp"
#include "Ressource.hpp"

namespace Display
{
    class SfmlDisplay : public Display::IMonitorDisplay
    {
    public:
        SfmlDisplay();

        ~SfmlDisplay();

    public:
        void draw(const Board &board,
                  const std::pair<int, int> &pair,
                  const std::vector<std::pair<int, int>> &vector,
                  bool fill) override;

        void write(const Board &board, const std::string &string) override;

        void
        write(std::string const &string, sf::Vector2f const &vec, sf::Color color);

        void erase() override;

        void refresh() override;

        void handleResize() override;

    public:
        void processEvents();

        void drawLine(int x1, int x2, int x3, int x4);

        void handlePlayerInput(sf::Keyboard::Key key, bool down);

    private:
        sf::RenderWindow _window;
        sf::Font _font;
        sf::Text _text;
        int _location;
        bool _isInSelection;
        int _moduleLocation;
        bool _isInLoading;
        bool _fill;
        std::string _pathLoad;
        bool _isAboveEveryone;
        sf::Sprite _LuneSprite;
        ResourceHolder<sf::Texture, Textures> *_textures;

        static constexpr int _width = 1920;
        static constexpr int _height = 1080;
        static constexpr const char *_title = "SFML";

        void resizeBoard(unsigned int height, unsigned int width);

        void drawSquare(Board &board);

        static const sf::Time TimePerFrame;

        void drawSelectionScreen();

        void drawLoadingScreen();

        void textHandle(sf::Event event);

        void drawGraphSquare(const Display::Board &board,
                             const std::pair<int, int> &pair1,
                             int idx, unsigned long size, int maximum);
    };
};

#endif //CPP_GKRELLM_SFML_HPP
