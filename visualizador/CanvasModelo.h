// CanvasModelo.h

#ifndef CANVASMODELO_H
#define CANVASMODELO_H

#include "Canvas.h"

class CanvasModelo : public Canvas
{
    Q_OBJECT
public:
    explicit CanvasModelo(QWidget *parent = 0);
    ~CanvasModelo();
    void setControlador(Controlador *c);

protected:
    void paintGL();
};

#endif // MYGLWIDGET_H

