#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <exception>
#include <algorithm>
#include <limits>
#include "Modelo.h"
#include "Video.h"
#include "rply.h"

using namespace std;

class Arquivo {
private:
    string enderecoArq;
    Modelo *modelo;
    float x_coord, y_coord, z_coord;
    char r, g, b;

public:
    Arquivo(string enderecoArq = NULL);
    void lerArquivo(Modelo *modelo);
    void lerArquivo(Video *video);
    vector<string> split(string str, char delimiter);
    void parserPadrao();
    void parserPly();
    void parserPts();
    void parserVideo(Video *video);
    void salvarArquivo(string fileName, Modelo *modelo);
    void escritorPly(string fileName, vector<Voxel> *pontos);
    void escritorPts(string fileName, vector<Voxel> *pontos);
    void criaPonto(Voxel *ponto);
    struct CallbackContext {
        Voxel *ponto;
        Modelo *modelo;
        float x_max = numeric_limits<float>::min(), y_max = numeric_limits<float>::min(), z_max = numeric_limits<float>::min();
        float x_min = numeric_limits<float>::max(), y_min = numeric_limits<float>::max(), z_min = numeric_limits<float>::max();
    };
    //    void setaArquivo(File arq);
    //    Modelo getModelo();
};

#endif // ARQUIVO_H
