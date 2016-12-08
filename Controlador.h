#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <vector>

#include "Arquivo.h"
#include "Modelo.h"
#include "Video.h"
#include "Voxel.h"
#include "Camera.h"

using namespace std;

enum Modos { INICIAL, MODELO, VIDEO, AJUDA, CAMERA };

class Controlador {
private:
    Arquivo *arquivo;
    Modelo *modelo;
    Video *video;
    Camera *camera;
    Modos modo;

public:
    Controlador();
    Modelo* getModelo();
    Video* getVideo();
    void novoModelo(string fileName);
    void novoVideo(string fileName);
    vector<Voxel>* getPontos();
    vector< vector<Voxel> >* getFrames();
    string getNome();
    int getQtdePontos();
    int getQtdeFrames();
    string getTempo();
    int getModo();
    void setModo(int modo);
    int getFormato();
    void salvarModelo(string fileName);
    float tamCanvas[6];
    float* getTamCanvas();
    float* getDimensoesBox();
    void setCamera(Camera *camera);
    Camera* getCamera();
//    void setaArquivo(File arq);
//    Modelo getModelo();
};

#endif // CONTROLADOR_H
