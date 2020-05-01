#include "cmp_menuitem.h"
#include "engine.hpp"
#include <renderer.hpp>
#include <utilities.hpp>
#include <iostream>
#include <memory>


MenuComponent::MenuComponent(Entity* const p, const std::string& str) : Component(p), _labelText(str){
    // Set default options
    setFont("MulledWineSeason-Medium.otf");
    setText(str);
    _label.setFillColor(sf::Color(220, 220, 220));
}

void MenuComponent::update(double dt) {
}

void MenuComponent::render() {
    Renderer::queue(&_label);
}

void MenuComponent::setIdx(int value){
}

void MenuComponent::setColor(const sf::Color color){
    _label.setFillColor(color);
}

void MenuComponent::setText(const std::string& text){
    _label.setString(text);
}

void MenuComponent::setFont(const std::string& font){
    _font = Resources::get<sf::Font>(font);
    _label.setFont(*_font);
}

void MenuComponent::setPosition(const sf::Vector2f position){
    _label.setPosition(position);
}

sf::Vector2f MenuComponent::getPosition(){
    return _label.getPosition();
}

float MenuComponent::getWidth(){
    return _label.getLocalBounds().width;
}

float MenuComponent::getHeight(){
    return _label.getLocalBounds().height;
}


MenuToggle::MenuToggle(Entity* const p, const bool value, const std::string& str) : MenuComponent(p, str), _value(value){
    setFont("MulledWineSeason-Medium.otf");
    setText(str);
    _label.setFillColor(sf::Color(220, 220, 220));
}

void MenuToggle::update(double dt){
}

void MenuToggle::render(){
    Renderer::queue(&_label);
}

void MenuToggle::setIdx(int value){
    if (value % 2 != 0 )
        _value = !_value;
    setText(_labelText);
}

void MenuToggle::setValue(const bool value){
    _value = value;
    setText(_labelText);
}

void MenuToggle::setText(const std::string& text){
    _labelText = text;

    if (_value)
        _optionText = "ON";
    else
        _optionText = "OFF";

    _label.setString(_labelText + " " + _optionText);
}

bool MenuToggle::getValue(){
    return _value;
}

MenuOption::MenuOption(Entity* const p, const int value, const std::vector<std::string> options, const std::string& str) : MenuComponent(p, str), _value(value), _menuOptions(options){
    setFont("MulledWineSeason-Medium.otf");
    setText(str);
    _label.setFillColor(sf::Color(220, 220, 220));
}

void MenuOption::update(double dt){
}

void MenuOption::render(){
    Renderer::queue(&_label);
}

void MenuOption::setIdx(int value){
    int idx = _value + value;
    if (idx >= 0 && idx < _menuOptions.size()){
        _value = idx;
    }
    setText(_labelText);
}

void MenuOption::setValue(const int value){
    if (value >= 0 && value < _menuOptions.size()){
        _value = value;
    }
    setText(_labelText);
}

void MenuOption::setText(const std::string& text){
    _label.setString(_labelText + " " + _menuOptions[_value]);
}

void MenuOption::setOptions(const std::vector<std::string> options){
    _menuOptions = options;
}

void MenuOption::addOption(const std::string option){
    _menuOptions.push_back(option);
}

int MenuOption::getValue(){
    return _value;
}

