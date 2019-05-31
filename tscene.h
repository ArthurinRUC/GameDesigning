#ifndef TSCENE_H
#define TSCENE_H

#include <QWidget>
#include<QMovie>
#include<QTimer>
#include<QLabel>
#include<QMouseEvent>
#include<QPushButton>
#include<QKeyEvent>


class tScene : public QLabel
{
    Q_OBJECT
public:
    explicit tScene(QWidget *parent = 0);
    ~tScene();

    QTimer* timer = nullptr;

    QLabel* MoneyFront = new QLabel(this);
    QLabel* MoneyBar = new QLabel(this);
    QMovie* moneybar = new QMovie(":/image/info_bar.png");
    QLabel* MoneyLabel = new QLabel(this);
    QMovie* moneylabel = new QMovie(":/image/money2.png");

    QLabel* LifeFront = new QLabel(this);
    QLabel* LifeBar = new QLabel(this);
    QMovie* lifebar = new QMovie(":/image/info_bar.png");
    QLabel* LifeLabel = new QLabel(this);
    QMovie* lifelabel = new QMovie(":/image/life2.png");

    QLabel* WaveFront = new QLabel(this);
    QLabel* WaveBar = new QLabel(this);
    QMovie* wavebar = new QMovie(":image/info_bar.png");
    QLabel* WaveLabel = new QLabel(this);
    QMovie* wavelabel = new QMovie(":/image/wave2.png");



signals:
    void toTitle();
    void toEasy();
    void toHard();

public slots:
};

class tStartScreen : public tScene
{
    Q_OBJECT
public:
    explicit tStartScreen(QWidget* parent = 0);
    ~tStartScreen();
private:
    QMovie* background = new QMovie(":/background/scene1.jpg");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
};

// 下面这个类设置选择的界面
class tStartScene : public tScene
{
    Q_OBJECT
public:
    explicit tStartScene(QWidget* parent = 0);
    ~tStartScene();
private:
    QMovie* background = new QMovie(":/GameMap/Title.jpg");
    QMovie* easy = new QMovie(":/GameMap/choose2.jpg");
    QMovie* hard = new QMovie(":/GameMap/choose1.jpg");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* easyStr = new QLabel(this);
    QLabel* hardStr = new QLabel(this);
protected:
    void mousePressEvent(QMouseEvent *event);
};

class easyScene : public tScene
{
    Q_OBJECT
public:
    explicit easyScene(QWidget* parent = 0);
    ~easyScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/GameMap/easyMap2.jpg");
    QPushButton* exit = new QPushButton(this);
    //QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave(); // emit toTitle();
};

class hardScene : public tScene
{
    Q_OBJECT
public:
    explicit hardScene(QWidget* parent = 0);
    ~hardScene();
protected:
    //void keyPressEvent(QKeyEvent *event); //僵尸的出现
private:
    QMovie* background = new QMovie(":/GameMap/hardMap2.jpg");
    //QPushButton* exit = new QPushButton(this);
    //QPoint cell;
    //void uiSetup(); //在PVZ中用来设计僵尸的出现等
private slots:
    //void onTimer(); //在PVZ中用于设置阳光
    void leave();
};

#endif // TSCENE_H
