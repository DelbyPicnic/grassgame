#include "debug.hpp"
#include "../main.hpp"
#include "../components/cmp_text.h"
#include "../components/cmp_menuitem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <vector>

using namespace sf;

void DebugScene::Load(){
    { 
        // test all loadable elements
        auto text_ent = makeEntity();
        auto text_cmp = text_ent->addComponent<TextComponent>("Text Component 1\nText Component 1 (line 2)");
        text_ent->addTag("text_component");
        text_cmp->setPosition(Vector2f(20.f, 20.f));

        auto menuitem_ent = makeEntity();
        auto menuitem_cmp = menuitem_ent->addComponent<MenuComponent>("Menu Component 1");
        menuitem_ent->addTag("menu_component");
        menuitem_cmp->setPosition(Vector2f(20.f, 100.f));
        menuOptions.push_back(menuitem_ent);

        auto menutoggle_ent = makeEntity();
        auto menutoggle_cmp = menutoggle_ent->addComponent<MenuToggle>(true, "Menu Toggle 1");
        menutoggle_cmp->setPosition(Vector2f(20.f, 140.f));
        menuOptions.push_back(menutoggle_ent);

        const std::vector<std::string> m_options = {"option 1", "option 2", "option 3"};
        auto menuoption_ent = makeEntity();
        auto menuoption_cmp = menuoption_ent->addComponent<MenuOption>(0, m_options, "Menu Option 1");
        menuoption_cmp->setPosition(Vector2f(20.f, 180.f));
        menuOptions.push_back(menuoption_ent);
    }
    setLoaded(true);
}

void DebugScene::Update(const double& dt){
    std::shared_ptr<Entity> selected = menuOptions[selectedOption];

    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
        if(event.type == sf::Event::KeyPressed){
            int max = menuOptions.size() -1;
            if(event.key.code == sf::Keyboard::Up){
                if(selectedOption > 0){
                    selectedOption--;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (selectedOption < max){
                    selectedOption++;
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
        }
    }

    for (auto &ent : menuOptions){
        auto comp = ent->GetCompatibleComponent<MenuComponent>();
        if (ent == selected){
            comp[0]->setColor(sf::Color(180, 180, 220));
        } else {
            comp[0]->setColor(sf::Color(220, 220, 220));
        }
    }

    Scene::Update(dt);
}
