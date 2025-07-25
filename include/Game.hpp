#ifndef SOBA_GAME_HPP
#define SOBA_GAME_HPP

#include <flecs.h>

namespace soba {

    class Game {
    public:
        flecs::world ecs;
        int frame_num = 0;
        bool should_quit = false;

        Game();
        ~Game();
    };
}

#endif // SOBA_GAME_HPP