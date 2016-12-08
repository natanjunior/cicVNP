#include "Camera.h"

#include "qdebug.h"
/*
Camera::Camera(){

}


bool Camera::verificaCamera(){
    FC2::BusManager busMgr;
    unsigned int numCameras;
    if (busMgr.GetNumOfCameras(&numCameras) != FC2::PGRERROR_OK)
        return false;
    if(numCameras<=0)
        return false;
    return true;
}

bool Camera::configuraCamera(){
    camera.Connect();

    //    FC2T::StereoCameraMode mode = FC2T::TWO_CAMERA;
    FC2T::StereoCameraMode mode = FC2T::THREE_CAMERA;
    fc2TriclopsError = FC2T::setStereoMode( camera, mode );
    if ( fc2TriclopsError ){
        qDebug() << FC2T::handleFc2TriclopsError(fc2TriclopsError, "setStereoMode");
        return false;
    }

    FC2::CameraInfo camInfo;
    fc2Error = camera.GetCameraInfo(&camInfo);
    if (fc2Error != FC2::PGRERROR_OK){
        qDebug() << FC2T::handleFc2Error(fc2Error);
        return false;
    }

    fc2TriclopsError = FC2T::getContextFromCamera( camInfo.serialNumber, &triclops );
    if (fc2TriclopsError != FC2T::ERRORTYPE_OK){
        qDebug() << FC2T::handleFc2TriclopsError(fc2TriclopsError, "getContextFromCamera");
        return false;
    }

    triclopsSetResolution( triclops, 960, 1280 );
    triclopsSetDisparity( triclops, 0, 255 );
    triclopsSetStereoMask( triclops, 15 );
    triclopsSetEdgeCorrelation( triclops, 1 ) ;
    triclopsSetEdgeMask( triclops, 11 ) ;

    triclopsSetTextureValidation( triclops, 0 );
    triclopsSetUniquenessValidation( triclops, 0 );

    triclopsSetSurfaceValidation( triclops, 1 );
    triclopsSetSurfaceValidationSize( triclops, 1 );
    triclopsSetSurfaceValidationDifference( triclops, 0.5 );

    triclopsSetSubpixelInterpolation( triclops, 1 ) ;
    triclopsSetStrictSubpixelValidation( triclops, 1 );

    camera.StopCapture();
    camera.Disconnect();

    return true;
}

void Camera::ligaCamera(){
    camera.Connect();
    camera.StartCapture();
}

vector<Voxel>* Camera::capturarNuvem(){
    pontos.clear();

    fc2Error = camera.RetrieveBuffer(&grabbedImage);
    if (fc2Error != FC2::PGRERROR_OK)
        FC2T::handleFc2Error(fc2Error);
        //return NULL; // FC2T::handleFc2Error(fc2Error);

    TriclopsInput triclopsColorInput;
    ImageContainer imageContainer;

    if ( generateTriclopsInput( grabbedImage, imageContainer, triclopsColorInput))
        return NULL; // EXIT_FAILURE;

    TriclopsImage16 disparityImage16;

    triclopsRectify( triclops, const_cast<TriclopsInput *>(&triclopsColorInput) );

    triclopsStereo( triclops );

    triclopsGetImage16( triclops, TriImg16_DISPARITY, TriCam_REFERENCE, &disparityImage16 );

    //    char const * pDispFilename = "disparity16.pgm";
    //    triclopsSaveImage16( &depthImage, const_cast<char *>(pDispFilename) );

    if ( save3dPoints( triclops, disparityImage16, triclopsColorInput, &pontos))
        return NULL; // EXIT_FAILURE;

    return &pontos;
}

void Camera::desligaCamera(){
    camera.StopCapture();
    camera.Disconnect();

    TriclopsError te;
    te = triclopsDestroyContext( triclops ) ;
}

int Camera::converteToBGRU( FC2::Image &image, FC2::Image &convertedImage ){
    FC2::Error fc2Error;
    fc2Error = image.SetColorProcessing(FC2::HQ_LINEAR);
    if (fc2Error != FC2::PGRERROR_OK)
        return FC2T::handleFc2Error(fc2Error);

    fc2Error = image.Convert(FC2::PIXEL_FORMAT_BGRU, &convertedImage);
    if (fc2Error != FC2::PGRERROR_OK)
        return FC2T::handleFc2Error(fc2Error);

    return 0;
}

int Camera::generateTriclopsInput( FC2::Image const &grabbedImage, ImageContainer &imageContainer, TriclopsInput &triclopsColorInput) {
    FC2T::ErrorType fc2TriclopsError;
    TriclopsError te;

    FC2::Image * unprocessedImage = imageContainer.unprocessed;

//    fc2TriclopsError = FC2T::unpackUnprocessedRawOrMono16Image( grabbedImage, true, unprocessedImage[RIGHT], unprocessedImage[LEFT]);
    fc2TriclopsError = FC2T::unpackUnprocessedRgbImage(
                    grabbedImage,
                    unprocessedImage[RIGHT],
                    unprocessedImage[CENTER],
                    unprocessedImage[LEFT]);

    if (fc2TriclopsError != FC2T::ERRORTYPE_OK)
        return FC2T::handleFc2TriclopsError(fc2TriclopsError, "unpackUnprocessedRawOrMono16Image");

    FC2::Image * bgruImage = imageContainer.bgru;

    for ( int i = 0; i < 3; ++i ){
        if ( converteToBGRU(unprocessedImage[i], bgruImage[i]) ){
            return 1;
        }
    }

    FC2::Image & packedColorImage = imageContainer.packed;

//    fc2TriclopsError = FC2T::packTwoSideBySideRgbImage( bgruImage[RIGHT], bgruImage[LEFT], packedColorImage );
    fc2TriclopsError = FC2T::packThreeSideBySideRgbImage(bgruImage[RIGHT], bgruImage[CENTER], bgruImage[LEFT], packedColorImage);

    if (fc2TriclopsError != FC2T::ERRORTYPE_OK)
        return handleFc2TriclopsError(fc2TriclopsError, "packTwoSideBySideRgbImage");

    te = triclopsBuildPackedTriclopsInput( grabbedImage.GetCols(),
                                            grabbedImage.GetRows(),
                                            packedColorImage.GetStride(),
                                            (unsigned long)grabbedImage.GetTimeStamp().seconds,
                                            (unsigned long)grabbedImage.GetTimeStamp().microSeconds,
                                            packedColorImage.GetData(),
                                            &triclopsColorInput );

    return 0;
}

int Camera::save3dPoints( TriclopsContext const &triclops, TriclopsImage16 const &disparityImage16, TriclopsInput const &colorData, vector<Voxel> *pontos){
    TriclopsColorImage colorImage = {0};
    TriclopsError te;
    float            x, y, z, r, g, b, ax, ay, az;
    int              nPoints = 0;
    int	             pixelinc;
    int	             i, j, k;
    unsigned short * row, * pixelInt;
    unsigned short   disparity;

    te = triclopsRectifyColorImage(triclops, TriCam_REFERENCE, const_cast<TriclopsInput *>(&colorData), &colorImage);

    pixelinc = disparityImage16.rowinc/2;

    pixelInt = disparityImage16.data + 0 * pixelinc;
    triclopsRCDMappedToWorldXYZ( triclops, 0, 0, pixelInt[0], &ax, &ay, &az );

    for ( i = 0, k = 0; i < disparityImage16.nrows; i++ ){
        row = disparityImage16.data + i * pixelinc;
        for ( j = 0; j < disparityImage16.ncols; j++, k++ ){
            disparity = row[j];

            triclopsRCDMappedToWorldXYZ( triclops, i, j, disparity, &x, &y, &z );

            r = colorImage.red[k]/256.0f;
            g = colorImage.green[k]/256.0f;
            b = colorImage.blue[k]/256.0f;

//            Voxel ponto = *new Voxel((j-160)/640.0f, (i-120)/480.0f, z, r, g, b);
            Voxel ponto = *new Voxel(x, y, z-az, r, g, b);
            pontos->push_back(ponto);
        }
    }

    qDebug() << "here";

    return 0;

}*/
