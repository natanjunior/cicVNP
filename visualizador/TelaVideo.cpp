// TelaVideo.cpp

#include "TelaVideo.h"

#include <QDebug>

using namespace std;

TelaVideo::TelaVideo(QWidget *parent, Controlador *c) :
    QWidget(parent),
    ui(new Ui::TelaVideo)
{
    controlador = c;

    ui->setupUi(this);

    ui->canvasVideo->setControlador(c);

//    ui->labelNome->setText(QString::fromStdString(controlador->getNome()));
    ui->labelNome->setText("Modelo");
    ui->labelQtdeFrames->setText(QString::fromStdString(to_string(controlador->getQtdeFrames()) + " frames"));

    ui->timeSlider->setMaximum(controlador->getQtdeFrames());

    maxSec = (controlador->getQtdeFrames()/30)+1;

    ui->labelTempo->setText(this->getTempoAtual());

    connect(ui->canvasVideo, SIGNAL(xSliderChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->canvasVideo, SIGNAL(ySliderChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->canvasVideo, SIGNAL(zSliderChanged(int)), ui->zSlider, SLOT(setValue(int)));
    connect(ui->canvasVideo, SIGNAL(zoomChanged(int)), ui->zoomSlider, SLOT(setValue(int)));
    connect(ui->canvasVideo, SIGNAL(pointChanged(int)), ui->pointSlider, SLOT(setValue(int)));
    connect(ui->canvasVideo, SIGNAL(frameChanged(int)), ui->timeSlider, SLOT(setValue(int)));
}

TelaVideo::~TelaVideo(){
    delete ui;
}

void TelaVideo::setControlador(Controlador *c){
    controlador = c;
    ui->canvasVideo->setControlador(c);
}

void TelaVideo::visaoInicial(){
    ui->canvasVideo->visaoInicial();
}

QString TelaVideo::getTempoAtual(){
    int atual = (ui->timeSlider->value()/30)+1;
    return maxSec + "/" + atual;
}

void TelaVideo::setShift(int opt){
    ui->canvasVideo->setMoveOption(opt);
}
