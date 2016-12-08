#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAXRECENTFILE 5

#include <QtWidgets>
#include "ui_mainwindow.h"
#include "TelaModelo.h"
#include "TelaVideo.h"
#include "TelaCamera.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include "Controlador.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setControlador(Controlador *c);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_actionOpen_Model_triggered();
    void AbrirArqRecente();
    void on_actionOpen_Video_triggered();
    void on_actionClear_Menu_triggered();
    void on_openModelButton_clicked();
    void on_openVideoButton_clicked();
    void on_rf_1_windowTitleChanged(const QString &title);
    void on_rf_2_windowTitleChanged(const QString &title);
    void on_rf_3_windowTitleChanged(const QString &title);
    void on_rf_4_windowTitleChanged(const QString &title);
    void on_rf_5_windowTitleChanged(const QString &title);
    void on_actionSave_as_triggered();
    void on_titleOpenModel_clicked();
    void on_titleOpenVideo_clicked();
    void on_openCameraButton_clicked();

    void on_rf_titulo_1_linkActivated(const QString &link);

signals:
    void rfNomeChanged(QString);

private:
    Ui::MainWindow *ui;
    QString config;
    Controlador *controlador;
    TelaModelo *telaModelo;
    TelaVideo *telaVideo;
    TelaCamera *telaCamera;
    QAction* RecentFiles[MAXRECENTFILE];
    QWidget* TabRecentFiles[MAXRECENTFILE];
    QString strippedName(const QString &fullFileName);
    QString extensionName(const QString &fullFileName);
    QString arqCorrente;
    void criarArqRecentes();
    void setArqCorrente(QString endArq);
    void updateRecentFileActions();
    void visaoInicial();
    void setShift(int opt);
    void abrirModelo(QString arq = NULL);
    void abrirVideo(QString arq = NULL);
    void abrirCamera();
    void abrir();
};

#endif // MAINWINDOW_H
