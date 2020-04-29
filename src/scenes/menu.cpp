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
    { 
        // Display title center screen
        auto dispCenter = Engine::GetWindowSize().x /2;
        auto mainTitle = makeEntity();
        auto titleText = mainTitle->addComponent<TextComponent>("GRASSGAME");
        mainTitle->addTag("title_main");
        titleText->setFont("BrokenChalk.ttf");
        titleText->setFontSize(80);
        float titleMidpoint = dispCenter - (titleText->getWidth() / 2);
        titleText->setPosition(Vector2f(static_cast<float>(titleMidpoint), 70.0f));

        // Display Main Menu
        std::array<std::string, 4> options {"Play", "Connect", "Options", "Quit"};
        float yPos = Engine::GetWindowSize().y /2;
    
        for(int i = 0; i < options.size(); i++){
            auto mItem = makeEntity();
            auto mItemText = mItem->addComponent<MenuComponent>(options[i]);
            float itmMidpoint = dispCenter - (mItemText->getWidth() / 2);
            mItemText->setPosition(Vector2f(static_cast<float>(itmMidpoint), yPos));
            mItem->addTag("opt_" + options[i]);
            menuItems.push_back(mItem);
            yPos += 40; 
        }
    }
    setLoaded(true);
}

void MainMenu::Update(const double& dt){
    
    std::shared_ptr<Entity> selected = menuItems[selectedIdx];

    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            int max = menuItems.size() -1;
            if(event.key.code == sf::Keyboard::Up){
                if(selectedIdx > 0){
                    selectedIdx--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (selectedIdx < max){
                    selectedIdx++;
                }
            }
            if(event.key.code == sf::Keyboard::Left){
                auto comp = selected->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(-1);
            }
            if(event.key.code == sf::Keyboard::Right){
                auto comp = selected->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(1);
            }
            if(event.key.code == sf::Keyboard::Return){
                switch(selectedIdx){
                    case 0 :    std::cout << "Play" << std::endl;
                                break;
                    case 1 :    std::cout << "Connect" << std::endl;
                                break;
                    case 2 :    Engine::ChangeScene(&optmenu);
                                break;
                    case 3 :    Engine::GetWindow().close();
                                break;
                }
            }
        }
    }
    Scene::Update(dt);
}

void OptionMenu::Load(){
    {
        // Display title center screen
        auto dispCenter = Engine::GetWindowSize().x /2;
        auto mainTitle = makeEntity();
        auto titleText = mainTitle->addComponent<TextComponent>("OPTIONS");
        mainTitle->addTag("title_options");
        titleText->setFont("BrokenChalk.ttf");
        titleText->setFontSize(80);
        float titleMidpoint = dispCenter - (titleText->getWidth() / 2);
        titleText->setPosition(Vector2f(static_cast<float>(titleMidpoint), 70.0f));
        
        
        // Display Options Menu
        // [Limit Framerate] [Display Resolution] [Fullscreen] [Save]
        float yPos = Engine::GetWindowSize().y /2;
        float xPos = Engine::GetWindowSize().x /2 -50;

        std::vector<std::string> fps_options = {"Unlimited", "30 FPS", "40 FPS", "59 FPS", "60 FPS", "120 FPS", "144 FPS"};
        auto optnFPSLimit = makeEntity();
        auto cmpFPSLimit = optnFPSLimit->addComponent<MenuOption>(0, fps_options, "Limit Framerate");
        cmpFPSLimit->setPosition(Vector2f(xPos, yPos));
        optnFPSLimit->addTag("optn_fps_limit");
        menuItems.push_back(optnFPSLimit);

        std::vector<std::string> resolution_options = {"640 x 480", "1280 x 720", "1920 x 1080"};
        auto optnResolution = makeEntity();
        auto cmpResolution = optnResolution->addComponent<MenuOption>(0, resolution_options, "Display Resolution");
        cmpResolution->setPosition(Vector2f(xPos, yPos + 40));
        optnResolution->addTag("optn_resolution");
        menuItems.push_back(optnResolution);

        auto optnFullscreen = makeEntity();
        auto cmpFullscreen = optnFullscreen->addComponent<MenuToggle>(0, "Fullscreen");
        cmpFullscreen->setPosition(Vector2f(xPos, yPos + 80));
        optnFullscreen->addTag("optn_fullscreen");
        menuItems.push_back(optnFullscreen);

        auto optnBack = makeEntity();
        auto cmpBack = optnBack->addComponent<MenuComponent>("Done");
        cmpBack->setPosition(Vector2f(xPos, yPos + 120));
        optnBack->addTag("optn_back");
        menuItems.push_back(optnBack);
    }
    setLoaded(true);
}

void OptionMenu::Update(const double& dt){
     std::shared_ptr<Entity> selected = menuItems[selectedIdx];

    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            int max = menuItems.size() -1;
            if(event.key.code == sf::Keyboard::Up){
                if(selectedIdx > 0){
                    selectedIdx--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (selectedIdx < max){
                    selectedIdx++;
                }
            }
            if(event.key.code == sf::Keyboard::Left){
                auto comp = selected->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(-1);
            }
            if(event.key.code == sf::Keyboard::Right){
                auto comp = selected->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(1);
            }
            if(event.key.code == sf::Keyboard::Return){
                switch(selectedIdx){
                    case 3 :    Engine::ChangeScene(&mainmenu);
                                break;
                }
            }
        }
    }
    Scene::Update(dt);
}