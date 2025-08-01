#include "GameProvider.hpp"

using namespace std;

namespace soba {

    bool GameProvider::get_game(shared_ptr<Game> &game) const {
        auto current_game = _game.lock();
        if (_game.expired()) {
            return false;
        } else {
            game = current_game;
            return true;
        }
    }

    void GameProvider::attach_game(shared_ptr<Game> const &game) {
        _game = game;
    }

    void GameProvider::detach_game() {
        _game.reset();
    }
}
