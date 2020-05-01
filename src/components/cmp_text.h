#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.hpp>

class TextComponent : public Component {
public:
    TextComponent() = delete;
    ~TextComponent() override = default;

    explicit TextComponent(Entity* p, const std::string& str = "");
    void update(double dt) override;
    void render() override;

    void setText(const std::string& str);
    void setFont(const std::string& font);
    void setFontSize(unsigned int fntSize);
    void setColour(const sf::Color colour);
    void setScale(const float scale);
    void setPosition(const sf::Vector2f position);
    void setRotation(const float rotation);

    float getWidth();

protected:
    std::shared_ptr<sf::Font> _font;
    std::string _string;
    sf::Text _text;
};