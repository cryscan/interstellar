//
// Created by lepet on 7/30/2018.
//

#include <GL/freeglut.h>
#include <GL/glext.h>
#include <system/engine.h>

namespace window {
    // Called when window is resized.
    void reshape(GLsizei width, GLsizei height) {
        if (height == 0)
            height = 1;
        GLfloat aspect = (GLfloat) width / (GLfloat) height;

        // We want to set projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, width, height);
        gluPerspective(45.0, aspect, 1.0, 20.0);
    }

    void display() {
        auto& engine = engine::get_instance();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        engine.render();
        glutSwapBuffers();
    }

    void mouse(int button, int state, int x, int y) {
        glm::vec<2, int> pos = {x, y};
        engine::get_instance().mouse(button, state, pos);
    }

    void motion(int x, int y) {
        glm::vec<2, int> pos = {x, y};
        engine::get_instance().motion(pos);
    }

    void key(unsigned char key, int x, int y) {
        if (key == 27)  // Escape in ASCII.
            exit(0);
    }

    void timer(int value) {
        engine::get_instance().update();
        glutPostRedisplay();

        static unsigned refresh = 30;
        glutTimerFunc(refresh, timer, 0);
    }

    void open(int argc, char** argv) {
        // Create the window.
        GLsizei width = 640, height = 480;
        glutInit(&argc, argv);
        glutInitWindowSize(width, height);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);

        glutCreateWindow("Interstellar Parking Lot");
        glutFullScreen();
    }

    void init() {
        glClearColor(0.0, 0.0, 0.0, 1.0);

        // Initialize other things.
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_MULTISAMPLE);
        glDisable(GL_LIGHTING);
        glShadeModel(GL_FLAT);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        // Initialize engine here.
        engine::get_instance().initialize();
    }

    void main_loop() {
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        glutKeyboardFunc(key);
        glutTimerFunc(0, timer, 0);

        glutMainLoop();
    }
}