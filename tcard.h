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
};

class tNormalTowerCard : public tCard
{
public:
    tNormalTowerCard(QLabel* parent = 0);
    ~tNormalTowerCard();
private:
    QMovie* anim = new QMovie(":/picture/normaltower.png");
};


class tFireTowerCard : public tCard
{
public:
    tFireTowerCard(QLabel* parent = 0);
    ~tFireTowerCard();
private:
    QMovie* anim = new QMovie(":/picture/firetower.png");
};

class tIceTowerCard : public tCard
{
public:
    tIceTowerCard(QLabel* parent = 0);
    ~tIceTowerCard();
private:
    QMovie* anim = new QMovie(":/picture/icetower.png");
};

class tLaserTowerCard : public tCard
{
public:
    tLaserTowerCard(QLabel* parent = 0);
    ~tLaserTowerCard();
private:
    QMovie* anim = new QMovie(":/picture/lasertower.png");
};
#endif // TCARD_H
