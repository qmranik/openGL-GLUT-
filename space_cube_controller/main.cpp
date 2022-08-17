//
//  main.cpp
//  space_cube_controller
//
//  Created by anik on 6/22/22.
//

#include <iostream>
#include<stdio.h>
#include<GLUT/glut.h>
#include<math.h>
#define pi 3.142857

using namespace std;

int spin=0,speed=2;
float smallFactor = 0.4 ,xr=1 ,yr=1 ,zr=0 ;

void myInit ()
{
    // Creating basic layout
    
    glClearColor( 0.212 ,0.271,0.31, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // it is the size of out virtual world
    glOrtho(0, 500, 0, 500, -10.0, 10.0);
    
    // For 3d objects we have to add this
    glEnable(GL_DEPTH_TEST);
}


void Face(GLfloat A[],GLfloat B[],GLfloat C[],GLfloat D[]){
    
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
    
}

void Cube(GLfloat V0[],GLfloat V1[],GLfloat V2[],GLfloat V3[],GLfloat V4[],GLfloat V5[],GLfloat V6[],GLfloat V7[]){
    
    glColor3b(1, 0, 0);
    Face(V0,V1,V2,V3);
    glColor3f(0, 1, 0);
    Face(V4,V5,V6,V7);
    glColor3f(0, 0, 1);
    Face(V0,V3,V7,V4);
    glColor3f(1, 1, 0);
    Face(V1,V2,V6,V5);
    glColor3f(0, 1, 1);
    Face(V0,V1,V5,V4);
    glColor3f(1, 0, 1);
    Face(V3,V2,V6,V7);
    
}

void Spin(){
    
    if(speed==0){
        glutIdleFunc(NULL);
    }
    spin+=speed;
    if(spin>360)
        spin=0;
    
    glutPostRedisplay();
}

void display ()
{
    // coordinates of the object which will be created
    GLfloat v[8][3] =
    {
        {-0.5, 0.5, 0.5},
        { 0.5, 0.5, 0.5},
        { 0.5,-0.5, 0.5},
        {-0.5,-0.5, 0.5},
        
        {-0.5, 0.5,-0.5},
        { 0.5, 0.5,-0.5},
        { 0.5,-0.5,-0.5},
        {-0.5,-0.5,-0.5},
    };
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glLoadIdentity();
    
   
    // We don't want to rotate the environment. We just want to rotate the object
    // For this we just pust this in a matrix and rotate it, then we pop it in out virtual world
    // With out this method our whole virtual environment will rotate with the cube.
    glPushMatrix();
       
        glRotatef(spin, xr, yr, zr);
        glScalef(smallFactor, smallFactor, smallFactor);
        
        Cube(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);
    
    glPopMatrix();
    
    glPointSize(3);
    glBegin(GL_POINTS);
        
        glColor3f(1,1,0);
        
        float LO = -1.1,HI = 1.1;
        for(int i=0 ; i<100 ; i++){
            float r1 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            float r2 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
           
            glVertex3f(r1,r2,+0.6);
        }
    
    glEnd();
    
    glutSwapBuffers();
    
}

void spinDisplay_forward(void)
{
    xr=1;
    yr=0;
    zr=0;
    glutPostRedisplay();
}

void spinDisplay_backward(void)
{
    xr=-1;
    yr=0;
    zr=0;
    glutPostRedisplay();
}

void spinDisplay_left(void)
{
    xr=0;
    yr=1;
    zr=0;
    glutPostRedisplay();
}

void spinDisplay_right(void)
{
    xr=0;
    yr=-1;
    zr=0;
    glutPostRedisplay();
}

void spinDisplay_forRight(void)
{
    xr=-1;
    yr=1;
    zr=0;
    glutPostRedisplay();
}

void spinDisplay_backleft(void)
{
    xr=1;
    yr=0;
    zr=1;
    glutPostRedisplay();
}

void spinDisplay_small(void)
{
    smallFactor-=0.05;
    glutPostRedisplay();
}

void spinDisplay_big(void)
{
    smallFactor+=0.05;
    glutPostRedisplay();
}

void faster(){
    speed+=1;
}

void slower(){
    speed-=1;
}

void my_keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
            
        case 'w':
            glutIdleFunc(Spin);
            spinDisplay_forward();
            break;
            
        case 'a':
            glutIdleFunc(Spin);
            spinDisplay_left();
            break;
            
        case 'd':
            glutIdleFunc(Spin);
            spinDisplay_right();
            break;
            
        case 's':
            glutIdleFunc(Spin);
            spinDisplay_backward();
            break;
            
        case 'e':
            glutIdleFunc(Spin);
            spinDisplay_forRight();
            break;
            
        case 'q':
            glutIdleFunc(Spin);
            spinDisplay_backleft();
            break;
            
        case 'x':
            glutIdleFunc(Spin);
            spinDisplay_small();
            break;
            
        case 'z':
            glutIdleFunc(Spin);
            spinDisplay_big();
            break;
            
        case 'f':
            glutIdleFunc(Spin);
            faster();
            break;
            
        case 'g':
            glutIdleFunc(Spin);
            slower();
            break;
            
        case 'p':
            glutIdleFunc(NULL);
            break;
            
        case 'y':
            exit(0);
            break;
            
        default:
            break;
    }
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    // GLUT_DEPTH is added for working with 3d object
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(400, 0);
    
    glutCreateWindow("Space Cube Controller");
   
    myInit();
    
    // creating the objects which will be shown after running this app
    glutDisplayFunc(display);
    
    // Keyboard controlls 
    glutKeyboardFunc(my_keyboard);
    
    // with out this the program will be terminated after running just once
    // but we want to run it intill we press 'y'
    glutMainLoop();
}
