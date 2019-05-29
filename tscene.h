#ifndef TSCENE_H
#define TSCENE_H

#include <QWidget>
#include<QMovie>
#include<QTimer>
#include<QLabel>
#include<QMouseEvent>
#include<QPushButton>


class tScene : public QLabel
{
    Q_OBJECT
public:
    explicit tScene(QWidget *parent = 0);
    ~tScene();

    QTimer* timer = nullptr;


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
    QLabel* UserName = new QLabel(this);
    QLabel* BestTime = new QLabel(this);
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
    //void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/GameMap/easyMap.jpg");
    QPushButton* exit = new QPushButton(this);
    //QPoint cell;
    //void uiSetup();
private slots:
    //void onTimer();
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
    QMovie* background = new QMovie(":/GameMap/hardMap.jpg");
    QPushButton* exit = new QPushButton(this);
    //QPoint cell;
    //void uiSetup(); //在PVZ中用来设计僵尸的出现等
private slots:
    //void onTimer(); //在PVZ中用于设置阳光
    void leave();
};

#endif // TSCENE_H
