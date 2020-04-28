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

        
        auto menutoggle_cmp = menuitem_ent->addComponent<MenuToggle>(true, "Menu Toggle 1");
        menutoggle_cmp->setPosition(Vector2f(20.f, 140.f));

    }
    setLoaded(true);
}

void DebugScene::Update(const double& dt){
    sf::Event event;
    while(Engine::GetWindow().pollEvent(event)){
        if(event.type == Event::Closed){
                Engine::GetWindow().close();
        }
    }
    
    Scene::Update(dt);
}
