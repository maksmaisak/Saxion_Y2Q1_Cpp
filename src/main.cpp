#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>
#include <optional>
#include "Messaging.h"
#include "Engine.h"
#include "Actor.h"
#include "Transformable.h"
#include "Rigidbody.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "WrapAroundScreenSystem.h"
#include "FlickerSystem.h"
#include "PlayerControlsSystem.h"

#include "Collision.h"

#include "Factory.h"

using uint = unsigned int;

const uint WIDTH  = 1600;
const uint HEIGHT = 1200;

const uint NUM_ASTEROIDS = 10;

struct Test : Receiver<en::Collision>, Receiver<int>, Receiver<float> {

    void receive(const int& num) override {
        std::cout << "received " << num << std::endl;
    }

    void receive(const float& num) override {
        std::cout << "received " << num << std::endl;
    }

    void receive(const en::Collision& info) override {
        std::cout << "received Collision" << std::endl;
    }
};

int main() {

    {
        Test a;
        Receiver<int>::accept(1);
        Test b[2];
        Receiver<int>::accept(2);
    }
    Receiver<int>::accept(3);

    Engine engine(WIDTH, HEIGHT);

    {
        engine.addSystem<RenderSystem>();
        engine.addSystem<PhysicsSystem>();

        engine.addSystem<PlayerControlsSystem>();

        engine.addSystem<WrapAroundScreenSystem>();
        //engine.addSystem<FlickerSystem>();
    }

    Test receiver;

    EntityRegistry& registry = engine.getRegistry();

    {
        Entity entity = registry.makeEntity();
        registry.add<en::Transformable>(entity);
        registry.add<std::shared_ptr<sf::Drawable>>(entity, std::make_shared<sf::CircleShape>(10.f, 20));
        auto& rb = registry.add<Rigidbody>(entity);
        rb.velocity = {100.f, 800.f};
        rb.radius = 10.f;
        //registry.destroy(entity);
    }

    game::makePlayer(engine);
    for (int i = 0; i < NUM_ASTEROIDS; ++i) {
        game::makeAsteroid(engine);
    }

    engine.run();

    return 0;
}
