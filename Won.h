#pragma once

#pragma once
#include "Scene.h"

class Won : public Scene {
public:
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};