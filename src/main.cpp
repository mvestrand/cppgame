#include <flecs.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unordered_map>

#include "Repl.hpp"
#include "Game.hpp"

using flecs::world;
using flecs::entity;

using namespace std;
using namespace soba;

void setup_ecs(flecs::world &ecs) {
    ecs.import<flecs::stats>();
    ecs.set<flecs::Rest>({});

    // entity UseMyPipeline = ecs.entity();
    // entity my_pipeline = ecs.pipeline()
    //     .with(UseMyPipeline)
    //     .build();
    
}

int main(int argc, char *argv[]) {
    auto game = make_shared<Game>();
    Repl repl;
    repl.attach_game(game);

    game->ecs = flecs::world(argc, argv);
    flecs::world &ecs = game->ecs;
    setup_ecs(ecs);

    while (!game->should_quit) {
        ecs.progress();
        repl.process_input();
        this_thread::sleep_for(16ms);
        game->frame_num++;
    }

    // Start Frame
    // - Fixed time-step(s) (16 ms)
    //      - Input
    //      - Physics update
    // - Frame time-step
    //      - Input
    //      - Gameplay update
    //      - UI
    // - Draw frame
    // End Frame

    return 0;
}





// struct engine {
//     const float SIMULATION_TICK_LENGTH = 0.016667f;
//     struct PhysicsUpdate {};
//     struct SimulationTick {};

//     engine(flecs::world &world) {
//         physics_tick = world.timer<SimulationTick>().interval(SIMULATION_TICK_LENGTH);
//         world.component<PhysicsUpdate>()
//             .add(flecs::Phase)
//             .tick_source(physics_tick)
//             .depends_on(flecs::PreUpdate);

//         world.system("PrintTime")
//             .kind(flecs::OnUpdate)
//             .run([](flecs::iter& it) {
//                 // printf("Time: %f\n", it.delta_time());
//             });
//     }
//     flecs::entity physics_tick;
// };
