#include<GL/glut.h>
#include<iostream>
using namespace std;

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ellipse");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(x + 200, y + 200);
    glEnd();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    //int x = 0;

    float rx = 100; //Semi major Axis
    float ry = 50; //Semi minor Axis

    //First region, i.e. slope>1
    float x = 0;
    float y = ry;

    float dp1 = (ry * ry) - (rx * rx) * ry + (0.25) * (rx * rx);

    float dx = 2 * (ry * ry) * x;
    float dy = 2 * (rx * rx) * y;

    while (dx < dy) {
        plot(x, y);
        plot(-x, y);
        plot(x, -y);
        plot(-x, -y);

        if (dp1 < 0) {
            x++;
            dx = 2 * (ry * ry) * x;
            dp1 += dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = 2 * (ry * ry) * x;
            dy = 2 * (rx * rx) * y;
            dp1 += dx - dy + (ry * ry);
        }
    }

    float dp2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y - 1) * (y - 1) - (rx * rx) * (ry * ry);

    //Above the X-Axis
    while (y > 0) {
        plot(x, y);
        plot(-x, y);
        plot(x, -y);
        plot(-x, -y);

        if (dp2 < 0) {
            x++;
            y--;
            dx = dx - 2 * (ry * ry); //* x;
            dy = dy - 2 * (rx * rx); //* y;
            dp2 += dx - dy + (rx * rx);
        }
        else {
            y--;
            dy = 2 * (rx * rx) * y;
            dp2 = dp2 - dy + (rx * rx);
        }
    }

    glEnd();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}