#include <GL/glut.h>

float rt = 0.0f;
float ballX = -0.5f;
float ballY = 0.0f;
float ballZ = 0.0f;

void init(int Width, int Height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    glEnable(GL_DEPTH_TEST); // enable depth testing

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 50.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(rt, 0.0f, -6.0f); // Move car left to right

    // Draw car body (rectangle-like polygon)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(0.4f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.4f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();

    // Draw wheels
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glutSolidSphere(0.3, 20, 20); // back wheel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ballX + 1.5, ballY, ballZ);
    glutSolidSphere(0.3, 20, 20); // front wheel
    glPopMatrix();

    // Update car position
    rt += 0.005f;
    if (rt > 2.0f)
        rt = -2.0f;

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Enable double buffer and depth
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Moving Car");

    init(640, 480);
    glutDisplayFunc(Draw);
    glutIdleFunc(Draw); // for continuous motion

    glutMainLoop();
    return 0;
}
