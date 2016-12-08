#include "Video.h"

Video::Video(string arq) {
    enderecoArq = arq;
}

void Video::setNome(string n){
    nome = n;
}

void Video::setFormato(string f){
    formato = f;
}

void Video::setDimensoes(float x_max, float y_max, float z_max, float x_min, float y_min, float z_min){
    dimensaoBox[0] = x_max;
    dimensaoBox[1] = y_max;
    dimensaoBox[2] = z_max;
    dimensaoBox[3] = x_min;
    dimensaoBox[4] = y_min;
    dimensaoBox[5] = z_min;
}

string Video::getFormato(){
    return formato;
}

vector<vector<Voxel>>* Video::getFrames(){
    return &frames;
}

void Video::setFrames(vector<vector<Voxel>> f){
    frames = f;
}

string Video::getNome(){
    return nome;
}

int Video::getQtdeFrames(){
    return frames.size();
}

float* Video::getDimensoesBox(){
    return dimensaoBox;
}

float Video::getTamX(){
    return dimensaoBox[0]-dimensaoBox[3];
}

float Video::getTamY(){
    return dimensaoBox[1]-dimensaoBox[4];
}

float Video::getTamZ(){
    return dimensaoBox[2]-dimensaoBox[5];
}
