#include <flecs.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unordered_map>

#include "Repl.hpp"

using flecs::world;
using flecs::entity;

using namespace std;
using namespace soba;

int main(int argc, char *argv[]) {
    auto ecs = flecs::world();
    Repl repl;
    int frame_num = 0;
    while (true) {
        repl.process_stdin();
        this_thread::sleep_for(16ms);
        frame_num++;
    }

















    // flecs::world ecs(argc, argv);
    // ecs.import<flecs::stats>();
    // ecs.set<flecs::Rest>({});

    // entity UseMyPipeline = ecs.entity();
    // entity my_pipeline = ecs.pipeline()
    //     .with(UseMyPipeline)
    //     .build();

    // while (ecs.progress()) {

    // }

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
