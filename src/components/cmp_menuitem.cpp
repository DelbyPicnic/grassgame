#include "cmp_menuitem.h"
#include "engine.hpp"
#include <renderer.hpp>
#include <utilities.hpp>
#include <iostream>
#include <memory>


MenuComponent::MenuComponent(Entity* const p, const std::string& str) : Component(p), _labelText(str){
}

void MenuComponent::update(double dt) {
}

void MenuComponent::render() {
    Renderer::queue(&_label);
}

void MenuComponent::setColor(const sf::Color color){
    _labelColor = color;
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
}

void MenuToggle::update(double dt){
    if (_value)
        _optionText = "ON";
    else
        _optionText = "OFF";

    _label.setString(_labelText + " " + _optionText);
}

void MenuToggle::render(){
    Renderer::queue(&_label);
}

void MenuToggle::setValue(const bool value){
    _value = value;
}

bool MenuToggle::getValue(){
    return _value;
}

MenuOption::MenuOption(Entity* const p, const int value, const std::vector<std::string> options, const std::string& str) : MenuComponent(p, str), _value(value), _menuOptions(options){
}

void MenuOption::update(double dt){
}

void MenuOption::render(){
    Renderer::queue(&_label);
}

void MenuOption::setValue(const int value){
    if (value == 0 || value < _menuOptions.size()){
        _value = value;
    }
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

