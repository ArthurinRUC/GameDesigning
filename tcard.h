#ifndef TCARD_H
#define TCARD_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QMouseEvent>

#include "tScene.h"

class tScene;

class tCard : public QLabel
{
public:
    tCard(QLabel* parent = 0);
    ~tCard();
    int plantIndex;
    int sunPoint = 50;
    int frame_max = 1, frame = 1;
    virtual void act();

    QWidget* front;
    QWidget* back;
    QLabel* frontText;
    tScene* scene;

    void setIndex(int index);
    void transFront();
protected:
    void mousePressEvent(QMouseEvent* event);
};

class tNormalTowerCard : public tCard
{
public:
    tNormalTowerCard(QLabel* parent = 0);
    ~tNormalTowerCard();
private:
    QMovie* anim = new QMovie(":/picture/tower1.jpg");
};

#endif // TCARD_H
