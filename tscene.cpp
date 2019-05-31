#include "tscene.h"


tScene::tScene(QWidget *parent) : QLabel(parent)
{

}

tScene::~tScene()
{
    if (!(this->MoneyFront == nullptr)) delete this->MoneyFront;
    if (!(this->MoneyBar == nullptr)) delete this->MoneyBar;
    if (!(this->moneybar == nullptr))delete this->moneybar;
    if (!(this->MoneyLabel == nullptr)) delete this->MoneyLabel;
    if (!(this->moneylabel == nullptr)) delete this->moneylabel;

    if (!(this->LifeFront == nullptr))delete this->LifeFront;
    if (!(this->LifeBar == nullptr)) delete this->LifeBar;
    if (!(this->lifebar == nullptr)) delete this->lifebar;
    if (!(this->LifeLabel == nullptr))delete this->LifeLabel;
    if (!(this->lifelabel == nullptr)) delete this->lifelabel;

    if (!(this->WaveFront == nullptr)) delete this->WaveFront;
    if (!(this->WaveBar == nullptr))delete this->WaveBar;
    if (!(this->wavebar == nullptr)) delete this->wavebar;
    if (!(this->WaveLabel == nullptr)) delete this->WaveLabel;
    if (!(this->wavelabel == nullptr))delete this->wavelabel;
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

tStartScene::tStartScene(QWidget* parent) : tScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn2->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn1->setMovie(easy);
    easy->start();
    btn2->setMovie(hard);
    hard->start();
    btn1->setGeometry(120, 205, 180, 180);
    btn2->setGeometry(500, 205, 180, 180);
    btn1->show();
    btn2->show();
    title->setText("choose a level");
    title->setGeometry(250, 0, 300, 100);
    title->setFont(QFont("Consolas", 18));
    title->show();

    QString str1="Easy Map";
    QString str2="Hard Map";
    easyStr->setGeometry(150, 400, 300, 100);
    hardStr->setGeometry(530,400,300,100);
    easyStr->setText(str1);
    hardStr->setText(str2);
    easyStr->setFont(QFont("Consolas", 14));
    hardStr->setFont(QFont("Consolas", 14));
    easyStr->show();
    hardStr->show();

}

tStartScene::~tStartScene()
{
    delete this->background;
    delete this->easy;
    delete this->hard;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
    delete this->easyStr;
    delete this->hardStr;
}


void tStartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(120, 205, 180, 180).contains(event->pos()))
    {
        emit toEasy();
    }
    if (QRect(500, 205, 180, 180).contains(event->pos()))
    {
        emit toHard();
    }
}

easyScene::easyScene(QWidget* parent) : tScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    this->uiSetup();
}

void easyScene::uiSetup()
{
    MoneyBar->setGeometry(120, 400, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(10, 480, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(60, 400, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(400, 400, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(290, 480, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(340, 400, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);


    WaveBar->setGeometry(680, 400, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(570, 480, 300, 200);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(615, 400, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    exit->setGeometry(700, 0, 60, 60); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
}

easyScene::~easyScene()
{
    delete this->background;
    if (!(this->MoneyFront == nullptr)) delete this->MoneyFront;
    if (!(this->MoneyBar == nullptr)) delete this->MoneyBar;
    if (!(this->moneybar == nullptr))delete this->moneybar;

    if (!(this->LifeFront == nullptr)) delete this->LifeFront;
    if (!(this->LifeBar == nullptr)) delete this->LifeBar;
    if (!(this->lifebar == nullptr))delete this->lifebar;

    if (!(this->WaveFront == nullptr)) delete this->WaveFront;
    if (!(this->WaveBar == nullptr)) delete this->WaveBar;
    if (!(this->wavebar == nullptr))delete this->wavebar;
}

void easyScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    /*case Qt::Key_1:
        this->putZombie(qrand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(qrand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(qrand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(qrand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(qrand() % 5, 4);
        break;
    case Qt::Key_6:
        this->putZombie(qrand() % 5, 5);
        break;
    case Qt::Key_7:
        this->putZombie(qrand() % 5, 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->threat = 6001;
        break;*/
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void easyScene::onTimer()
{
    /*this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->createZombie();
    if (qrand() % 521 < 100)
    {
        zBonus* sun = new zSunFall(this);
        Bonuses.append(sun);
    }*/
    this->exit->raise();
    //this->judge();
}

void easyScene::leave()
{
    emit toTitle();
}


// 以下是对复杂地图的设计
hardScene::hardScene(QWidget* parent) : tScene(parent)
{
    this->setGeometry(0, 0, 1400, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    //this->uiSetup();
}

hardScene::~hardScene()
{
    delete this->background;
}



void hardScene::leave()
{
    emit toTitle();
}
