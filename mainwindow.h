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
class Enemy1;
class Enemy2;
class Bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
    explicit MainWindow(QWidget *parent = nullptr);
    tScene* scene;
    tStartScene* startscene;
    tStartScreen* startscreen;
	~MainWindow();

	AudioPlayer* audioPlayer() const;

public slots:
    void back();    // 来到主界面
    void startEasy();
    void startHard();

private:
	Ui::MainWindow *		ui;
	int						m_waves;
	int						m_playerHp;
	int						m_playrGold;
	bool					m_gameEnded;
	bool					m_gameWin;
};

#endif // MAINWINDOW_H
