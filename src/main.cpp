#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>
#include <optional>
#include <vector>
#include <utils/CustomTypeIndex.h>
#include "Messaging.h"
#include "Engine.h"
#include "Actor.h"
#include "Transformable.h"
#include "Rigidbody.h"
#include "DrawInfo.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "DestroyByTimerSystem.h"
#include "WrapAroundScreenSystem.h"
#include "FlickerSystem.h"
#include "PlayerControlsSystem.h"
#include "BreakAsteroidSystem.h"
#include "ShootSystem.h"
#include "DiagnosticsSystem.h"

#include "CustomTypeIndex.h"

#include "Collision.h"

#include "Factory.h"

using uint = unsigned int;

const uint Width  = 1600;
const uint Height = 1200;
const bool EnableVSync = true;

const uint NumAsteroids = 10;

struct Test : Receiver<en::Collision, int, float> {

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

template<typename T>
inline std::size_t idx = CustomTypeIndex<struct Dummy>::index<T>;

int main() {

    auto a = idx<en::Transformable>;
    auto b = idx<en::DrawInfo>;
    auto c = idx<float>;
    auto d = idx<en::Transformable>;

    Engine engine(Width, Height, EnableVSync);

    {
        engine.addSystem<RenderSystem>();
        engine.addSystem<PhysicsSystem>();

        engine.addSystem<DestroyByTimerSystem>();

        engine.addSystem<PlayerControlsSystem>();
        engine.addSystem<ShootSystem>();
        engine.addSystem<WrapAroundScreenSystem>();
        engine.addSystem<BreakAsteroidSystem>();
        //engine.addSystem<FlickerSystem>();

        engine.addSystem<DiagnosticsSystem>();
    }

    game::makePlayer(engine);

    for (int i = 0; i < NumAsteroids; ++i) {
        game::makeAsteroid(engine, (Asteroid::Size)lround(en::random(0.f, 2.f)));
    }

    engine.run();

    return 0;
}
