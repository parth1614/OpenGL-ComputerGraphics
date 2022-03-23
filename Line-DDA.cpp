#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line DDA");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    //DDA Algo Begins
    float x0, y0, x1, y1,dx, dy, xinc, yinc, steps;
    glBegin(GL_POINTS);
    x0 = 50;
    y0 = 50;
    x1 = 300;
    y1 = 100;
    // cin>>x0>>y0>>x1>>y1;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    xinc = dx/ steps;
    yinc = dy/ steps;

    for (int i = 1; i <= steps; ++i) {
        glVertex2i(x0, y0);
        x0 += xinc;
        y0 += yinc;
    }
    //Algo ends//

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {

    // cin>>x0>>y0>>x1>>y1;
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
