#include "Modelo.h"

#include <QDebug>

Modelo::Modelo(string arq) {
    enderecoArq = arq;
    dimensaoBox[0] = numeric_limits<float>::min();
    dimensaoBox[1] = numeric_limits<float>::min();
    dimensaoBox[2] = numeric_limits<float>::min();
    dimensaoBox[3] = numeric_limits<float>::max();
    dimensaoBox[4] = numeric_limits<float>::max();
    dimensaoBox[5] = numeric_limits<float>::max();
}

void Modelo::setNome(string n){
    nome = n;
}

void Modelo::setFormato(int f){
    formato = static_cast<Formato>(f);
}

void Modelo::setDimensoes(float x_max, float y_max, float z_max, float x_min, float y_min, float z_min){
    dimensaoBox[0] = x_max;
    dimensaoBox[1] = y_max;
    dimensaoBox[2] = z_max;
    dimensaoBox[3] = x_min;
    dimensaoBox[4] = y_min;
    dimensaoBox[5] = z_min;
}

int Modelo::getFormato(){
    return formato;
}

vector<Voxel>* Modelo::getPontos(){
    return &pontos;
}

void Modelo::addPonto(Voxel voxel){
    pontos.push_back(voxel);
    dimensaoBox[0] = max(dimensaoBox[0], voxel.getX_coord());
    dimensaoBox[3] = min(dimensaoBox[3], voxel.getX_coord());
    dimensaoBox[1] = max(dimensaoBox[1], voxel.getY_coord());
    dimensaoBox[4] = min(dimensaoBox[4], voxel.getY_coord());
    dimensaoBox[2] = max(dimensaoBox[2], voxel.getZ_coord());
    dimensaoBox[5] = min(dimensaoBox[5], voxel.getZ_coord());
}

string Modelo::getNome(){
    return nome;
}

int Modelo::getQtdePontos(){
    return pontos.size();
}

float* Modelo::getDimensoesBox(){
    return dimensaoBox;
}

float Modelo::getTamX(){
    return dimensaoBox[0]-dimensaoBox[3];
}

float Modelo::getTamY(){
    return dimensaoBox[1]-dimensaoBox[4];
}

float Modelo::getTamZ(){
    return dimensaoBox[2]-dimensaoBox[5];
}
