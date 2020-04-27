#include "cmp_text.h"
#include <renderer.hpp>
#include <utilities.hpp>
#include <iostream>
void TextComponent::update(double dt) {
}

void TextComponent::render() {
    Renderer::queue(&_text);
}

TextComponent::TextComponent(Entity* const p, const std::string& str) : Component(p), _string(str){
    _text.setString(_string);
    _font = Resources::get<sf::Font>("MulledWineSeason-Medium.otf");
    _text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str){
    _string = str;
    _text.setString(_string);
}

void TextComponent::SetFont(const std::string& font){
    _font = Resources::get<sf::Font>(font);
    _text.setFont(*_font);
}

void TextComponent::SetFontSize(unsigned int fntSize){
    _text.setCharacterSize(fntSize);
}

void TextComponent::SetColour(const sf::Color colour){
    _text.setFillColor(colour);
}

void TextComponent::SetScale(const float scale){
    _text.setScale(sf::Vector2f(scale,scale));
}

void TextComponent::SetPosition(const sf::Vector2f position){
    _text.setPosition(position);
}

void TextComponent::SetRotation(const float rotation){
    _text.setRotation(rotation);
}

float TextComponent::getWidth(){
    sf::FloatRect txtBounds = _text.getLocalBounds();
    return txtBounds.width;
}