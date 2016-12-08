#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->rf_1->hide();
    ui->rf_2->hide();
    ui->rf_3->hide();
    ui->rf_4->hide();
    ui->rf_5->hide();

    config = QDir::currentPath() + "/voqxconfig.ini";
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setControlador(Controlador *c){
    controlador = c;
    criarArqRecentes();
}

void MainWindow::criarArqRecentes(){
    for (int i = 0; i < MAXRECENTFILE; ++i) {
        RecentFiles[i] = new QAction(this);
        RecentFiles[i]->setVisible(false);
        connect(RecentFiles[i], SIGNAL(triggered()), this, SLOT(AbrirArqRecente()));
        ui->menuRecentFiles->addAction(RecentFiles[i]);
    }

    TabRecentFiles[0] = ui->rf_1;
    TabRecentFiles[1] = ui->rf_2;
    TabRecentFiles[2] = ui->rf_3;
    TabRecentFiles[3] = ui->rf_4;
    TabRecentFiles[4] = ui->rf_5;

    this->updateRecentFileActions();
}

void MainWindow::setArqCorrente(QString endArq){
    QSettings settings(config, QSettings::NativeFormat);
    QStringList files = settings.value("RecentFile").toStringList();
    files.removeAll(endArq);
    files.prepend(endArq);
    while (files.size() > MAXRECENTFILE)
            files.removeLast();

    settings.setValue("RecentFile", files);

    this->updateRecentFileActions();

    this->setWindowTitle(strippedName(endArq));

    ui->statusbar->showMessage(tr("File loaded"), 2000);
}

void MainWindow::updateRecentFileActions(){
    QSettings settings(config, QSettings::NativeFormat);
    QStringList files = settings.value("RecentFile").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MAXRECENTFILE);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        RecentFiles[i]->setText(text);
        RecentFiles[i]->setData(files[i]);
        RecentFiles[i]->setVisible(true);

        if(controlador->getModo()==0){
            TabRecentFiles[i]->setProperty("nome", text);
            TabRecentFiles[i]->setProperty("endArq", files[i]);

            TabRecentFiles[i]->setWindowTitle(strippedName(files[i]));

            TabRecentFiles[i]->show();
        }
    }

    for (int j = numRecentFiles; j < MAXRECENTFILE; ++j)
        RecentFiles[j]->setVisible(false);
}

QString MainWindow::strippedName(const QString &fullFileName){
    return QFileInfo(fullFileName).fileName();
}

QString MainWindow::extensionName(const QString &fullFileName){
    return QFileInfo(fullFileName).completeSuffix();
}

void MainWindow::AbrirArqRecente(){
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString tipo = extensionName(action->data().toString());
        if((tipo.compare("txt")==0)||(tipo.compare("ply")==0)||(tipo.compare("pts")==0)){
            abrirModelo(action->data().toString());
        }else if(tipo.compare("pcv")==0){
            abrirVideo(action->data().toString());
        }
    }
}

void MainWindow::abrir(){
    if(controlador->getModo()==1)
        telaModelo->~TelaModelo();
    else if(controlador->getModo()==2)
        telaVideo->~TelaVideo();
    else if(controlador->getModo()==4)
        telaCamera->~TelaCamera();
}

void MainWindow::abrirModelo(QString fileName){
    abrir();
    if(fileName==NULL)
        fileName = QFileDialog::getOpenFileName(this, tr("Open model"), QDir::homePath(), tr("Model (*.pts *.ply *.txt)"));
    if(fileName.isEmpty() || fileName.isNull())
        return;
    controlador->novoModelo(fileName.toStdString());
    telaModelo = new TelaModelo(this, controlador);
    setCentralWidget(telaModelo);
    setArqCorrente(fileName);
    ui->actionSave_as->setEnabled(true);
    controlador->setModo(1);
}

void MainWindow::abrirVideo(QString fileName){
    abrir();
    if(fileName==NULL)
        fileName = QFileDialog::getOpenFileName(this, tr("Open video"), QDir::homePath(), tr("PCV File (*.pcv)"));
    if(fileName.isEmpty() || fileName.isNull())
        return;
    controlador->novoVideo(fileName.toStdString());
    telaVideo = new TelaVideo(this, controlador);
    setCentralWidget(telaVideo);
    setArqCorrente(fileName);
    controlador->setModo(2);
}

void MainWindow::abrirCamera(){
    abrir();
    if(controlador->getCamera() != NULL){
        telaCamera = new TelaCamera(this, controlador);
        setCentralWidget(telaCamera);
        controlador->setModo(4);
    }else{
        ui->statusbar->showMessage(tr("Camera não conectada!"), 2000);
    }
}

void MainWindow::on_actionOpen_Model_triggered(){
    abrirModelo(NULL);
}

void MainWindow::on_actionOpen_Video_triggered(){
    abrirVideo(NULL);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Shift)
        this->setShift(2);
    else if(e->key() == Qt::Key_Space)
        this->visaoInicial();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Shift)
        this->setShift(0);
}

void MainWindow::setShift(int opt){
    if(controlador->getModo()==1)
        telaModelo->setShift(opt);
    else if(controlador->getModo()==2)
        telaVideo->setShift(opt);
}

void MainWindow::visaoInicial(){
    if(controlador->getModo()==1)
        telaModelo->visaoInicial();
    else if(controlador->getModo()==2)
        telaVideo->visaoInicial();
}

void MainWindow::on_actionClear_Menu_triggered(){
    QSettings settings(config, QSettings::NativeFormat);
    QStringList files = settings.value("RecentFile").toStringList();
    files.clear();
    settings.setValue("RecentFile", files);
    this->updateRecentFileActions();
}

void MainWindow::on_openModelButton_clicked(){
    abrirModelo(NULL);
}

void MainWindow::on_openVideoButton_clicked(){
    abrirVideo(NULL);
}

void MainWindow::on_rf_1_windowTitleChanged(const QString &title){
    ui->rf_titulo_1->setText(title);
}

void MainWindow::on_rf_2_windowTitleChanged(const QString &title){
    ui->rf_titulo_2->setText(title);
}

void MainWindow::on_rf_3_windowTitleChanged(const QString &title){
    ui->rf_titulo_3->setText(title);
}

void MainWindow::on_rf_4_windowTitleChanged(const QString &title){
    ui->rf_titulo_4->setText(title);
}

void MainWindow::on_rf_5_windowTitleChanged(const QString &title){
    ui->rf_titulo_5->setText(title);
}

void MainWindow::on_actionSave_as_triggered(){ // alterar isso
    QString format = "pts";
    QString initialPath = QDir::homePath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath, tr("PTS File (*.pts);;PLY File (*.ply)"));

    controlador->salvarModelo(fileName.toUtf8().constData());
}

void MainWindow::on_titleOpenModel_clicked(){
    abrirModelo(NULL);
}

void MainWindow::on_titleOpenVideo_clicked(){
    abrirVideo(NULL);
}

void MainWindow::on_openCameraButton_clicked(){
    abrirCamera();
}

void MainWindow::on_rf_titulo_1_linkActivated(const QString &link){
//    qDebug() << link;
}
