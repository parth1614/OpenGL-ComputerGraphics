#include "./freeglut-3.2.1/include/GL/freeglut.h"

#include<iostream>
#include<vector>
using namespace std;
float r=100;

void init()
{
  glClearColor(1.0,1.0,1.0,0.0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0.0,640.0,0.0,480.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glPointSize(1.0f);
}

struct Color{
  GLfloat r;
  GLfloat g;
  GLfloat b;
};

void plotcircle(int x,int y){
  glBegin(GL_POINTS);
  glVertex2f(x+100,y+100);
  glVertex2f(-x+100,y+100);
  glVertex2f(x+100,-y+100);
  glVertex2f(-x+100,-y+100);

  glVertex2f(y+100,x+100);
  glVertex2f(-y+100,x+100);
  glVertex2f(y+100,-x+100);
  glVertex2f(-y+100,-x+100);
  glEnd();
}

Color getpixel(GLint x,GLint y){
  Color color;
  glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
  return color;
}

void setpixel(GLint x,GLint y,Color color){
  glColor3f(color.r,color.g,color.b);
  glBegin(GL_POINTS);
  glVertex2f(x,y);
  glEnd();
  glFlush();
}

void boundaryfill(GLint x,GLint y,Color bcolor,Color fcolor){
  Color ccolor = getpixel(x,y);
  if(ccolor.r != bcolor.r && 
    ccolor.g != bcolor.g &&
    ccolor.b != bcolor.b){
    setpixel(x,y,fcolor);
    boundaryfill(x+1,y,bcolor,fcolor);
    // boundaryfill(x+1,y+1,bcolor,fcolor);
    boundaryfill(x,y+1,bcolor,fcolor);
    // boundaryfill(x-1,y+1,bcolor,fcolor);
    boundaryfill(x-1,y,bcolor,fcolor);
    // boundaryfill(x+1,y-1,bcolor,fcolor);
    boundaryfill(x,y-1,bcolor,fcolor);
    // boundaryfill(x-1,y-1,bcolor,fcolor);
    }
}


void display()
{ 
  // Used to initialise display
  glClear(GL_COLOR_BUFFER_BIT);
  // glColor3f(0.0,0.0,0.0);
  // glPointSize(4.0);

  //initial decision parameter P0 = 1-r
  int p = 3 - 2*r;
  int x = 0;
  int y = r;

  while(x<y){
    if(p<0){
      plotcircle(x,y);
      p = p + 4*x + 6;
      x=x+1;
      y=y;
    }
    else{
      plotcircle(x,y);
      p = p + 4*x - 4*y + 10;
      x = x+1;
      y = y-1;
    }
  }
  glEnd();
  glFlush();

  Color fillcolor = {0.0f,0.0f,1.0f};
  Color boundary = {0.0f,0.0f,0.0f};

  // motion(100,150);
  boundaryfill(101,101,boundary,fillcolor);
  glEnd();
}


int main(int argc,char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  // glutInitWindowPosition(50,100);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(200,200);
  glutCreateWindow("Circle Plotting using midpoint Algo");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
