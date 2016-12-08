// CanvasVideo.cpp

#include "CanvasVideo.h"

#include <QDebug>

CanvasVideo::CanvasVideo(QWidget *parent)
    : Canvas(parent)
{
    frames = NULL;
    f = 0;
}

CanvasVideo::~CanvasVideo(){}

void CanvasVideo::setControlador(Controlador *c){
    controlador = c;
    frames = c->getFrames();
    pontos = frames->at(f%frames->size());
    f++;
    aTimer = new QTimer;
    connect(aTimer,SIGNAL(timeout()),SLOT(animate()));
    aTimer->start(30);
}

void CanvasVideo::setFrame(int frame){
    if(f != frame){
        aTimer->stop();
        f = frame;
        updateGL();
        aTimer->start(30);
    }
}

void CanvasVideo::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glScalef (zoom/10.0, zoom/10.0, zoom/10.0);
    glTranslatef(xTsl, yTsl, zTsl);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glPointSize(point);
    glBegin(GL_POINTS);
    for (unsigned long i = 0; i < pontos.size(); i++) {
        Voxel ponto = pontos.at(i);
        glColor3f(ponto.getR_color(), ponto.getG_color(), ponto.getB_color());
        float x, y, z;
        x = ponto.getX_coord();
        y = ponto.getY_coord();
        z = ponto.getZ_coord();
        glVertex3f(x, y, z);
    }
    glEnd();
}

void CanvasVideo::animate(){
    int frame = f%frames->size();
    pontos = frames->at(frame);
    emit frameChanged(frame);
    if(f != frame){
        setFrame(frame);
    }
    f++;
    updateGL();
}
