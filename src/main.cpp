#include <iostream>
#include <ctime>
#include <GL/glut.h>

#include <system/window.h>

int main(int argc, char **argv) {
    srand(time(nullptr));

    window::open(argc, argv);
    window::init();
    window::main_loop();

    return 0;
}