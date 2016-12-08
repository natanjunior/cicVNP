// Canvas.cpp

#include "Canvas.h"

Canvas::Canvas(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    xTsl = 0.0;
    yTsl = 0.0;
    zTsl = 0.0;
    zoom = 10;
    point = 1.0;
    pontos = NULL;
    moveOption = true;
}

Canvas::~Canvas(){}

QSize Canvas::minimumSizeHint() const{
    return QSize(50, 50);
}

QSize Canvas::sizeHint() const{
    return QSize(500, 500);
}

void Canvas::setXmovement(int move){
    if(moveOption)
        this->setXRotation(move-180);
    else
        this->setXTranslate((move/100.0)-1.8);
}

void Canvas::setYmovement(int move){
    if(moveOption)
        this->setYRotation(move-180);
    else
        this->setYTranslate((move/100.0)-1.8);
}

void Canvas::setZmovement(int move){
    if(moveOption)
        this->setZRotation(move-180);
    else
        this->setZTranslate((move/100.0)-1.8);
}

void Canvas::setMoveOption(int opt){
    if(opt==2){
        // ROTATE MODE
        moveOption=false;
        emit xSliderChanged((xTsl+1.8)*100);
        emit ySliderChanged((yTsl+1.8)*100);
        emit zSliderChanged((zTsl+1.8)*100);
    }else{
        // MOVE MODE
        moveOption=true;
        emit xSliderChanged(xRot+180);
        emit ySliderChanged(yRot+180);
        emit zSliderChanged(zRot+180);
    }
}

static void qNormalizeAngle(int &angulo){
    while (angulo < 0)
        angulo += 360 * 16;
    while (angulo > 360)
        angulo -= 360 * 16;
}

void Canvas::setXRotation(int angulo){
    qNormalizeAngle(angulo);
    if (angulo != xRot) {
        xRot = angulo;
        emit xSliderChanged(angulo+180);
        updateGL();
    }
}

void Canvas::setYRotation(int angulo){
    qNormalizeAngle(angulo);
    if (angulo != yRot) {
        yRot = angulo;
        emit ySliderChanged(angulo+180);
        updateGL();
    }
}

void Canvas::setZRotation(int angulo){
    qNormalizeAngle(angulo);
    if (angulo != zRot) {
        zRot = angulo;
        emit zSliderChanged(angulo+180);
        updateGL();
    }
}

void Canvas::setXTranslate(float distancia){
    if (distancia != xTsl) {
        xTsl = distancia;
        emit xSliderChanged((distancia+1.8)*100);
        updateGL();
    }
}

void Canvas::setYTranslate(float distancia){
    if (distancia != yTsl) {
        yTsl = distancia;
        emit ySliderChanged((distancia+1.8)*100);
        updateGL();
    }
}

void Canvas::setZTranslate(float distancia){
    if (distancia != zTsl) {
        zTsl = distancia;
        emit zSliderChanged((distancia+1.8)*100);
        updateGL();
    }
}

void Canvas::setZoom(int z){
    if (z != zoom) {
        zoom = z;
        emit zoomChanged(z);
        updateGL();
    }
}

void Canvas::setPoint(int p){
    if (p != point) {
        point = p/10.0;
        emit pointChanged(p);
        updateGL();
    }
}

void Canvas::screenshoot(){
    QPixmap pixmap = renderPixmap(width(), height());
    QString format = "jpg";
    QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(format.toUpper())
                                                    .arg(format));
    if (!fileName.isEmpty())
        pixmap.save(fileName, format.toLatin1().constData());
}

void Canvas::initializeGL(){
    glShadeModel(GL_SMOOTH);
    glClearDepth(100.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //		gl.glDepthFunc(GL2.GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
}

void Canvas::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glScalef (zoom/10.0, zoom/10.0, zoom/10.0);
    glTranslatef(xTsl, yTsl, zTsl);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 328.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glPointSize(point);
    glBegin(GL_POINTS);
    vector<Voxel> *pontos = controlador->getPontos();
    for (unsigned long i = 0; i < pontos->size(); i++) {
        Voxel ponto = pontos->at(i);
        glColor3f(ponto.getR_color(), ponto.getG_color(), ponto.getB_color());
        float x, y, z;
        x = ponto.getX_coord();
        y = ponto.getY_coord();
        z = ponto.getZ_coord();
        if(controlador->getFormato()==2){ //momentaneo
            bool teste = fabs(z - 0.227799997) < numeric_limits<float>::epsilon();
            if(!teste){
                z = (z/255)+0.227799997;
            }
        }
        glVertex3f(x, y, z);
    }
    glEnd();
}

void Canvas::resizeGL(int width, int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glClearColor(0.875, 0.875, 0.875, 0.875);
    glLoadIdentity();
    float* tamOrtho = controlador->getTamCanvas();
    orthoLeft = tamOrtho[0];
    if(controlador->getFormato()==2){
        GLdouble aspect = width / (height ? height : 1);
        const GLdouble zNear = 0.1, zFar = 20.0, fov = 120.0;
        gluPerspective(fov,aspect,0.00001,100);
    }else{
        glOrtho(tamOrtho[0], tamOrtho[1], tamOrtho[2], tamOrtho[3], tamOrtho[4], tamOrtho[5]);
    }
    glMatrixMode(GL_MODELVIEW);
}

void Canvas::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if(moveOption){
        if (event->buttons() & Qt::LeftButton) {
            setXRotation(xRot + 1 * dy);
            setYRotation(yRot + 1 * dx);
        } else if (event->buttons() & Qt::RightButton) {
            setXRotation(xRot + 1 * dy);
            setZRotation(zRot + 1 * dx);
        }
    }else{
        if (event->buttons() & Qt::LeftButton) {
            setXTranslate(xTsl + 0.005 * dx);
            setYTranslate(yTsl + 0.005 * dy);
        } else if (event->buttons() & Qt::RightButton) {
            setXTranslate(xTsl + 0.005 * dx);
            setZTranslate(zTsl + 0.005 * dy);
        }
    }

    lastPos = event->pos();
}

void Canvas::visaoInicial(){
    setXRotation(0);
    setYRotation(0);
    setZRotation(0);
    setXTranslate(0.0);
    setYTranslate(0.0);
    setZTranslate(0.0);
    setZoom(10);
    setPoint(10);
    if(controlador->getFormato()==2){
        setXTranslate(controlador->getModelo()->getTamX()/2.0);
        setYTranslate(controlador->getModelo()->getTamY()/2.0);
        setZRotation(180);
    }
}

void Canvas::setControlador(Controlador *c){
    controlador = c;
    pontos = c->getPontos();
    float* tamOrtho = controlador->getTamCanvas();
    orthoLeft = tamOrtho[0];
    orthoRight = tamOrtho[1];
    orthoBottom = tamOrtho[2];
    orthoTop = tamOrtho[3];
    orthoNear = tamOrtho[4];
    orthoFar = tamOrtho[5];
    if(controlador->getFormato()==2){
//        xTsl = controlador->getModelo()->getTamX()/2.0;
//        yTsl = controlador->getModelo()->getTamY()/2.0;
        yRot = 180;
    }
}
