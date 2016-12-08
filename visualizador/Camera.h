#ifndef CAMERA_H
#define CAMERA_H

/*#include <string>
#include "Voxel.h"
#include <vector>
#include "triclops.h"
#include "fc2triclops.h"

using namespace std;

// aliases namespaces
namespace FC2 = FlyCapture2;
namespace FC2T = Fc2Triclops;

*/class Camera{/*
public:
    Camera();
    bool verificaCamera();
    bool configuraCamera();
    vector<Voxel>* capturarNuvem();
    void ligaCamera();
    void desligaCamera();

    struct ImageContainer{
        FC2::Image unprocessed[3];
        FC2::Image bgru[3];
        FC2::Image packed;
    };

    enum IMAGE_SIDE{
        RIGHT = 0,
        LEFT = 1,
        CENTER = 2
    };

private:
    TriclopsContext triclops;
    FC2::Camera camera;
    FC2::Image grabbedImage;
    FC2::Error fc2Error;
    FC2T::ErrorType fc2TriclopsError;
    vector<Voxel> pontos;
    int configuraCamera( FC2::Camera &camera );
    int capturaImagem ( FC2::Camera & camera, FC2::Image &grabbedImage );
    int converteToBGRU( FC2::Image & image, FC2::Image &convertedImage );
    int generateTriclopsInput( FC2::Image const &grabbedImage, ImageContainer &imageContainer, TriclopsInput &colorData );
    int doStereo( TriclopsContext const &triclops, TriclopsInput &stereoData, TriclopsImage16 &depthImage);
    int save3dPoints( TriclopsContext const &triclops, TriclopsImage16 const &disparityImage16, TriclopsInput const &colorData, vector<Voxel> *pontos);
*/};

#endif // CAMERA_H*/
