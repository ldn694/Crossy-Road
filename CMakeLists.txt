cmake_minimum_required(VERSION 3.16)
project(CrossyRoad LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(include)


add_executable(CrossyRoad 
    src/main.cpp
    src/Application.cpp
    src/Aircraft.cpp
    src/Command.cpp
    src/CommandQueue.cpp
    src/Entity.cpp
    src/GameState.cpp 
    src/MenuState.cpp
    src/PauseState.cpp
    src/Player.cpp
    src/SceneNode.cpp
    src/SpriteNode.cpp
    src/State.cpp
    src/StateStack.cpp
    src/TitleState.cpp
    src/Utility.cpp
    src/World.cpp
    src/Context.cpp
    src/Clickable.cpp
    src/ClickableList.cpp
    src/Button.cpp
    src/Choice.cpp
    src/GameStartState.cpp
    src/Animation.cpp
    src/Road.cpp
    src/Railways.cpp
    src/River.cpp
    src/SRoad.cpp
    src/Land.cpp
    )
target_link_libraries(CrossyRoad PRIVATE sfml-graphics)
target_compile_features(CrossyRoad PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CrossyRoad
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CrossyRoad>
        VERBATIM)
endif()

install(TARGETS CrossyRoad)
