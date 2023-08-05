#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

// Class made to make using text simpler
class Text {
    private:
        sf::Text _text;
    public:
        int x, y, size;
        sf::Color color;
        sf::Font font;
        string content;
        Text(string content, int x, int y, int size, sf::Color color, sf::Font font) {
            this->content = content;
            this->x = x;
            this->y = y;
            this->size = size;
            this->color = color;
            this->font = font;
            sf::Text textobj;
            this->_text = textobj;
            UpdateTextObject();
        }
        void Draw(sf::RenderWindow& window) {
            window.draw(_text);
        }

        void UpdateTextObject() {
            _text.setString(content);
            _text.setCharacterSize(size);
            _text.setFillColor(color);
            _text.setFont(font);
        }
        sf::Text GetTextObject() {return _text;}
        string GetTextContent() {return content; UpdateTextObject();}
        void SetTextContent(string content) {this->content = content;}
};