cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 0.1.0)
include(FetchContent)

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
  
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmt)

add_library(
    ProjectCore STATIC
    src/game_manager.cpp
    src/interface.cpp
    src/player.cpp
)

target_include_directories(
    ProjectCore
    PUBLIC
    src
)

target_link_libraries(
    ProjectCore 
    PUBLIC 
    fmt::fmt
)

target_compile_features(ProjectCore PRIVATE cxx_std_17)

add_executable(
    MyProject 
    src/main.cpp
)
    
target_link_libraries(
    MyProject 
    PRIVATE
    ProjectCore
)
target_compile_features(MyProject PRIVATE cxx_std_17)


add_executable(
    MyProjectTest
    test/main.cpp
    )
    
target_compile_features(MyProjectTest PRIVATE cxx_std_17)
target_link_libraries(
    MyProjectTest
    PUBLIC
    ProjectCore
    gmock
    gmock_main
)

# target_include_directories(MyProject PRIVATE "C:/Repos/fmt/include")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
