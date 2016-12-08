#include "Controlador.h"

#include <QDebug>

Controlador::Controlador(){
    modo = static_cast<Modos>(0);
    camera = NULL;
}

void Controlador::novoModelo(string fileName){
    modelo = new Modelo(fileName);
    arquivo = new Arquivo(fileName);
    arquivo->lerArquivo(modelo);
}

void Controlador::novoVideo(string fileName){
    video = new Video(fileName);
    arquivo = new Arquivo(fileName);
    arquivo->lerArquivo(video);
}

vector<Voxel>* Controlador::getPontos(){
    return modelo->getPontos();
}

vector< vector<Voxel> >* Controlador::getFrames(){
    return video->getFrames();
}

string Controlador::getNome(){
    return modelo->getNome();
}

int Controlador::getQtdePontos(){
    return modelo->getQtdePontos();
}

int Controlador::getQtdeFrames(){
    return video->getQtdeFrames();
}

Modelo* Controlador::getModelo(){
    return modelo;
}

int Controlador::getFormato(){
    return modelo->getFormato();
}

int Controlador::getModo(){
    return modo;
}

void Controlador::salvarModelo(string fileName){
    arquivo->salvarArquivo(fileName, modelo);
}

float* Controlador::getTamCanvas(){
    float maior = max(getModelo()->getTamX(), getModelo()->getTamY());
    maior = max(maior, getModelo()->getTamZ());
    int casas = ceil(log10(maior+1));
    tamCanvas[0] = (-1)*pow(10,casas);
    tamCanvas[1] = pow(10,casas);
    tamCanvas[2] = (-1)*pow(10,casas);
    tamCanvas[3] = pow(10,casas);
    tamCanvas[4] = (-10)*pow(10,casas);
    tamCanvas[5] = 10*pow(10,casas);
//    float* dimensaoBox = getModelo()->getDimensoesBox();
//    tamCanvas[0] = dimensaoBox[3] - (getModelo()->getTamX()*1.5);
//    tamCanvas[1] = dimensaoBox[0] + (getModelo()->getTamX()*1.5);
//    tamCanvas[2] = dimensaoBox[4] - (getModelo()->getTamY()*1.5);
//    tamCanvas[3] = dimensaoBox[1] + (getModelo()->getTamZ()*1.5);
//    tamCanvas[4] = dimensaoBox[5] - (getModelo()->getTamZ()*10);
//    tamCanvas[5] = dimensaoBox[2] + (getModelo()->getTamZ()*10);
    return tamCanvas;
}

void Controlador::setCamera(Camera *cam){
    camera = cam;
}

Camera* Controlador::getCamera(){
    return camera;
}

float* Controlador::getDimensoesBox(){
    return modelo->getDimensoesBox();
}

void Controlador::setModo(int m){
    modo = static_cast<Modos>(m);
}
