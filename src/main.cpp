#include "engine.hpp"
#include "main.hpp"
#include "scenes/menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

MainMenu mainmenu;
OptionMenu optmenu;
CreditsMenu crdmenu;

int main(){
    Settings* s = new Settings();
    s->screen_width = 1280;
    s->screen_height = 720;
    s->vsync = true;
    s->fullscreen = false;
    s->input_type = "KEYBOARD";

    Engine::Start(*s, "GrassGame", &mainmenu);
}