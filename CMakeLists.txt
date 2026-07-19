cmake_minimum_required(VERSION 3.14)

project(SCSCore1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Concurrent)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/ExampleModule
)

add_executable(SCSCore1
    main.cpp
    Core/appbus.h Core/appbus.cpp
    Core/coredispatcher.h Core/coredispatcher.cpp

    Core/coremanager.h Core/coremanager.cpp
    Core/configmanager.h Core/configmanager.cpp
    Core/core.h Core/core.cpp
    Modules/ExampleModule/examplemodule.h Modules/ExampleModule/examplemodule.cpp
    Core/imodule.h
)

target_link_libraries(SCSCore1
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Concurrent
)

include(GNUInstallDirs)
install(TARGETS SCSCore1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
