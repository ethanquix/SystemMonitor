//
// Created by szterg on 21/01/17.
//

#include <iostream>
#include <wordexp.h>
#include "SfmlDisplay.hpp"
#include "../core/Core.hpp"

void Display::SfmlDisplay::draw(const Display::Board &board,
                                const std::pair<int, int> &pair,
                                const std::vector<std::pair<int, int>> &vector,
                                bool fill)
{
    (void) fill;
    if (vector.empty())
        return;
    auto it = (vector.size() > 40) ? vector.end() - 40 : vector.begin();
    auto tmp = (vector.size() > 40) ? 40 : vector.size();
    auto idx = 0;
    auto min_elem = std::min_element(it, vector.end(),
                                     [](const std::pair<int, int> &left,
                                        const std::pair<int, int> &right) {
                                         return left.second < right.second;
                                     });
    auto max_elem = std::min_element(it, vector.end(),
                                     [](const std::pair<int, int> &left,
                                        const std::pair<int, int> &right) {
                                         return left.second > right.second;
                                     });
    std::for_each(it, vector.end(),
                  [&it, board, pair, &idx, vector, this, &tmp, &min_elem, &max_elem](
                          std::pair<int, int> const &) {
                      drawGraphSquare(board, (*it), idx, tmp, (*max_elem).second);
                      it++;
                      idx++;
                  });
}

void Display::SfmlDisplay::write(const Display::Board &board,
                                 const std::string &string)
{
    _text.setString(string);
    _text.setPosition(sf::Vector2f(board.x, board.y));
    _window.draw(_text);
}

Display::SfmlDisplay::SfmlDisplay() :
        _window(sf::VideoMode(_width, _height), _title,
                sf::Style::Close | sf::Style::Resize),
        _font(),
        _text(),
        _location(0),
        _isInSelection(false),
        _isInLoading(0),
        _fill(true),
        _pathLoad(),
        _isAboveEveryone(false),
        _LuneSprite(),
        _textures(new ResourceHolder<sf::Texture, Textures>())
{
    try {
        _textures->load_resource(Textures::Lune, "ressources/Lune.png");
        _LuneSprite.setTexture(_textures->get_resource(Textures::Lune));
    }
    catch (std::runtime_error const &e) {
        std::cerr << e.what() << std::endl;
    }

    _window.setKeyRepeatEnabled(true);
    resizeBoard(1080, 1920);
    if (_font.loadFromFile("ressources/roboto.ttf")) {
        _text.setFont(_font);
        _text.setCharacterSize(24);
        _text.setColor(sf::Color(54, 5, 19));
        _text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }
}

Display::SfmlDisplay::~SfmlDisplay()
{
    _window.close();
}

void Display::SfmlDisplay::handlePlayerInput(sf::Keyboard::Key key, bool down)
{
    (void) down;

    switch (key) {
        case sf::Keyboard::Right:
            _location = (_location + 1) % 8;
            break;
        case sf::Keyboard::Left:
            _location = (_location == 0) ? 7 : _location - 1;
            break;
        case sf::Keyboard::Up:
            _moduleLocation = (int) ((_moduleLocation == 0) ?
                                     Core::getInstance()->getCachedModules().size() -
                                     1 : (unsigned long) (_moduleLocation - 1));
            break;
        case sf::Keyboard::Down:
            _moduleLocation = (int) ((_moduleLocation + 1) %
                                     Core::getInstance()->getCachedModules().size());
            break;
        case sf::Keyboard::BackSpace:
            Core::getInstance()->disableModule(_location);
            break;
        case sf::Keyboard::P:
            _isInLoading = 1;
            break;
        case sf::Keyboard::M:
            _fill = !_fill;
            break;
        case sf::Keyboard::X:
            _isAboveEveryone = !_isAboveEveryone;
            break;
        case sf::Keyboard::F2:
            _location = 0;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F3:
            _location = 1;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F4:
            _location = 2;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F5:
            _location = 3;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F6:
            _location = 4;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F7:
            _location = 5;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F8:
            _location = 6;
            _isInSelection = 1;
            break;
        case sf::Keyboard::F9:
            _location = 7;
            _isInSelection = 1;
            break;
        case sf::Keyboard::N:
            Core::getInstance()->changeDisplay(false);
            break;
        case sf::Keyboard::Return:
            if (_isInSelection) {
                auto instance = Core::getInstance();
                instance->enableModule(
                        *(instance->getCachedModules().begin() + _moduleLocation),
                        _location);
            }
            _isInSelection = !_isInSelection;
            _moduleLocation = 0;
            break;
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
            Core::getInstance()->exitLoop();
            _window.close();
            break;
        default:
            break;
    }
}

void Display::SfmlDisplay::processEvents()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (_isInLoading)
            textHandle(event);
        else {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    handlePlayerInput(event.key.code, true);
                    break;
                case sf::Event::Resized:
                    resizeBoard(event.size.height, event.size.width);
                    break;
                case sf::Event::Closed: {
                    Core::getInstance()->exitLoop();
                    _window.close();
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void Display::SfmlDisplay::erase()
{
    _window.clear(sf::Color(113, 113, 114));
}

void Display::SfmlDisplay::handleResize()
{

}

void Display::SfmlDisplay::refresh()
{
    if (_isAboveEveryone)
        _window.draw(_LuneSprite);
    else if (_isInLoading)
        drawLoadingScreen();
    else if (_isInSelection)
        drawSelectionScreen();
    else {
        drawLine(0, _height / 2, _width, _height / 2);
        drawLine(_width / 2, 0, _width / 2, _height);
        drawLine(_width / 2, _height / 4, _width, _height / 4);
        drawLine(_width / 2, _height - _height / 4, _width,
                 _height - _height / 4);
        drawLine(_width - _width / 4, _height / 2, _width - _width / 4,
                 _height);
        resizeBoard(_height, _width);
        auto board = Core::getInstance()->getBoards()[_location];
        drawSquare(board);
    }
    _window.display();
}

void Display::SfmlDisplay::resizeBoard(unsigned int height,
                                       unsigned int width)
{
    Display::Board *_boards = Core::getInstance()->getBoards();

    for (int i = 0; i < 2; ++i) {
        _boards[i].x = 1;
        _boards[i].y = 1 + i * (height / 2);
        _boards[i].width = (width - 2) / 2;
        _boards[i].height = (height - 2) / 2;
    }
    for (int i = 2; i < 4; ++i) {
        _boards[i].x = width / 2 + 2;
        _boards[i].y = 1 + (i - 2) * ((height - 2) / 4 + 1);
        _boards[i].width = (width - 2) / 2;
        _boards[i].height = (height - 2) / 4;
    }
    for (int i = 4; i < 6; ++i) {
        _boards[i].x = width / 2 + 2;
        _boards[i].y =
                2 + 2 * (height - 2) / 4 + (i - 4) * ((height - 2) / 4 + 1);
        _boards[i].width = (width - 2) / 4;
        _boards[i].height = (height - 2) / 4;
    }
    for (int i = 6; i < 8; ++i) {
        _boards[i].x = width / 4 * 3 + 3;
        _boards[i].y =
                2 + 2 * (height - 2) / 4 + (i - 6) * ((height - 2) / 4 + 1);
        _boards[i].width = (width - 2) / 4;
        _boards[i].height = (height - 2) / 4;
    }
}

void Display::SfmlDisplay::drawLine(int x1, int x2, int x3, int x4)
{
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(x1, x2)),
                    sf::Vertex(sf::Vector2f(x3, x4))
            };
    _window.draw(line, 2, sf::Lines);
}

void Display::SfmlDisplay::drawSelectionScreen()
{
    int x = 0;

    erase();
    auto Cache = Core::getInstance()->getCachedModules();
    auto it = Cache.begin();
    std::for_each(Cache.begin(), Cache.end(),
                  [&it, this, &x](std::string const &) {
                      this->write((*it), sf::Vector2f(_width / 3, x * 50),
                                  (x == _moduleLocation) ? sf::Color::White
                                                         : sf::Color::Black);
                      it++;
                      x++;
                  });
}

void Display::SfmlDisplay::drawSquare(Display::Board &board)
{
    sf::RectangleShape rectangle(sf::Vector2f(board.width, board.height));
    rectangle.setFillColor(sf::Color(247, 221, 46, 50));
    rectangle.setPosition(sf::Vector2f(board.x, board.y));

    _window.draw(rectangle);
}

void
Display::SfmlDisplay::write(std::string const &string, sf::Vector2f const &vec,
                            sf::Color color)
{
    sf::Text tmp;

    tmp.setFont(_font);
    tmp.setPosition(vec);
    tmp.setColor(color);
    tmp.setString(string);
    _window.draw(tmp);
}

void Display::SfmlDisplay::drawLoadingScreen()
{
    erase();
    sf::Text tmp;

    tmp.setFont(_font);
    tmp.setString(_pathLoad.c_str() + sizeof(char));
    tmp.setPosition(sf::Vector2f(_width / 3, _height / 2));
    tmp.setColor(sf::Color(204, 153, 17));
    _window.draw(tmp);
}

void Display::SfmlDisplay::textHandle(sf::Event event)
{
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode > 30 && _isInLoading)
            _pathLoad += static_cast<char>(event.text.unicode);
    }
    if (_isInLoading && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Q)
            handlePlayerInput(sf::Keyboard::Escape, true);
        if (event.key.code == sf::Keyboard::BackSpace && _pathLoad.size() > 1)
            _pathLoad.pop_back();
        if (event.key.code == sf::Keyboard::Return) {
            wordexp_t exp_result;
            if (_pathLoad.size() == 1) {
                _isInLoading = 0;
                return;
            }
            if (wordexp(_pathLoad.c_str() + 1, &exp_result, 0) == 0) {
                auto instance = Core::getInstance();
                instance->loadModule(exp_result.we_wordv[0]);
                wordfree(&exp_result);
                _pathLoad = "";
                _isInLoading = 0;
            }
        }
    }
}

void Display::SfmlDisplay::drawGraphSquare(const Display::Board &board,
                                           const std::pair<int, int> &cur,
                                           int idx, unsigned long size,
                                           int maximum)
{
    int tmpH = board.height - board.height / 3;
    if (tmpH == 0 || maximum == 0 || size == 0)
        return;
    int recH = ((cur.second * tmpH) / maximum * tmpH / tmpH);
    sf::RectangleShape rectangle(sf::Vector2f(board.width / size, recH));
    rectangle.setFillColor(
            (_fill) ? sf::Color::Yellow : sf::Color(rand() % 255, rand() % 255,
                                                    rand() % 255, rand() % 255));
    rectangle.setPosition(sf::Vector2f(board.x + (idx * (board.width / size)),
                                       (board.y + board.height) - recH));
    _window.draw(rectangle);
}