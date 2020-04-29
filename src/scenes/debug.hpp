#pragma once
#include "engine.hpp"

class DebugScene : public Scene {
public:
    DebugScene() = default;
    ~DebugScene() override = default;
    void Load() override;
    void Update(const double& dt) override;

protected:
    std::vector<std::shared_ptr<Entity>> menuOptions;
    int selectedOption = 0;
};