#include "CanvasModelo.h"

#include "QDebug"

CanvasModelo::CanvasModelo(QWidget *parent)
    : Canvas(parent)
{
    pontos = NULL;
}

CanvasModelo::~CanvasModelo(){}

void CanvasModelo::setControlador(Controlador *c){
    controlador = c;
    pontos = c->getPontos();
    float* tamOrtho = controlador->getTamCanvas();
    orthoLeft = tamOrtho[0];
    orthoRight = tamOrtho[1];
    orthoBottom = tamOrtho[2];
    orthoTop = tamOrtho[3];
    orthoNear = tamOrtho[4];
    orthoFar = tamOrtho[5];
    dimensaoBox = controlador->getDimensoesBox();
    xCorrection = ((dimensaoBox[0]-dimensaoBox[3])/2)+dimensaoBox[3];
    yCorrection = ((dimensaoBox[1]-dimensaoBox[4])/2)+dimensaoBox[4];
    zCorrection = ((dimensaoBox[5]-dimensaoBox[5])/2)+dimensaoBox[5];
    if(controlador->getFormato()==2){
//        xTsl = controlador->getModelo()->getTamX()/2.0;
//        yTsl = controlador->getModelo()->getTamY()/2.0;
        yRot = 180;
    }
}

void desenhaCubo(Voxel ponto){
    float x = ponto.getX_coord();
    float y = ponto.getY_coord();
    float z = ponto.getZ_coord();

    glColor3ub(ponto.getR_color(), ponto.getG_color(), ponto.getB_color());

    glBegin(GL_POLYGON);
    glVertex3f(x,y,z);
    glVertex3f(x,y+1.0,z);
    glVertex3f(x+1.0,y+1.0,z);
    glVertex3f(x+1.0,y,z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x,y+1,z+1);
    glVertex3f(x,y,z+1);
    glVertex3f(x,y,z);
    glVertex3f(x,y+1,z);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x+1,y+1,z);
    glVertex3f(x+1,y,z);
    glVertex3f(x+1,y,z+1);
    glVertex3f(x+1,y+1,z+1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x,y+1,z+1);
    glVertex3f(x,y+1,z);
    glVertex3f(x+1,y+1,z);
    glVertex3f(x+1,y+1,z+1);
    glEnd();
}

void CanvasModelo::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glScalef (zoom/10.0, zoom/10.0, zoom/10.0);
    glTranslatef(xTsl*1000, yTsl*1000, zTsl*1000);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    vector<Voxel> *pontos = controlador->getPontos();
    glPointSize(point);
    glBegin(GL_POINTS);
    for (unsigned long i = 0; i < pontos->size(); i++) {
        Voxel ponto = pontos->at(i);
//        desenhaCubo(ponto);
        glColor3ub(ponto.getR_color(), ponto.getG_color(), ponto.getB_color());
        glVertex3f(ponto.getX_coord()-0, ponto.getY_coord()-0, ponto.getZ_coord()-0);
    }
    glEnd();
}
