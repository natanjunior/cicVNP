// CanvasVideo.h

#ifndef CANVASVIDEO_H
#define CANVASVIDEO_H

#include <QTimer>
#include "Canvas.h"

class CanvasVideo : public Canvas
{
    Q_OBJECT
public:
    explicit CanvasVideo(QWidget *parent = 0);
    ~CanvasVideo();
    void setControlador(Controlador *c);

protected:
    void paintGL();

public slots:
    void setFrame(int frame);

signals:
    void frameChanged(int frame);

private:
    vector< vector<Voxel> >* frames;
    vector<Voxel> pontos;
    int f;
    QTimer *aTimer;

private slots:
    void animate();

};

#endif // MYGLWIDGET_H

