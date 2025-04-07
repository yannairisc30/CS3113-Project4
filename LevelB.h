/**
* Author:Yannairis Cruz
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
#pragma once
#include "Scene.h"

class LevelB : public Scene {
public:
    //static const int ENEMY_COUNT = 2;

    ~LevelB();

    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};
