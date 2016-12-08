#include "Voxel.h"

Voxel::Voxel(float x, float y, float z, int r, int g, int b){
    X_coord = x;
    Y_coord = y;
    Z_coord = z;
    R_color = r;
    G_color = g;
    B_color = b;
}
Voxel::Voxel(){
    R_color = G_color = B_color = 64;
}
float Voxel::getX_coord() {
    return X_coord;
}
void Voxel::setX_coord(float x_coord) {
    X_coord = x_coord;
}
float Voxel::getY_coord() {
    return Y_coord;
}
void Voxel::setY_coord(float y_coord) {
    Y_coord = y_coord;
}
float Voxel::getZ_coord() {
    return Z_coord;
}
void Voxel::setZ_coord(float z_coord) {
    Z_coord = z_coord;
}
char Voxel::getR_color() {
    return R_color;
}
void Voxel::setR_color(char r_color) {
    R_color = r_color;
}
char Voxel::getG_color() {
    return G_color;
}
void Voxel::setG_color(char g_color) {
    G_color = g_color;
}
char Voxel::getB_color() {
    return B_color;
}
void Voxel::setB_color(char b_color) {
    B_color = b_color;
}
string Voxel::getLinha(){
    return to_string(X_coord) + " " +
            to_string(Y_coord) + " " +
            to_string(Z_coord) + " " +
            to_string(R_color) + " " +
            to_string(G_color) + " " +
            to_string(B_color);
}
