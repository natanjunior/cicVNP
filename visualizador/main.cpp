// main.cpp

#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "TelaModelo.h"
#include "TelaVideo.h"
#include "Controlador.h"
#include "Arquivo.h"
#include "Modelo.h"
#include "Video.h"
#include "Voxel.h"
#include "Camera.h"

int main(int argc, char *argv[]){

    Controlador controlador;
//    Camera *cam = new Camera();
//    if(cam->verificaCamera()){
//        cam->configuraCamera();
//        controlador.setCamera(cam);
//    }

    QApplication app(argc, argv);
    MainWindow mw;

    mw.showMaximized();
    mw.setControlador(&controlador);

    return app.exec();
}
