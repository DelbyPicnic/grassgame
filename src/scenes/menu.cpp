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
            mItem->addTag("menu");
            yPos += 40; 
        }
    }
    setLoaded(true);
}

void MainMenu::Update(const double& dt){
    
    auto selected = ents.find(itemTags[selectedIdx]);
    
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            int max = itemTags.size() -1;
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
                auto comp = selected[0]->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(-1);
            }
            if(event.key.code == sf::Keyboard::Right){
                auto comp = selected[0]->GetCompatibleComponent<MenuComponent>();
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
    std::vector<std::shared_ptr<Entity>> menuItems = ents.find("menu");
    for (auto &ent : menuItems){
        auto comp = ent->GetCompatibleComponent<MenuComponent>();
        if (ent == selected[0]){
            comp[0]->setColor(sf::Color(100, 100, 220));
        }else{
            comp[0]->setColor(sf::Color(220, 220, 220));
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
        optnFPSLimit->addTag("opt_fps_limit");
        optnFPSLimit->addTag("menu");
        
        std::vector<std::string> resolution_options = {"640 x 480", "1280 x 720", "1920 x 1080"};
        auto optnResolution = makeEntity();
        auto cmpResolution = optnResolution->addComponent<MenuOption>(0, resolution_options, "Display Resolution");
        cmpResolution->setPosition(Vector2f(xPos, yPos + 40));
        optnResolution->addTag("opt_resolution");
        optnResolution->addTag("menu");

        auto optnFullscreen = makeEntity();
        auto cmpFullscreen = optnFullscreen->addComponent<MenuToggle>(0, "Fullscreen");
        cmpFullscreen->setPosition(Vector2f(xPos, yPos + 80));
        optnFullscreen->addTag("opt_fullscreen");
        optnFullscreen->addTag("menu");

        auto optnBack = makeEntity();
        auto cmpBack = optnBack->addComponent<MenuComponent>("Done");
        cmpBack->setPosition(Vector2f(xPos, yPos + 120));
        optnBack->addTag("opt_back");
        optnBack->addTag("menu");
    }
    setLoaded(true);
}

void OptionMenu::setOptions(){
    
    auto optnFPSLimit = ents.find("opt_fps_limit");
    auto cmpFPSLimit = optnFPSLimit[0]->get_components<MenuOption>();
    int value = cmpFPSLimit[0]->getValue();
    switch (value){
        case 0: Engine::GetWindow().setFramerateLimit(0);
                break;
        case 1: Engine::GetWindow().setFramerateLimit(30);
                break;
        case 2: Engine::GetWindow().setFramerateLimit(40);
                break;
        case 3: Engine::GetWindow().setFramerateLimit(59);
                break;
        case 4: Engine::GetWindow().setFramerateLimit(60);
                break;
        case 5: Engine::GetWindow().setFramerateLimit(120);
                break;
        case 6: Engine::GetWindow().setFramerateLimit(144);
                break;
    }
    
}

void OptionMenu::Update(const double& dt){
    auto selected = ents.find(itemTags[selectedIdx]);

    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            int max = itemTags.size() -1;
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
                auto comp = selected[0]->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(-1);
            }
            if(event.key.code == sf::Keyboard::Right){
                auto comp = selected[0]->GetCompatibleComponent<MenuComponent>();
                comp[0]->setIdx(1);
            }
            if(event.key.code == sf::Keyboard::Return){
                switch(selectedIdx){
                    case 3 :    setOptions();
                                Engine::ChangeScene(&mainmenu);
                                break;
                }
            }
        }
    }

    std::vector<std::shared_ptr<Entity>> menuItems = ents.find("menu");
    for (auto &ent : menuItems){
        auto comp = ent->GetCompatibleComponent<MenuComponent>();
        if (ent == selected[0]){
            comp[0]->setColor(sf::Color(100, 100, 220));
        }else{
            comp[0]->setColor(sf::Color(220, 220, 220));
        }
    }
    Scene::Update(dt);
}