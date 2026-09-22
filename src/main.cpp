#include "game.hpp"
#include "core/window.hpp"

int main() {
    Game game{};
    game.init();
    game.run();
    game.shutdown();
    return 0;
}
