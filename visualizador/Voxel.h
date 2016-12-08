#ifndef VOXEL_H
#define VOXEL_H

#include <string>
#include <vector>

using namespace std;

class Voxel{
private:
    float X_coord;
    float Y_coord;
    float Z_coord;
    char R_color;
    char G_color;
    char B_color;
public:
    Voxel(float x, float y, float z, int r, int g, int b);
    Voxel();
    float getX_coord();
    void setX_coord(float x_coord);
    float getY_coord();
    void setY_coord(float y_coord);
    float getZ_coord();
    void setZ_coord(float z_coord);
    char getR_color();
    void setR_color(char r_color);
    char getG_color();
    void setG_color(char g_color);
    char getB_color();
    void setB_color(char b_color);
    string getLinha();
};

#endif // VOXEL_H
