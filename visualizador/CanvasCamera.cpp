#include "CanvasCamera.h"

#include "QDebug"

CanvasCamera::CanvasCamera(QWidget *parent)
: Canvas(parent)
{
    pontos = NULL;
    camera = NULL;
}

CanvasCamera::~CanvasCamera(){}

void CanvasCamera::setControlador(Controlador *c){
    controlador = c;
    camera = c->getCamera();
    zRot = 180;
    aTimer = new QTimer;
    connect(aTimer,SIGNAL(timeout()),SLOT(newFrame()));
}

void CanvasCamera::ligaCamera(){
//    camera->ligaCamera();
}

void CanvasCamera::desligaCamera(){
//    camera->desligaCamera();
}

void CanvasCamera::capturaNuvem(){
    aTimer->stop();
//    pontos = camera->capturarNuvem();
    updateGL();
    aTimer->start(1000);
}

void CanvasCamera::newFrame(){
    this->capturaNuvem();
}

void CanvasCamera::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glScalef (zoom/10.0, zoom/10.0, zoom/10.0);
    glTranslatef(xTsl, yTsl, zTsl);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glPointSize(point);
    if(pontos!=NULL){
        glBegin(GL_POINTS);
        for (unsigned long i = 0; i < pontos->size(); i++) {
            Voxel ponto = pontos->at(i);
            glColor3f(ponto.getR_color(), ponto.getG_color(), ponto.getB_color());
            float x, y, z;
            x = ponto.getX_coord();
            y = ponto.getY_coord();
            z = ponto.getZ_coord();
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}
