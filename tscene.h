#ifndef TSCENE_H
#define TSCENE_H

#include <QWidget>
#include<QMovie>
#include<QTimer>
#include<QLabel>
#include<QMouseEvent>


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
    int frame = 1000;
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
    QMovie* lawn = new QMovie(":/GameMap/choose1.jpg");
    QMovie* dark = new QMovie(":/GameMap/choose2.jpg");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* UserName = new QLabel(this);
    QLabel* BestTime = new QLabel(this);
protected:
    void mousePressEvent(QMouseEvent *event);
};


#endif // TSCENE_H
