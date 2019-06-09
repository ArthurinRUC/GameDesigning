#ifndef TSCENE_H
#define TSCENE_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QKeyEvent>
#include <waypoint.h>
#include <enemy.h>
#include <tower.h>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtDebug>

#include "bullet.h"
#include "audioplayer.h"
#include "towerposition.h"
#include "plistreader.h"

class Bullet;

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

    QLabel* Base = new QLabel(this);
    QMovie* base = new QMovie(":/image/base0.png");

    // move to base class
    void addBullet(Bullet *bullet);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    QList<Enemy *> enemyList() const;
    void awardGold(int gold);
    void getHpDamage(int damage);
    void doGameOver();

    QList<Bullet *>			m_bulletList;
    QList<Enemy *>			m_enemyList;
    QList<Tower *>			m_towersList;
    int						m_waves;
    bool					m_gameEnded;
    bool					m_gameWin;
    int						m_playerHp;
    int						m_playerGold;
    AudioPlayer *		    m_audioPlayer;


    //QMovie* loseScene = new QMovie(":/background/victory1.jpg");

signals:
    void toTitle(); //返回信号，返回主界面
    void toEasy();
    void toHard();


public slots:
    void FireIceattack();
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
    QMovie* easy = new QMovie(":/GameMap/EasyMap13.jpg");
    QMovie* hard = new QMovie(":/GameMap/HardMap12.jpg");
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

    //增加代码 6-6
    //void getHpDamage(int damage = 1);
   // void removedEnemy(Enemy *enemy);
    //void removedBullet(Bullet *bullet);
    //void addBullet(Bullet *bullet);
    //void awardGold(int gold);

    AudioPlayer* audioPlayer() const;
    //QList<Enemy *> enemyList() const;

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);

    //增加代码 6-6
    void mousePressEvent(QMouseEvent *);

private:
    QMovie* background = new QMovie(":/GameMap/easyMap2.jpg");
    QPushButton* exit = new QPushButton(this);



    QMovie* station = new QMovie("/image/open_spot.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* btn3 = new QLabel(this);
    QLabel* btn4 = new QLabel(this);
    QLabel* btn5 = new QLabel(this);
    QLabel* btn6 = new QLabel(this);
    QLabel* btn7 = new QLabel(this);
    QLabel* btn8 = new QLabel(this);
    QLabel* btn9 = new QLabel(this);
    QLabel* btn10 = new QLabel(this);
    QLabel* btn11 = new QLabel(this);
    QLabel* btn12 = new QLabel(this);
    QLabel* btn13 = new QLabel(this);

    //QPoint cell;
    void uiSetup();

    //增加代码 6-6
private:
    void loadTowerPositions(); //√
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const; //√
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    //void doGameOver();
    void preLoadWavesInfo();



private:
    //MainWindow *		ui;
    //int						m_waves;
    //int						m_playerHp;
    //int						m_playerGold;
    //bool					m_gameEnded;
    //bool					m_gameWin;
    //AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    //QList<Tower *>			m_towersList; //√
    QList<WayPoint *>		m_wayPointsList;
    //QList<Enemy *>			m_enemyList;
    //QList<Bullet *>			m_bulletList;


private slots:
    void onTimer();
    void leave(); // emit toTitle();

    //增加代码 6-6
    void back();
    //void startEasy();
    //void startHard();

    void updateMap(); //原来的槽
    void gameStart(); //原来的槽

};


class hardScene : public tScene
{
    Q_OBJECT
public:
    explicit hardScene(QWidget* parent = 0);
    ~hardScene();

    //增加代码 6-6
    //void getHpDamage(int damage = 1);
   // void removedEnemy(Enemy *enemy);
    //void removedBullet(Bullet *bullet);
    //void addBullet(Bullet *bullet);
    //void awardGold(int gold);

    AudioPlayer* audioPlayer() const;
    //QList<Enemy *> enemyList() const;

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);

    //增加代码 6-6
    void mousePressEvent(QMouseEvent *);

private:
    QMovie* background = new QMovie(":/GameMap/hardMap2.jpg");
    QPushButton* exit = new QPushButton(this);

    QMovie* station = new QMovie("/image/open_spot.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* btn3 = new QLabel(this);
    QLabel* btn4 = new QLabel(this);
    QLabel* btn5 = new QLabel(this);
    QLabel* btn6 = new QLabel(this);
    QLabel* btn7 = new QLabel(this);
    QLabel* btn8 = new QLabel(this);
    QLabel* btn9 = new QLabel(this);
    QLabel* btn10 = new QLabel(this);
    QLabel* btn11= new QLabel(this);
    QLabel* btn12 = new QLabel(this);
    QLabel* btn13= new QLabel(this);
    QLabel* btn14 = new QLabel(this);

    //QPoint cell;
    void uiSetup(); //在PVZ中用来设计僵尸的出现等

private:
    void loadTowerPositions(); //√
    //for different enemies
    void addNormalWayPoints();
    void addIceWayPoints();
    void addFireWayPoints();
    void addFastWayPoints();
    void addBossWayPoints();

    bool loadWave();
    bool canBuyTower() const; //√
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    //void doGameOver();
    void preLoadWavesInfo();

private:
    //MainWindow *		ui;
    //int						m_waves;
    //int						m_playerHp;
    //int						m_playerGold;
    //bool					m_gameEnded;
    //bool					m_gameWin;
    //AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    //QList<Tower *>			m_towersList; //√
    //QList<WayPoint *>		m_wayPointsList;
    //for different enemies
    QList<WayPoint *>       normalWayPointsList;
    QList<WayPoint *>		iceWayPointsList;
    QList<WayPoint *>		fireWayPointsList;
    QList<WayPoint *>		fastWayPointsList;
    QList<WayPoint *>		bossWayPointsList;
    //QList<Enemy *>			m_enemyList;
    //QList<Bullet *>			m_bulletList;

private slots:
    void onTimer();
    void leave(); // emit toTitle();

    //增加代码 6-6
    void back();
    //void startEasy();
    //void startHard();

    void updateMap(); //原来的槽
    void gameStart(); //原来的槽
};

#endif // TSCENE_H
