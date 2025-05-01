#include <GL/glut.h>

struct Edge {
    float x1, y1, x2, y2;
};

// Polygon vertex coordinates
Edge polygon[] = {
    {100, 150, 200, 250},
    {200, 250, 300, 200},
    {300, 200, 250, 100},
    {250, 100, 150, 100},
    {150, 100, 100, 150}
};

int numEdges = sizeof(polygon) / sizeof(polygon[0]);

void drawPolygonOutline() {
    glColor3f(0.0, 0.0, 0.0); // Black outline
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numEdges; i++) {
        glVertex2f(polygon[i].x1, polygon[i].y1);
    }
    glEnd();
}

void scanlineFill() {
    int ymin = 480, ymax = 0;

    // Find min and max Y
    for (int i = 0; i < numEdges; i++) {
        if (polygon[i].y1 < ymin) ymin = polygon[i].y1;
        if (polygon[i].y1 > ymax) ymax = polygon[i].y1;
        if (polygon[i].y2 < ymin) ymin = polygon[i].y2;
        if (polygon[i].y2 > ymax) ymax = polygon[i].y2;
    }

    for (int y = ymin; y <= ymax; y++) {
        int xIntersect[10], count = 0;

        for (int i = 0; i < numEdges; i++) {
            float x1 = polygon[i].x1, y1 = polygon[i].y1;
            float x2 = polygon[i].x2, y2 = polygon[i].y2;

            if (y1 == y2) continue; // Ignore horizontal edges

            if ((y >= y1 && y < y2) || (y >= y2 && y < y1)) {
                float x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                xIntersect[count++] = x;
            }
        }

        // Sort intersections
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (xIntersect[i] > xIntersect[j]) {
                    int temp = xIntersect[i];
                    xIntersect[i] = xIntersect[j];
                    xIntersect[j] = temp;
                }
            }
        }

        // Fill pixels between pairs
        glColor3f(1.0, 0.0, 0.0); // Red fill
        glBegin(GL_LINES);
        for (int i = 0; i < count; i += 2) {
            glVertex2i(xIntersect[i], y);
            glVertex2i(xIntersect[i + 1], y);
        }
        glEnd();
    }
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygonOutline();
    scanlineFill();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0); // white background
    glColor3f(0.0, 0.0, 0.0);       // black drawing color
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scanline Polygon Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
