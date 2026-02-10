#include <iostream>
#include "StateMachine.h"
#include "input.h"

int main(int argc, char* argv[]) {
    StateMachine application;
    SDL_Event event;

    if (!application.init()) {
        return EXIT_FAILURE;
    }

    bool running = true;

    while (running) {
        update_key_buffer(event); 

        if (quit_requested) {
            running = false;
            break;
        }

        application.current_state->update();
        application.current_state->render();
    }

    return EXIT_SUCCESS;
}
