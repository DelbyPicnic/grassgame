#pragma once
#include "engine.hpp"

class MainMenu : public Scene {
public:
    MainMenu() = default;
    ~MainMenu() override = default;
    void Load() override;
    void Update(const double& dt) override;
protected:
    std::vector<std::string> itemTags = {"opt_Play", "opt_Connect", "opt_Options", "opt_Quit"};
    int selectedIdx = 0;
};
/*
class ConnectMenu : public MainMenu {
public:
    ConnectMenu() = default;
    ~ConnectMenu() override = default;
    void Load() override;
    void Update(const double& dt) override;
};
*/
class OptionMenu : public MainMenu {
public:
    OptionMenu() = default;
    ~OptionMenu() override = default;
    void Load() override;
    void Update(const double& dt) override;
protected:
    void setOptions();
    std::vector<std::string> itemTags = {"opt_fps_limit", "opt_resolution", "opt_fullscreen", "opt_back"};
};

