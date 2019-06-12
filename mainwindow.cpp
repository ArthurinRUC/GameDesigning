#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "audioplayer.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>

#include "tscene.h"

static const int TowerCost = 300;
//static const QString s_curDir = "C:/Users/81915/Desktop/LS/Programming/GD/GameDesigning/music";

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
    , scene(nullptr)
	, ui(new Ui::MainWindow)
	, m_waves(0)
	, m_playerHp(5)
	, m_playrGold(1000)
	, m_gameEnded(false)
    , m_gameWin(false)

{
    //此处开始构造MainWindow
	ui->setupUi(this);

    this->setWindowIcon(QIcon(":/image/logo.jpg"));
    this->setWindowTitle("Tower Defense");
    this->setMouseTracking(true);                //track mouse when mouse isn`t pressed
    this->setFixedSize(800, 600);
    startscreen = new tStartScreen(this);
    connect(this->startscreen, SIGNAL(toTitle()), this, SLOT(back()));
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::back()
{
    this->setFixedSize(800, 600);
    if (scene)
    {
        delete scene;
        scene = nullptr;
    }
    if (startscreen)
    {
        delete startscreen;
        startscreen = nullptr;
    }
    startscene = new tStartScene(this);
    connect(this->startscene, SIGNAL(toEasy()), this, SLOT(startEasy()));
    connect(this->startscene, SIGNAL(toHard()), this, SLOT(startHard()));
}

void MainWindow::startEasy()
{
    this->setFixedSize(800, 600);
    if (startscene)
    {
        delete startscene;
        startscene = nullptr;
    }
    //remember to delete !!!
    scene = new easyScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}

void MainWindow::startHard()
{
    this->setFixedSize(800, 600);
    if (startscene)
    {
        delete startscene;
        startscene = nullptr;
    }
    scene = new hardScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}














