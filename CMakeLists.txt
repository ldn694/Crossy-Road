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
    src/Command.cpp
    src/CommandQueue.cpp 
    src/Entity.cpp
    src/GameState.cpp 
    src/MenuState.cpp
    src/PauseState.cpp
    src/Player.cpp
    src/SceneNode.cpp
    src/ScrollBar.cpp
    src/ScrollBarList.cpp 
    src/ScoreboardState.cpp
    src/SettingState.cpp
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
    src/FakeEntity.cpp
    src/Animal.cpp
    src/Zone.cpp
    src/RoadList.cpp
    src/Rock.cpp
    src/TypeBox.cpp
    src/Category.cpp
    src/FloatingLog.cpp
    src/AirEntity.cpp
    src/Tree.cpp
    src/Car.cpp
    src/GameOverState.cpp
    src/Scoreboard.cpp
    src/LoadingState.cpp
    src/Train.cpp
    src/TrafficLight.cpp
    src/Rain.cpp
    src/StopLight.cpp
    src/Settings.cpp
    src/SoundPlayer.cpp
    src/MusicPlayer.cpp
    src/LandWithAnimal.cpp
    src/WalkingAnimal.cpp
    src/Switch.cpp
    src/KeyBindingButton.cpp
    )

target_link_libraries(CrossyRoad PRIVATE sfml-audio)
target_link_libraries(CrossyRoad PRIVATE sfml-graphics)
target_compile_features(CrossyRoad PRIVATE cxx_std_17)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")

if(WIN32)
    add_custom_command(
        TARGET CrossyRoad
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CrossyRoad>
        VERBATIM)
endif()

install(TARGETS CrossyRoad)
