file(GLOB WINCONW_CORE_SOURCES src/*.cpp src/basic_widgets/*.cpp)

add_library(winconw.core STATIC ${WINCONW_CORE_SOURCES})
target_include_directories(winconw.core PUBLIC include)