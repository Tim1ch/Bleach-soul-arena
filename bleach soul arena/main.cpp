#include <iostream>
#include "engine.hpp"
#include "state_machine.hpp"

int main() {
    Engine * engine = Engine::create_instance();
    engine->game_loop();
    return  0;
}