#ifndef VIDEO_H
#define VIDEO_H

#include <stdio.h>
#include <string>
#include <vector>

#include "Voxel.h"

using namespace std;

class Video{
private:
    string nome;
    string formato;
    string enderecoArq;
    vector< vector<Voxel> > frames;
    float dimensaoBox[6]; //x_max, y_max, z_max, x_min, y_min, z_min
public:
    Video(string arquivo = NULL);
    ~Video();
    void setNome(string nome);
    void setFormato(string formato);
    void setDimensoes(float x_max, float y_max, float z_max, float x_min, float y_min, float z_min);
    string getFormato();
    vector< vector<Voxel> >* getFrames();
    void setFrames(vector< vector<Voxel> > frames);
    string getNome();
    int getQtdeFrames();
    float* getDimensoesBox();
    float getTamX();
    float getTamY();
    float getTamZ();
};

#endif // MODELO_H
