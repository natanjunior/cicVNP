#ifndef CANVASCAMERA_H
#define CANVASCAMERA_H

#include "Canvas.h"
#include "Camera.h"

class CanvasCamera : public Canvas
{
    Q_OBJECT
public:
    explicit CanvasCamera(QWidget *parent = 0);
    ~CanvasCamera();
    void setControlador(Controlador *c);
    void ligaCamera();
    void desligaCamera();
    void capturaNuvem();

protected:
    void paintGL();

private:
    Camera *camera;
    QTimer *aTimer;

private slots:
    void newFrame();
};

#endif // CANVASCAMERA_H
