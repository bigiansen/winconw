set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/winconw.testapp/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/winconw.testapp/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/winconw.testapp/)

file(GLOB WINCONW_TESTAPP_SOURCES src/*.cpp)
add_executable(winconw.testapp ${WINCONW_TESTAPP_SOURCES})
target_link_libraries(winconw.testapp winconw.core)