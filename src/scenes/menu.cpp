#include "menu.hpp"
#include "../main.hpp"
#include "../components/cmp_text.h"
#include "../components/cmp_menuitem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

void MainMenu::Load() {
    cout << "Loading main menu..." << endl;
    {   
        // Display title center screen
        auto dispCenter = Engine::GetWindowSize().x /2;
        auto mainTitle = makeEntity();
        auto titleText = mainTitle->addComponent<TextComponent>("GRASSGAME");

        mainTitle->addTag("title_main");
        titleText->SetFont("BrokenChalk.ttf");
        titleText->SetFontSize(80);
        float titleMidpoint = dispCenter - (titleText->getWidth() / 2);
        titleText->SetPosition(Vector2f(static_cast<float>(titleMidpoint), 70.0f));

        // Display Main Menu
        std::array<std::string, 4> menuItems {"Play", "Connect", "Options", "Quit"};
        float yPos = Engine::GetWindowSize().y /2;
        int idx = 0;
        for(std::string itm : menuItems){
            auto mItem = makeEntity();
            auto mItemText = mItem->addComponent<MenuComponent>(itm);
            float itmMidpoint = dispCenter - (mItemText->getWidth() / 2);
            mItemText->setPosition(Vector2f(static_cast<float>(itmMidpoint), yPos));
            mItem->addTag("menu");
            mItem->addTag("opt_" + to_string(idx));
            yPos += 30;
            idx++;
        }
    }
    setLoaded(true);
}

void MainMenu::Update(const double& dt){
    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Up){
                if(_selItem > 0){
                    _selItem--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (_selItem < 4){
                    _selItem++;
                }
            }
        }
    }

    // Update all menu items
    vector<shared_ptr<Entity>> mItems = ents.find("menu");
    for(auto &ent : mItems){
        // Get entity component
        auto entText = ent->get_components<MenuComponent>();
        entText[0]->setColor(sf::Color(220, 220, 220));
    }

    // Update the selected menu item
    vector<shared_ptr<Entity>> selItem = ents.find("opt_" + to_string(_selItem));
    if(selItem[0] != nullptr){
        // Get item component
        auto selEntText = selItem[0]->get_components<MenuComponent>();
        selEntText[0]->setColor(sf::Color(255, 255, 255));
    }

    // User selection actionables
    if(Keyboard::isKeyPressed(Keyboard::Return)){
        switch(_selItem){
            case 0 :    std::cout << "Play" << std::endl;
                        break;
            case 1 :    std::cout << "Connect" << std::endl;
                        break;
            case 2 :    Engine::ChangeScene(&optmenu);
                        break;
            case 3 :    Engine::ChangeScene(&crdmenu);
                        break;
            case 4 :    Engine::GetWindow().close();
                        break;
        }
    }
    
    Scene::Update(dt);
}

void OptionMenu::Load(){
    cout << "Loading Options Menu..." << endl;
    {
        // Display title center screen
        auto dispCenter = Engine::GetWindowSize().x /2;
        auto mainTitle = makeEntity();
        auto titleText = mainTitle->addComponent<TextComponent>("OPTIONS");

        mainTitle->addTag("title_options");
        titleText->SetFont("BrokenChalk.ttf");
        titleText->SetFontSize(80);
        float titleMidpoint = dispCenter - (titleText->getWidth() / 2);
        titleText->SetPosition(Vector2f(static_cast<float>(titleMidpoint), 70.0f));
        
        
        // Display Main Menu
        std::array<std::string, 4> menuItems {"Fullscreen", "Vsync", "Use Gamepad"};
        float yPos = Engine::GetWindowSize().y /2;
        int idx = 0;
        for(std::string itm : menuItems){
            auto mItem = makeEntity();
            auto mItemText = mItem->addComponent<MenuToggle>(false, itm);
            float itmMidpoint = dispCenter - (mItemText->getWidth() / 2);
            mItemText->setPosition(Vector2f(static_cast<float>(itmMidpoint), yPos));
            mItem->addTag("menu");
            mItem->addTag("opt_" + to_string(idx));
            yPos += 30;
            idx++;
        }
    }
    setLoaded(true);
}

void OptionMenu::Update(const double& dt){
     // Update all menu items
    vector<shared_ptr<Entity>> mItems = ents.find("menu");
    for(auto &ent : mItems){
        // Get entity component
        auto entText = ent->get_components<MenuToggle>();
        if(entText[0] != nullptr){
            entText[0]->setColor(sf::Color(220, 220, 220));
        }
    }
    
    // Update the selected menu item
    vector<shared_ptr<Entity>> selItem = ents.find("opt_" + to_string(_selItem));
    if(selItem[0] != nullptr){
        // Get item component
        auto selEntText = selItem[0]->get_components<MenuToggle>();
        selEntText[0]->setColor(sf::Color(255, 255, 255));
    }
    
    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Up){
                if(_selItem > 0){
                    _selItem--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (_selItem < 2){
                    _selItem++;
                }
            }
            if(event.key.code == sf::Keyboard::Left){
                auto entText = mItems[_selItem]->get_components<MenuToggle>();
                entText[0]->setValue(!entText[0]->getValue());
            }
            if(event.key.code == sf::Keyboard::Right){
                auto entText = mItems[_selItem]->get_components<MenuToggle>();
                entText[0]->setValue(!entText[0]->getValue());
            }
            if(event.key.code == sf::Keyboard::BackSpace){
                Engine::ChangeScene(&mainmenu);
                goto end;
            }
        }
    }
    end:
    Scene::Update(dt);
}

void CreditsMenu::Load(){
    cout << "Loading Credits Menu..." << endl;
    {
        auto txt = makeEntity();
        auto t = txt->addComponent<TextComponent>("Credits Menu...");
    }
    setLoaded(true);
}

void CreditsMenu::Update(const double& dt){
    // Get system events from the window:
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::BackSpace){
                Engine::ChangeScene(&mainmenu);
            }
        }
    }
}