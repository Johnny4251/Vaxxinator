#include <iostream>
#include "DemoState.h"
#include "input.h"
#include "Sprite.h"

#define STATE_NAME "DemoState"

enum class Dir { Front, Back, Side };
int x, y, speed;
Dir lastDir;
Sprite* player;

DemoState::DemoState(StateMachine* machine)
    : State(STATE_NAME, machine){}

void DemoState::enter() {
    x,y = 50;
    speed = 3;
    player = nullptr;
    
    std::cout << "Entering " << STATE_NAME << std::endl;
    clear_keys();

    player = new Sprite(state_machine->renderer);
    player->setScale(4);
    player->setPosition(x, y);
    player->setFlipX(false);

    // Stand
    player->addAnimation("stand_front", "assets/sprites/roberto/s_player_F_sheet.png",  16, 16, 10, -1, true);
    player->addAnimation("stand_back",  "assets/sprites/roberto/s_player_B_sheet.png",  16, 16, 10, -1, true);
    player->addAnimation("stand_side",  "assets/sprites/roberto/s_player_S_sheet.png",  16, 16, 10, -1, true);

    // Run
    player->addAnimation("run_front",   "assets/sprites/roberto/s_player_run_F_sheet.png", 16, 16, 6, -1, true);
    player->addAnimation("run_back",    "assets/sprites/roberto/s_player_run_B_sheet.png", 16, 16, 6, -1, true);
    player->addAnimation("run_side",    "assets/sprites/roberto/s_player_run_S_sheet.png", 16, 16, 6, -1, true);

    player->setBaseAnimation("stand_front", true);
}

void DemoState::update() {
    bool moving = false;

    bool left  = key_down(SDL_SCANCODE_LEFT);
    bool right = key_down(SDL_SCANCODE_RIGHT);
    bool up    = key_down(SDL_SCANCODE_UP);
    bool down  = key_down(SDL_SCANCODE_DOWN);

    if (right) { x += speed; moving = true; lastDir = Dir::Side; player->setFlipX(false); }
    if (left)  { x -= speed; moving = true; lastDir = Dir::Side; player->setFlipX(true); }

    if (!left && !right) {
        if (up)   { y -= speed; moving = true; lastDir = Dir::Back; }
        if (down) { y += speed; moving = true; lastDir = Dir::Front; }
    } else {
        if (up)   { y -= speed; moving = true; }
        if (down) { y += speed; moving = true; }
    }

    const char* anim = nullptr;
    if (moving) {
        if (lastDir == Dir::Front) anim = "run_front";
        else if (lastDir == Dir::Back) anim = "run_back";
        else anim = "run_side";
    } else {
        if (lastDir == Dir::Front) anim = "stand_front";
        else if (lastDir == Dir::Back) anim = "stand_back";
        else anim = "stand_side";
    }

    player->setBaseAnimation(anim, false);

    while (has_key()) {
        SDL_Keycode key = pop_key();
        if (key == SDLK_ESCAPE) {
            state_machine->transition("MainMenu");
            return;
        }
    }

    player->setPosition(x, y);
    player->update();
}

void DemoState::render() {
    SDL_SetRenderDrawColor(state_machine->renderer, 0xff, 0xff, 0xff, 255);
    SDL_RenderClear(state_machine->renderer);
    player->render();
    SDL_RenderPresent(state_machine->renderer);
}

void DemoState::exit() {
    delete player;
    player = nullptr;
    std::cout << "Exiting " << STATE_NAME << std::endl;
}
