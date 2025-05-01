#include <GL/glut.h>
#include <iostream>
using namespace std;

int xc = 320, yc = 240; // Center of the circle

void plot_point(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

void bresenham_circle(int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    plot_point(x, y);

    while (x <= y) {
        x++;
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        plot_point(x, y);
    }

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int radius1 = 100;
    bresenham_circle(radius1);
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Background color: white
    glColor3f(0.0, 0.0, 0.0);         // Drawing color: black
    gluOrtho2D(0, 640, 0, 480);       // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Circle Drawing");

    Init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
