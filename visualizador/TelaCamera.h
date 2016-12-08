#ifndef TELACAMERA_H
#define TELACAMERA_H

#include <QWidget>
#include <QSlider>
#include <QtWidgets>
#include <string>
#include "ui_TelaCamera.h"
#include "Controlador.h"

namespace Ui {
class TelaCamera;
}

class TelaCamera : public QWidget
{
    Q_OBJECT

public:
    explicit TelaCamera(QWidget *parent = 0, Controlador *c = NULL);
    ~TelaCamera();
    void setControlador(Controlador *c);

private slots:
    void on_exButton_clicked();

private:
    Ui::TelaCamera *ui;
    Controlador *controlador;
};

#endif // TELACAMERA_H
