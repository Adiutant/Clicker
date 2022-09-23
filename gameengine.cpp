#include "gameengine.h"

GameEngine::GameEngine()
{    



}

GameEngine::~GameEngine()
{
    levelTimer->stop();
    levelTimer->deleteLater();
}
void GameEngine::onGameStart()
{
    if (levelTimer->isActive()){
        levelTimer->stop();
    }
    score.looses = 0;
    score.wins = 0;
    int  currentTaskValue = randomBetween(0, 10, QDateTime::currentDateTime().toMSecsSinceEpoch());
    emit displayCurrentLevel("-");
    QThread::currentThread()->msleep(200);
    emit displayScore(QPair<int,int>(score.wins,score.looses));
    score.currentClicks = 0;
    score.currentTarget = currentTaskValue;
    levelTimer->start(2000);
    emit displayCurrentLevel(QString::number(currentTaskValue));
}
void GameEngine::onGameStop()
{
    levelTimer->stop();
}

void GameEngine::initEngine()
{
    levelTimer = new QTimer();
    connect(levelTimer, &QTimer::timeout, this, &GameEngine::onNewLevel);
}

void GameEngine::onMouseClicked()
{
    score.currentClicks++;
}

void GameEngine::onNewLevel()
{
    if (score.currentClicks == score.currentTarget){
        score.wins++;
    } else {
        score.looses++;
    }
    qDebug()<<score.wins<<"wl"<< score.looses;
    qDebug()<<score.currentClicks<<"ct"<< score.currentTarget;
    emit displayScore(QPair<int,int>(score.wins,score.looses));
    int  currentTaskValue = randomBetween(0, 10, QDateTime::currentDateTime().toMSecsSinceEpoch());
    emit displayCurrentLevel("-");
    levelTimer->stop();
    QThread::currentThread()->msleep(200);
    score.currentClicks = 0;
    score.currentTarget = currentTaskValue;
    levelTimer->start();
    emit displayCurrentLevel(QString::number(currentTaskValue));

}
