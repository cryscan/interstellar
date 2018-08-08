include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES */*.cpp)


find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

add_executable(park main.cpp ${SOURCES})
target_link_libraries(park ${GLUT_LIBRARY} ${OPENGL_LIBRARY})