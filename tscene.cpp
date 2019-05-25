#include "tscene.h"


tScene::tScene(QWidget *parent) : QLabel(parent)
{

}

tScene::~tScene()
{

}

tStartScreen::tStartScreen(QWidget* parent) : tScene(parent)
{
    this->setGeometry(0, 0, 800, 600); //界面
    this->setMovie(this->background);  //图片
    this->background->start();      //
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(255,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

tStartScreen::~tStartScreen()
{
    delete this->background;
    delete this->front;
}

void tStartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}
