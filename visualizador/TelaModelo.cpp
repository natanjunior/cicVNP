// TelaModelo.cpp

#include "TelaModelo.h"

using namespace std;

TelaModelo::TelaModelo(QWidget *parent, Controlador *c) :
    QWidget(parent),
    ui(new Ui::TelaModelo)
{
    controlador = c;

    ui->setupUi(this);

    ui->canvasModelo->setControlador(c);

    ui->labelNome->setText(QString::fromStdString(controlador->getNome()));
    ui->labelQtdePontos->setText(QString::fromStdString(to_string(controlador->getQtdePontos()) + " pontos"));
    ui->labelTamX->setText(QString::fromStdString("X axis: " + to_string(controlador->getModelo()->getTamX())));
    ui->labelTamY->setText(QString::fromStdString("Y axis: " + to_string(controlador->getModelo()->getTamY())));
    ui->labelTamZ->setText(QString::fromStdString("Z axis: " + to_string(controlador->getModelo()->getTamZ())));

    connect(ui->canvasModelo, SIGNAL(xSliderChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->canvasModelo, SIGNAL(ySliderChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->canvasModelo, SIGNAL(zSliderChanged(int)), ui->zSlider, SLOT(setValue(int)));
    connect(ui->canvasModelo, SIGNAL(zoomChanged(int)), ui->zoomSlider, SLOT(setValue(int)));
    connect(ui->canvasModelo, SIGNAL(pointChanged(int)), ui->pointSlider, SLOT(setValue(int)));
}

TelaModelo::~TelaModelo(){
    delete ui;
}

void TelaModelo::setControlador(Controlador *c){
    controlador = c;
    ui->canvasModelo->setControlador(c);
}

void TelaModelo::visaoInicial(){
    ui->canvasModelo->visaoInicial();
}

void TelaModelo::setShift(int opt){
    ui->canvasModelo->setMoveOption(opt);
}

void TelaModelo::on_exButton_clicked(){
    QString format = "pts";
    QString initialPath = QDir::homePath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath, tr("PLY File (*.ply);;PTS File (*.pts)"));

    controlador->salvarModelo(fileName.toUtf8().constData());
}
