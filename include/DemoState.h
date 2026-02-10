#pragma once
#include "DefaultState.h"

class Sprite;

class DemoState : public State {
public:
    DemoState(StateMachine* machine);

    void enter() override;
    void update() override;
    void render() override;
    void exit() override;
};