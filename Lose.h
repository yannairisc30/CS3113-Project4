
#pragma once
#include "Scene.h"

class Lose : public Scene {
public:
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};