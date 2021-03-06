//
// Created by hsy on 2018/8/6.
//

#include <system/engine.h>
#include <objects/spaceship.h>

spaceship::spaceship(const glm::vec3& offset, GLfloat angle) :
        object{engine::get_instance().get_model("rocket")},
        offset{offset},
        angle{angle},
        ratio{1.0} {}

void spaceship::update() {
    object::update();
    ratio = 0.8 + 0.2 * cosf(angle / 180);
    angle += 4.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1] + 0.2f, offset[2]);
    glRotatef(angle, 0, 1.0f, 0);
    glRotatef(angle, 1.0f, 0, 0);
    glRotatef(angle, 0, 0, 1.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glScalef(ratio, ratio, ratio);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}

void spaceship::render(int pass) {
    glm::mat4 projection;

    switch (pass) {
        case 1:
            // Draw outline.
            glEnable(GL_STENCIL_TEST);
            // Do not draw on color buffer and depth buffer.
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);

            // Always pass the test, all what draws later will make the test fail.
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            glStencilMask(0xFF);
            glClear(GL_STENCIL_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glMultMatrixf(reinterpret_cast<const GLfloat*>(&transform));
            glScalef(1.2f, 1.2f, 1.2f);
            if (mesh != nullptr)
                mesh->render();
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glStencilMask(0x00);

            glStencilFunc(GL_EQUAL, 0, 0xFF);
            // Draw nothing when stencil value is 0.

            glStencilFunc(GL_EQUAL, 1, 0xFF);
            // Draw a rectangle on the whole screen.

            glGetFloatv(GL_PROJECTION_MATRIX, reinterpret_cast<GLfloat*>(&projection));
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glBegin(GL_QUADS);
            glBindTexture(GL_TEXTURE_2D, 0);
            glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(-1.0f, 1.0f);
            glVertex2f(-1.0f, -1.0f);
            glVertex2f(1.0f, -1.0f);
            glEnd();
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glMultMatrixf(reinterpret_cast<const GLfloat*>(&projection));

            glDepthMask(GL_TRUE);
            glDisable(GL_STENCIL_TEST);
            break;

        case 2:
            // Or render the normal model.
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glMultMatrixf(reinterpret_cast<const GLfloat*>(&transform));
            if (mesh != nullptr)
                mesh->render();
            glPopMatrix();
            break;

        default:
            break;
    }
}


