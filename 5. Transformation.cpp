#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> pntX;
vector<int> pntY;
int edges;
int choice;
int transx, transy;
double scalex, scaley;
double angleRad;

double roundf(double val) {
    return floor(val + 0.5);
}

void drawPolygon() {
    glColor3f(0.0, 0.0, 0.0); // Original polygon - black
    glBegin(GL_POLYGON);
    for (int i = 0; i < edges; ++i) {
        glVertex2i(pntX[i], pntY[i]);
    }
    glEnd();
}

void drawPolygonTrans(int tx, int ty) {
    glColor3f(1.0, 0.0, 0.0); // Red for translated
    glBegin(GL_POLYGON);
    for (int i = 0; i < edges; ++i) {
        glVertex2i(pntX[i] + tx, pntY[i] + ty);
    }
    glEnd();
}

void drawPolygonScale(double sx, double sy) {
    glColor3f(0.0, 1.0, 0.0); // Green for scaled
    glBegin(GL_POLYGON);
    for (int i = 0; i < edges; ++i) {
        glVertex2i(roundf(pntX[i] * sx), roundf(pntY[i] * sy));
    }
    glEnd();
}

void drawPolygonRotation(double angleRad) {
    double centerX = 0, centerY = 0;
    for (int i = 0; i < edges; ++i) {
        centerX += pntX[i];
        centerY += pntY[i];
    }
    centerX /= edges;
    centerY /= edges;

    glColor3f(0.0, 0.0, 1.0); // Blue for rotated
    glBegin(GL_POLYGON);
    for (int i = 0; i < edges; ++i) {
        double x = pntX[i] - centerX;
        double y = pntY[i] - centerY;

        double rotatedX = x * cos(angleRad) - y * sin(angleRad) + centerX;
        double rotatedY = x * sin(angleRad) + y * cos(angleRad) + centerY;

        glVertex2f(rotatedX, rotatedY);
    }
    glEnd();
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glColor3f(0.0f, 0.0f, 0.0f);      // Draw color
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygon();

    if (choice == 1) {
        drawPolygonTrans(transx, transy);
    } else if (choice == 2) {
        drawPolygonScale(scalex, scaley);
    } else if (choice == 3) {
        drawPolygonRotation(angleRad);
    }

    glFlush();
}

int main(int argc, char **argv) {
    int angle;
    cout << "Enter your choice:\n";
    cout << "1. Translation\n";
    cout << "2. Scaling\n";
    cout << "3. Rotation\n";
    cout << "4. Exit\n";
    cin >> choice;

    if (choice == 4) return 0;

    cout << "\nFor Polygon:\n";
    cout << "Enter number of edges: ";
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        int x, y;
        cout << "Enter coordinates for vertex " << i + 1 << ": ";
        cin >> x >> y;
        pntX.push_back(x);
        pntY.push_back(y);
    }

    if (choice == 1) {
        cout << "Enter the translation factor for x and y: ";
        cin >> transx >> transy;
    } else if (choice == 2) {
        cout << "Enter the scaling factor for x and y: ";
        cin >> scalex >> scaley;
    } else if (choice == 3) {
        cout << "Enter the angle of rotation (in degrees): ";
        cin >> angle;
        angleRad = angle * M_PI / 180.0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Basic Polygon Transformations");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
