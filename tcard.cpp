#include "tCard.h"

tCard::tCard(QLabel* parent) : QLabel(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    back = new QWidget(this);
    back->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    back->show();
    back->raise();
    front = new QWidget(this);
    front->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    front->show();
    front->raise();
    frontText = new QLabel(this);
    frontText->setText("50");
    frontText->setGeometry(60, 33, 40, 20);
    frontText->setAlignment(Qt::AlignHCenter);
    frontText->setFont(QFont("Calibri", 11));
    frontText->show();
    frontText->raise();
    this->show();
    this->raise();
}

void tCard::act()
{
    if (this->frame > 0)
    {
        this->frame --;
    }
    this->transFront();
    this->raise();
}

void tCard::setIndex(int index)
{
    this->setGeometry(125, 40 + 60 * index, 100, 60);
}

void tCard::transFront()
{
    front->setGeometry(0, 6, 100, 54 * this->frame / this->frame_max);
    if (scene->sunPoint >= this->sunPoint)
    {
        back->setGeometry(0, 0, 0, 0);
    }
    else
    {
        back->setGeometry(0, 6, 100, 54);
    }
}

void tCard::mousePressEvent(QMouseEvent* event)
{
    if (scene->currentCard != nullptr)
    {
        scene->currentCard->move(scene->currentPos);
    }
    if (event->button() == Qt::LeftButton)
    {
        if (this->front->height() > 0)
        {
            QSound::play(":/Sounds/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        if (this->scene->sunPoint < this->sunPoint)
        {
            QSound::play(":/Sounds/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        QSound::play(":/Sounds/rc/Place.wav");
        scene->currentPos = this->pos();
        scene->currentCard = this;
    }
    else
    {
        scene->currentCard = nullptr;
    }
}

tCard::~tCard()
{
    delete (this->back);
    delete (this->front);
    delete (this->frontText);
}

tNormalTowerCard::tNormalTowerCard(QLabel *parent):tCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("50");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 1;
    this->sunPoint = 50;
}

tNormalTowerCard::~tNormalTowerCard()
{
    delete this->anim;
}
