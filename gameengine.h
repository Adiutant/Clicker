#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <QTimer>
#include <QDateTime>
#include <QObject>
#include <QThread>
#include <QDebug>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine();
    ~GameEngine();
private:
    struct Score{
        int currentTarget{0};
        int currentClicks{0};
        int wins{0};
        int looses{0};
    };
    QTimer *levelTimer;
    Score score{};
    inline static int randomBetween(int low, int high, int seed)
    {
        qsrand(seed);
        return (qrand() % ((high + 1) - low) + low);
    }
signals:
    void displayCurrentLevel(QString);
    void displayScore(QPair<int,int>);
public slots:
    void onGameStart();
    void onGameStop();
    void initEngine();
    void onMouseClicked();
    void onNewLevel();
};

#endif // GAMEENGINE_H
