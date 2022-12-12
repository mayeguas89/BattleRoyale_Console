cmake_minimum_required(VERSION 3.14)
project(BattleRoyale VERSION 0.1.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)


# FetchContent_Declare(tabulate
#   GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
#   GIT_TAG v1.4
#   GIT_PROGRESS TRUE
# )
# FetchContent_MakeAvailable(tabulate)

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.12.0
  GIT_PROGRESS TRUE
  )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
  
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
)

target_compile_features(battleroyalecore PRIVATE cxx_std_17)

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
