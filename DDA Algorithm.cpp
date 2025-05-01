#include <GL/glut.h>
#include <cmath> // for fabs() and round()

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // Drawing color: white
    glPointSize(2.0);                 // Pixel size
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);       // Coordinate system
}

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void dda(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        setPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    dda(50, 50, 450, 400); // Draw line from (50,50) to (450,400)
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
