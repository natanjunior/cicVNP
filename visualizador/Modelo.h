#ifndef MODELO_H
#define MODELO_H

#include <stdio.h>
#include <string>
#include <vector>
#include <limits>
#include "Voxel.h"

using namespace std;

enum Formato { PADRAO, PLY, PTSarq, PTSrealtime };

class Modelo{
private:
    string nome;
    Formato formato;
    string enderecoArq;
    vector<Voxel> pontos;
    float dimensaoBox[6]; //x_max, y_max, z_max, x_min, y_min, z_min
public:
    Modelo(string arquivo = NULL);
    ~Modelo();
    void setNome(string nome);
    void setFormato(int formato);
    void setDimensoes(float x_max, float y_max, float z_max, float x_min, float y_min, float z_min);
    int getFormato();
    vector<Voxel>* getPontos();
    void addPonto(Voxel voxel);
    string getNome();
    int getQtdePontos();
    float* getDimensoesBox();
    float getTamX();
    float getTamY();
    float getTamZ();
};

#endif // MODELO_H
