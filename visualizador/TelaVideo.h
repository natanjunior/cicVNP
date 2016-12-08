// TELAVIDEO.h

#ifndef TELAVIDEO_H
#define TELAVIDEO_H

#include <QWidget>
#include <QSlider>
#include <QtWidgets>
#include <string>
#include "ui_TelaVideo.h"
#include "TelaVideo.h"
#include "Controlador.h"

namespace Ui {
class TelaVideo;
}

class TelaVideo : public QWidget{
    Q_OBJECT

public:
    explicit TelaVideo(QWidget *parent = 0, Controlador *c = NULL);
    ~TelaVideo();
    void setControlador(Controlador *c);
    void visaoInicial();
    void setShift(int opt);

private:
    Ui::TelaVideo *ui;
    Controlador *controlador;
    int maxSec;

    QString getTempoAtual();
};

#endif // TelaVideo
