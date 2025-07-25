#ifndef SOBA_GAME_PROVIDER_HPP
#define SOBA_GAME_PROVIDER_HPP

#include <memory>

namespace soba {

    class Game;

    class GameProvider {
        private:
            std::weak_ptr<Game> _game;
        public:
            bool get_game(std::shared_ptr<Game> &game) const;
            void attach_game(std::shared_ptr<Game> const &game);
            void detach_game();
    };

}

#endif