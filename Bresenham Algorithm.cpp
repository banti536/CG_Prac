#include <GL/glut.h>
#include <cmath>

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Background color: black
    glColor3f(1.0, 1.0, 1.0);          // Drawing color: white
    glPointSize(2.0);                  // Size of the point
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);        // Coordinate system
}

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        setPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham(50, 400, 450, 50);  // Draw line from (50,400) to (450,50)
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
