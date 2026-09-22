#include "core/window.hpp"
#include "game.hpp"

int main() {
    Game game{};
    game.init();
    game.run();
    game.shutdown();
    return 0;
}
