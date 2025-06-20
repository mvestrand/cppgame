#include <simple_module.h>

/* #region ECS_COMPONENT_DECLARE(Position); */
ecs_entity_t FLECS_IDPositionID_;
/* #endregion */

ECS_COMPONENT_DECLARE(Velocity);

void Move(ecs_iter_t *it) {
    Position *p = ecs_field(it, Position, 0);
    Velocity *v = ecs_field(it, Velocity, 1);

    for (int i = 0; i < it->count; i ++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
    }
}



void SimpleModuleImport(ecs_world_t *world) {
    // Create the module entity. The PascalCase module name is translated to a
    // lower case path for the entity name, like "simple.module".

    /*#region ECS_MODULE(world, SimpleModule);*/
    ecs_entity_t FLECS_IDSimpleModuleID_ = 0;
    { 
        ecs_component_desc_t desc = {0}; 
        desc.entity = FLECS_IDSimpleModuleID_; 
        FLECS_IDSimpleModuleID_ = ecs_module_init(world, "SimpleModule", &desc);
        ecs_set_scope(world, FLECS_IDSimpleModuleID_); 
    } 
    (void)FLECS_IDSimpleModuleID_;
    /* #endregion */

    // All contents of the module are created inside the module's namespace, so
    // the Position component will be created as simple.module.Position

    /* #region ECS_COMPONENT_DEFINE(world, Position); */
    { 
        ecs_component_desc_t desc = {0}; 
        ecs_entity_desc_t edesc = {0};
        edesc.id = FLECS_IDPositionID_; 
        edesc.use_low_id = 1; 
        edesc.name = "Position"; 
        edesc.symbol = "Position"; 
        desc.entity = ecs_entity_init(world, &edesc);
        desc.type.size = ((ecs_size_t)(sizeof(Position))); 
        desc.type.alignment = (int64_t)__alignof(Position); 
        FLECS_IDPositionID_ = ecs_component_init(world, &desc); 
    } 
    if (!(FLECS_IDPositionID_ != 0)) { 
        ecs_assert_log_((2), "ecs_id(Position) != 0", 
            "C:\\Users\\Max\\proj\\cgame\\src\\simple_module.c", 40, 
            "failed to create component %s", "Position"); 
            ecs_os_api.abort_(); 
        } 
        (void)( 
               (!!(FLECS_IDPositionID_ != 0)) 
            || (_wassert(L"FLECS_IDPositionID_ != 0", L"C:\\Users\\Max\\proj\\cgame\\src\\simple_module.c", 
                        (unsigned)(40)), 
                0)
        );
    /* #endregion */
    ECS_COMPONENT_DEFINE(world, Velocity);

    /* #region     ECS_SYSTEM(world, Move, EcsOnUpdate, Position, Velocity); */
    ecs_entity_t FLECS_IDMoveID_ = 0; 
    { 
        ecs_system_desc_t desc = {0}; 
        ecs_entity_desc_t edesc = {0}; 
        ecs_id_t add_ids[3] = { 
            ( (EcsOnUpdate) 
                ? (ECS_PAIR | ( (((uint64_t)(EcsDependsOn)) << 32) + ((uint32_t)((EcsOnUpdate))))) 
                : 0), 
            (EcsOnUpdate), 
            0 
        }; 
        edesc.id = FLECS_IDMoveID_; 
        edesc.name = "Move"; 
        edesc.add = add_ids;

        desc.entity = ecs_entity_init(world, &edesc); 
        desc.query.expr = "Position, Velocity"; 
        desc.callback = Move; 
        FLECS_IDMoveID_ = ecs_system_init(world, &desc); 
    } 
    // 
    if (!(FLECS_IDMoveID_ != 0)) { 
        ecs_assert_log_((2), "ecs_id(Move) != 0", "C:\\Users\\Max\\proj\\cgame\\src\\simple_module.c", 68, 
            "failed to create system %s", "Move"); 
        ecs_os_api.abort_(); 
    } 
    (void)( (!!(FLECS_IDMoveID_ != 0)) || (_wassert(L"FLECS_IDMoveID_ != 0", L"C:\\Users\\Max\\proj\\cgame\\src\\simple_module.c", (unsigned)(68)), 0) 
    ); 
    ecs_entity_t Move = FLECS_IDMoveID_; 
    (void)FLECS_IDMoveID_; 
    (void)Move;
    /* #endregion */
}