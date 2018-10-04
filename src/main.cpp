#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {

    Engine& engine = Engine::getInstance();

    //std::shared_ptr<Entity> pEntity = engine.makeEntity();
    //pEntity->destroy();

    engine.makeEntity<Player>()->setPosition(500, 600);

    //engine.makeEntity<>();
    //engine.makeEntity<>();
    //engine.makeEntity<>();

    engine.run();

    return 0;
}