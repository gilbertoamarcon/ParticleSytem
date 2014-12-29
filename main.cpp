#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "Particle.h"
#include "ParticleSystem.h"

#define WINDOW_TITLE    "Video"
#define WINDOW_W        1280
#define WINDOW_H        720
#define MOUSE_FACTOR    1000
#define Z_NEAR          0.001
#define Z_FAR           1000
#define C_FOVY          75
#define FULL_SCREEN     1
#define FRAME_TIME      15
#define PLOT_AXIS       1

#define HIDE_1ST_PART   1
#define FLOOR_SIDE      5

using namespace std;

typedef enum MOUSE_CONTROL{CAM,SPRING_POS,SPRING_ANGLE};

double c_aspect     = (double)WINDOW_W/WINDOW_H;

double theta        = 90;
double phi          = 90;

double mouse_xs     = 0;
double mouse_ys     = 0;

int aux             = 0;

MOUSE_CONTROL mouseControl  = CAM;

ParticleSystem particles;

Vector camPos(0,0,8);

void iniGl();

void keyPressed(unsigned char key, int x, int y);

void mouseMove(int x, int y);

double fixDegrees(double ang);
void plotAxis();

void updateValues(int n);

void RenderScene();

int main(int argc, char **argv){

    particles.init(2,200,Vector(0,0,1),Vector(1,1,1),0.1,10000,.1,-.0025,0.1);

    glutInit(&argc, argv);

    iniGl();

    glutMainLoop();

    return 1;
}

double fixDegrees(double ang){
    if (ang < 0)
        ang += 360;
    else if(ang > 360)
        ang -= 360;
    return ang;
}

void mouseMove(int x, int y){
    mouse_xs    = (double)x/MOUSE_FACTOR-0.5;
    mouse_ys    = (double)y/MOUSE_FACTOR-0.5;
    theta       = fixDegrees(360*mouse_xs);
    phi         = fixDegrees(360*mouse_ys);
    switch(mouseControl){
        case CAM:
            camPos.setDirection(theta,phi);
            aux = 2*(phi>180)-1;
            break;
        case SPRING_POS:
            particles.setBirth(Vector(3*mouse_xs,3*mouse_ys,1));
            break;
        case SPRING_ANGLE:
            particles.initVel.setDirection(theta,phi);
            break;
        default:
            break;
    }
}

void iniGl(){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow(WINDOW_TITLE);
    glutKeyboardFunc(&keyPressed);
    glutDisplayFunc(&RenderScene);
    glutPassiveMotionFunc(&mouseMove);
    glutTimerFunc(1,updateValues,0);
    glutIdleFunc(&RenderScene);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glutSetCursor(GLUT_CURSOR_NONE);
    gluPerspective(C_FOVY,c_aspect,Z_NEAR,Z_FAR);
    if (FULL_SCREEN)
        glutFullScreen();
}

void keyPressed(unsigned char key, int x, int y){
    switch (key){
        case 27:
            exit(0);
            break;
        case 'q':
            mouseControl = CAM;
            break;
        case 'w':
            mouseControl = SPRING_POS;
            break;
        case 'e':
            mouseControl = SPRING_ANGLE;
            break;
        case 'a':
            particles.initVel.mult(1.1);
            break;
        case 'z':
            particles.initVel.mult(1/1.1);
            break;
        case 's':
            particles.lifeLimit *= 1.1;
            break;
        case 'x':
            particles.lifeLimit /= 1.1;
            break;
        case 'd':
            particles.rndVel *= 1.1;
            break;
        case 'c':
            particles.rndVel /= 1.1;
            break;
        case 'f':
            particles.width *= 1.1;
            break;
        case 'v':
            particles.width /= 1.1;
            break;
        case 'g':
            camPos.mult(1.1);
            break;
        case 'b':
            camPos.mult(1/1.1);
            break;
        default:
            break;
    }
}

void plotAxis(){
    glColor3f(1,0.5,0.5);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
    glEnd();
    glColor3f(0.5,1,0.5);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
    glEnd();
    glColor3f(0.5,0.5,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    glEnd();
}

void updateValues(int n){
    particles.update();
    glutTimerFunc(FRAME_TIME,updateValues,0);
}

void RenderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        gluLookAt(camPos.x,camPos.y,camPos.z,0,0,0, 0,0,aux);

        // Ground floor
        glColor3f(0.1,0.1,0.1);
        glBegin(GL_QUADS);
            glVertex3f(-FLOOR_SIDE,-FLOOR_SIDE,0);
            glVertex3f( FLOOR_SIDE,-FLOOR_SIDE,0);
            glVertex3f( FLOOR_SIDE, FLOOR_SIDE,0);
            glVertex3f(-FLOOR_SIDE, FLOOR_SIDE,0);
        glEnd();

        // Axis
        if (PLOT_AXIS)
            plotAxis();

        // Particles
        for (int i = 0; i < particles.num_particles; i++){
            if(!(HIDE_1ST_PART  && particles.particle[i].firstCycle)){
                glPointSize(particles.particle[i].p_size);
                glColor3f(particles.particle[i].color.x,particles.particle[i].color.y,particles.particle[i].color.z);
                glBegin(GL_POINTS);
                    glVertex3f(particles.particle[i].pos.x,particles.particle[i].pos.y,particles.particle[i].pos.z);
                glEnd();
            }
        }

    glPopMatrix();
    glutSwapBuffers();
}
