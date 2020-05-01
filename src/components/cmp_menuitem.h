#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.hpp>
#include <vector>

// Simple selectable menu item
class MenuComponent : public Component {
public:
    MenuComponent() = delete;
    ~MenuComponent() override = default;
    explicit MenuComponent(Entity* const p, const std::string& str = "");

    void update(double dt) override;
    void render() override;
    virtual void setIdx(int value);
    void setColor(const sf::Color color);
    void setText(const std::string& text);
    void setFont(const std::string& font);
    void setFontSize(unsigned int fSize);
    void setScale(const float scale);
    void setPosition(const sf::Vector2f position);
    void setRotation(const float rotation);
    sf::Vector2f getPosition();
    float getWidth();
    float getHeight();
    

protected:
    std::string _labelText;
    sf::Text _label;
    std::shared_ptr<sf::Font> _font;
};

// Menu boolean option on/off
class MenuToggle : public MenuComponent {
public:
    MenuToggle() = delete;
    ~MenuToggle() override = default;
    explicit MenuToggle(Entity* const p, const bool value, const std::string& str = "");

    void update(double dt) override;
    void render() override;
    void setIdx(int value) override;
    void setValue(const bool value);
    void setText(const std::string& text);
    bool getValue();

protected:
    std::string _optionText;
    bool _value;
};

// Customizable menu option with many options
class MenuOption : public MenuComponent {
public:
    MenuOption() = delete;
    ~MenuOption() override = default;
    explicit MenuOption(Entity* const p, const int value, const std::vector<std::string> options, const std::string& std = "");

    void update(double dt) override;
    void render() override;
    void setIdx(int value);
    void setValue(const int value);
    void setText(const std::string& text);
    void setOptions(const std::vector<std::string> options);
    void addOption(const std::string option);
    int getValue();

protected:
    std::vector<std::string> _menuOptions;
    int _value;
};