#ifndef CANVAS_H
#define CANVAS_H

#include <OpenGL/glu.h>

#if defined(Q_WS_MAC)
#include <OpenGL/glu.h>
#elif defined(Q_OS_LINUX)
#include <GL/glu.h>
#endif

#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <limits>
#include "Controlador.h"
#include "Voxel.h"

class Canvas : public QGLWidget{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();
    void setControlador(Controlador *c);

    Controlador *controlador;
    vector< vector<Voxel> >* frames;
    vector<Voxel>* pontos;
    int xRot;
    int yRot;
    int zRot;
    float xTsl;
    float yTsl;
    float zTsl;
    float orthoLeft;
    float orthoRight;
    float orthoTop;
    float orthoBottom;
    float orthoNear;
    float orthoFar;
    int zoom;
    float point;
    bool moveOption;
    float* dimensaoBox; //x_max, y_max, z_max, x_min, y_min, z_min
    float xCorrection;
    float yCorrection;
    float zCorrection;
    QPoint lastPos;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void setXRotation(int angulo);
    void setYRotation(int angulo);
    void setZRotation(int angulo);
    void setXTranslate(float distancia);
    void setYTranslate(float distancia);
    void setZTranslate(float distancia);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void setXmovement(int move);
    void setYmovement(int move);
    void setZmovement(int move);
    void setMoveOption(int opt);
    void setZoom(int zoom);
    void setPoint(int point);
    void screenshoot();
    void visaoInicial();

signals:
    void xSliderChanged(int move);
    void ySliderChanged(int move);
    void zSliderChanged(int move);
    void moveOptionChanged(int opt);
    void zoomChanged(int zoom);
    void pointChanged(int point);
};

#endif // CANVAS_H
