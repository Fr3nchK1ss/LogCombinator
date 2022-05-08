cmake_minimum_required(VERSION 3.16)

project(LogCombinator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(PROJECT "logCombinator")

qt_add_executable(${PROJECT}
    main.cpp
    logmodel.h logmodel.cpp
    logcontroller.h logcontroller.cpp
    logsfpmodel.h logsfpmodel.cpp
)

#qt_add_resources(${PROJECT} "particles"
#    PREFIX "/"
#    FILES
#        resources/colors.png
#        resources/sphere.png
#)

qt_add_qml_module(${PROJECT}
    URI LogCombinator
    VERSION 1.0
    QML_FILES main.qml
              CheckboxDelegate.qml
              CombineButton.qml
              ParticlesRain.qml
)


target_compile_definitions(${PROJECT}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT}
    PRIVATE Qt6::Quick)
