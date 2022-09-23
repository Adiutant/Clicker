#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include "gameengine.h"
#include <QThread>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QThread *gameEngineThread;
    GameEngine *engine;
protected:
     virtual void mousePressEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void onDisplayCurrentLevel(QString);
    void onDisplayScore(QPair<int,int>);
signals:
    void mouseClicked();

};
#endif // MAINWINDOW_H
