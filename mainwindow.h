#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "tscene.h"

namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    explicit MainWindow(QWidget *parent = nullptr);
    tScene* scene;
	~MainWindow();


    //以下为原有游戏代码
	void getHpDamage(int damage = 1);
	void removedEnemy(Enemy *enemy);
	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
	void awardGold(int gold);

	AudioPlayer* audioPlayer() const;
	QList<Enemy *> enemyList() const;

protected:
    //void paintEvent(QPaintEvent *);
    //void mousePressEvent(QMouseEvent *); //√

public slots:
    void back();    // 来到主界面
    void startEasy();
    void startHard();

    //void updateMap(); //原来的槽
    //void gameStart(); //原来的槽

private:
    void loadTowerPositions(); //√
	void addWayPoints();
	bool loadWave();
    bool canBuyTower() const; //√
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
    void preLoadWavesInfo();

private:
	Ui::MainWindow *		ui;
	int						m_waves;
	int						m_playerHp;
	int						m_playrGold;
	bool					m_gameEnded;
	bool					m_gameWin;
	AudioPlayer *			m_audioPlayer;
	QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    QList<Tower *>			m_towersList; //√
	QList<WayPoint *>		m_wayPointsList;
	QList<Enemy *>			m_enemyList;
	QList<Bullet *>			m_bulletList;
};

#endif // MAINWINDOW_H
