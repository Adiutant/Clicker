#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    engine = new GameEngine();
    gameEngineThread = new QThread();
    connect(ui->startPB, &QPushButton::clicked, engine, &GameEngine::onGameStart);
    connect(ui->stopPB, &QPushButton::clicked, engine, &GameEngine::onGameStop);
    connect(engine,&GameEngine::displayCurrentLevel, this, &MainWindow::onDisplayCurrentLevel);
    connect(engine,&GameEngine::displayScore, this, &MainWindow::onDisplayScore);
    connect(this, &MainWindow::mouseClicked,engine,&GameEngine::onMouseClicked);
    ui->trueCount->setStyleSheet("QLCDNumber {background-color:transparent;color:green}");
    ui->falseCount->setStyleSheet("QLCDNumber {background-color:transparent;color:red}");
    ui->targetValue->setStyleSheet("QLCDNumber {background-color:transparent;color:black}");
    connect(gameEngineThread, &QThread::started, engine, &GameEngine::initEngine);
    engine->moveToThread(gameEngineThread);
    gameEngineThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int key= event->button();
    if (key == Qt::MouseButton::LeftButton){
        emit mouseClicked();
    }
}

void MainWindow::onDisplayCurrentLevel(QString info)
{

    ui->targetValue->display(info);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox messagebox(this);
    messagebox.setWindowTitle("До свидания");
    messagebox.setText("Приходите еще!");
    messagebox.addButton("Обязательно приду!", QMessageBox::AcceptRole);
    int res = messagebox.exec();
    if (res != QMessageBox::AcceptRole) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::onDisplayScore(QPair<int, int> score)
{
    ui->trueCount->display(score.first);
    ui->falseCount->display(score.second);
}




