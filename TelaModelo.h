// canvas.h

#ifndef TELAMODELO_H
#define TELAMODELO_H

#include <QWidget>
#include <QSlider>
#include <QtWidgets>
#include <string>
#include "ui_TelaModelo.h"
#include "Controlador.h"

namespace Ui {
class TelaModelo;
}

class TelaModelo : public QWidget
{
    Q_OBJECT

public:
    explicit TelaModelo(QWidget *parent = 0, Controlador *c = NULL);
    ~TelaModelo();
    void setControlador(Controlador *c);
    void visaoInicial();
    void setShift(int opt);

private slots:
    void on_exButton_clicked();

private:
    Ui::TelaModelo *ui;
    Controlador *controlador;
};

#endif // telamodelo
