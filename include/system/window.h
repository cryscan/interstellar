//
// Created by lepet on 7/30/2018.
//

#ifndef P3_WINDOW_H
#define P3_WINDOW_H

namespace window {
    // Open the window. Called at the beginning.
    void open(int argc, char** argv);
    // Init game engine. Called after window is opened.
    void init();
    // Close the window. Called at the end.
    void close();
    // Start the main loop after the window and game is set up.
    void main_loop();
}

#endif //P3_WINDOW_H
