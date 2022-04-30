cmake_minimum_required(VERSION 3.16)

project(LogCombinator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appLogCombinator
    main.cpp
    logmodel.h logmodel.cpp
    logcontroller.h logcontroller.cpp
    logsfpmodel.h logsfpmodel.cpp
)

qt_add_qml_module(appLogCombinator
    URI LogCombinator
    VERSION 1.0
    QML_FILES main.qml
              CheckboxDelegate.qml
              CombineButton.qml
)


target_compile_definitions(appLogCombinator
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appLogCombinator
    PRIVATE Qt6::Quick)
