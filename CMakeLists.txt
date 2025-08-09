cmake_minimum_required(VERSION 3.16)
project(ChannelsGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

add_executable(ChannelsGenerator
    src/main.cpp
    src/ChannelManager.cpp
    src/Parameter.cpp
    src/ParameterModel.cpp
)

target_include_directories(ChannelsGenerator PRIVATE src)
target_link_libraries(ChannelsGenerator PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::QuickControls2)

# If using qrc to include QML in resources:
#qt6_add_resources(RESOURCES qml.qrc)
#target_sources(ChannelGenerator PRIVATE ${RESOURCES})
