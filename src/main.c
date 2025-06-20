#include <stdio.h>
#include <flecs.h>

// #include <colsim.h>
// #region Declare MyTag2
//ECS_TAG_DECLARE(MyTag2);
ECS_TAG_DECLARE(MyTag2);
// #endregion

#include <simple_module.h>
#include <stdio.h>

void PrintPosition(ecs_iter_t *it) {
    Position *p = ecs_field(it, Position, 0);

    for (int i = 0; i < it->count; i ++) {
        printf("p = {%f, %f} (system)\n", p[i].x, p[i].y);
    }
}

int main_simple(int argc, char *argv[]) {
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    // Import module which calls the SimpleModuleImport function
    ECS_IMPORT(world, SimpleModule);

    // Create system that uses component from module. Note how the component
    // identifier is prefixed with the module.
    ECS_SYSTEM(world, PrintPosition, EcsOnUpdate, simple.module.Position);

    // Create entity with components imported from module
    ecs_entity_t e = ecs_insert(world, ecs_value(Position, {10, 20}));
                     ecs_set(world, e, Velocity, {1, 2});

    // Call progress which runs imported Move system
    ecs_progress(world, 0);

    // Use component from module in operation
    const Position *p = ecs_get(world, e, Position);
    printf("p = {%f, %f} (get)\n", p->x, p->y);

    return ecs_fini(world);

    // Output:
    //   p = {11.000000, 22.000000} (system)
    //   p = {11.000000, 22.000000} (get)
}

int main_app_init(ecs_world_t *world) {
  FILE *fptr;
  fptr = fopen("c_world.json", "w");
  ecs_world_to_json_desc_t desc = {.serialize_builtin=true, .serialize_modules=true };
  char *json = ecs_world_to_json(world, &desc);
  fprintf(fptr, json);
  fclose(fptr);
}

int main(int argc, char *argv[]) {
  return main_simple(argc, argv);
}


// int main(int argc, char *argv[]) {
//   ecs_world_t *world = ecs_init();

//   //  ECS_TAG(world, MyTag);
//   // @{ #region
//   ecs_entity_t FLECS_IDMyTagID_;
//   ecs_entity_t MyTag = 0;
//   { 
//     ecs_entity_desc_t desc = {0};
//     desc.id = MyTag; 
//     desc.name = "MyTag"; 
//     desc.add_expr = "0"; 
//     MyTag = ecs_entity_init(world, &desc); 
//     FLECS_IDMyTagID_ = MyTag; 
//     if (!(MyTag != 0)) { 
//       ecs_assert_log_((2), "MyTag != 0", 
//         "C:\\Users\\Max\\proj\\cgame\\src\\main.c", 19, 
//         "failed to create entity %s", "MyTag"); 
//         ecs_os_api.abort_(); 
//     } 
//     (void)(    (!!(MyTag != 0)) /**/
//             || (_wassert(L"MyTag != 0", 
//                   L"C:\\Users\\Max\\proj\\cgame\\src\\main.c", 
//                   (unsigned)(19)), 
//                 0) 
//           ); 
//   } 
//   (void)MyTag; 
//   (void)FLECS_IDMyTagID_;
//   // @} #endregion


//   int res = ecs_app_run(world, &(ecs_app_desc_t) {
//     .delta_time = (1.0 / 60.0),
//     .target_fps = 60,
//     .enable_stats = true,         /**< Periodically collect statistics */
//     .enable_rest = true,          /**< Enables ECS access over HTTP, necessary for explorer */
//     //.threads = 4,               /**< Number of threads. */
//     //.frames = 3600,/* 1min */   /**< Number of frames to run (0 for infinite) */
//     //.port = 8000,               /**< HTTP port used by REST API */
//     .init = &main_app_init,   /**< If set, function is ran before starting the
//                                     * main loop. */
//   });
  
//   ecs_fini(world);
//   return res;
// }
