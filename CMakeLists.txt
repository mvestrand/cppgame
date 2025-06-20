cmake_minimum_required(VERSION 3.15...3.31)

project(
	SimpleFlecsApp
	VERSION 0.1
	LANGUAGES C CXX)

set(INC_DIR include)
set(SRC_DIR src)
set(APP_DIR ${SRC_DIR}/bin)
set(CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(FLECS_LIB flecs::flecs_static)

set(TARGET_NAME SimpleApp)
set(TARGET_DIR ${CUR_DIR})


set(FLECS_DIR extern/flecs)
add_subdirectory(${FLECS_DIR} ${CMAKE_CURRENT_BINARY_DIR}/flecs)


include(${FLECS_DIR}/cmake/target_default_compile_options.cmake)
include(${FLECS_DIR}/cmake/target_default_compile_warnings.cmake)
include(${FLECS_DIR}/cmake/target_default_compile_functions.cmake)

file(GLOB_RECURSE INC include/*.h include/*.hpp)
file(GLOB_RECURSE SRC src/*.c)
add_executable(${TARGET_NAME} ${SRC} ${INC})
message(STATUS "INC=${INC}")
message(STATUS "SRC=${SRC}")

target_include_directories(${TARGET_NAME} PUBLIC ${FLECS_DIR}/include)
target_include_directories(${TARGET_NAME} PUBLIC ${TARGET_DIR}/include)

target_link_libraries(${TARGET_NAME} ${FLECS_LIB})
target_default_compile_options_cxx(${TARGET_NAME})
target_default_compile_warnings_cxx(${TARGET_NAME})


# target_include_directories(${TARGET_NAME} PUBLIC include)
# target_include_directories(${TARGET_NAME} PUBLIC ${FLECS_DIR}/include)
# set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# if(WIN32)
# 	target_link_libraries(${TARGET_NAME} PUBLIC ${FLECS_LIB} wsock32 ws2_32)
# endif()

# enable_testing()
# add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})