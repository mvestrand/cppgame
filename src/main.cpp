#include <stdio.h>
#include <flecs.h>


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
using flecs::world;
using flecs::entity;

struct engine {
    



    engine(world &ecs) {

    }
};




int main(int argc, char *argv[]) {
    flecs::world world(argc, argv);
    world.import<flecs::stats>();
    world.set<flecs::Rest>({});

    world.import<engine>();


    while (world.progress()) {

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
