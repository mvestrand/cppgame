#include <stdio.h>
#include <flecs.h>


struct engine {
    const float SIMULATION_TICK_LENGTH = 0.016667f;
    struct UpdateSimulation {};
    struct SimulationTick {};

    engine(flecs::world &world) {
        physics_tick = world.timer<SimulationTick>().interval(SIMULATION_TICK_LENGTH);
        world.component<UpdateSimulation>()
            .add(flecs::Phase)
            .depends_on(flecs::OnUpdate);

        world.system("PrintTime")
            .kind(flecs::OnUpdate)
            .run([](flecs::iter& it) {
                printf("Time: %f\n", it.delta_time());
            });
    }
    flecs::entity physics_tick;
};

int main(int argc, char *argv[]) {
    flecs::world world(argc, argv);
    world.import<engine>();
    return world.app()
        .enable_rest()
        .target_fps(60)
        .delta_time(1.0f / 60.0f)
        .run();
}
