#include "TelaCamera.h"

using namespace std;

TelaCamera::TelaCamera(QWidget *parent, Controlador *c) :
    QWidget(parent),
    ui(new Ui::TelaCamera)
{
    controlador = c;

    ui->setupUi(this);

    ui->canvasCamera->setControlador(c);
    ui->canvasCamera->ligaCamera();
    ui->canvasCamera->capturaNuvem();
    ui->canvasCamera->desligaCamera();
}

TelaCamera::~TelaCamera()
{
    delete ui;
}

void TelaCamera::setControlador(Controlador *c){
    controlador = c;
    ui->canvasCamera->setControlador(c);
}

void TelaCamera::on_exButton_clicked()
{

}
