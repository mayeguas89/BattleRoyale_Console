cmake_minimum_required(VERSION 3.14)
project(BattleRoyale VERSION 0.1.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# set(BOOST_INCLUDE_LIBRARIES algorithm)
# set(BOOST_ENABLE_CMAKE ON)

# FetchContent_Declare(
#   Boost
#   GIT_REPOSITORY https://github.com/boostorg/boost.git
#   GIT_TAG boost-1.81.0
# )
# FetchContent_MakeAvailable(Boost)

FetchContent_Declare(tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG v1.4
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(tabulate)

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.12.0
  GIT_PROGRESS TRUE
  )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
  GIT_PROGRESS TRUE
  )

FetchContent_MakeAvailable(json)
  
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmt)

add_library(
    battleroyalecore STATIC
    src/game_manager.cpp
    src/interface.cpp
    src/player.cpp
    src/tournament.cpp
    src/character.cpp
    src/turn_action.cpp
)

target_include_directories(
    battleroyalecore
    PUBLIC
    src
)

target_link_libraries(
    battleroyalecore 
    PUBLIC 
    fmt::fmt
    nlohmann_json::nlohmann_json
    tabulate::tabulate
)

target_compile_features(battleroyalecore PRIVATE cxx_std_17)

add_custom_command(
        TARGET battleroyalecore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/cfg/final_melee_weapons.json
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/cfg/final_melee_weapons.json)

add_custom_command(
        TARGET battleroyalecore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/cfg/final_ranged_weapons.json
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/cfg/final_ranged_weapons.json)

add_custom_command(
        TARGET battleroyalecore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/cfg/final_spells.json
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/cfg/final_spells.json)

add_custom_command(
        TARGET battleroyalecore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/cfg/final_armor.json
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/cfg/final_armor.json)

add_executable(
    battleroyale 
    src/main.cpp
)
    
target_link_libraries(
    battleroyale 
    PRIVATE
    battleroyalecore
)

target_compile_features(battleroyale PRIVATE cxx_std_17)


add_executable(
    battleroyaleTest
    test/main.cpp
    )
    
target_compile_features(battleroyaleTest PRIVATE cxx_std_17)
target_link_libraries(
    battleroyaleTest
    PUBLIC
    battleroyalecore
    gmock
    gmock_main
)

# target_include_directories(MyProject PRIVATE "C:/Repos/fmt/include")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
