#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include"tscene.h"

class QPainter;
class Enemy;
class MainWindow;
class QTimer;
class tScene;

class Tower : QObject
{
	Q_OBJECT
public:
    Tower(QPoint pos, tScene *game, const QPixmap &sprite = QPixmap(":/image/tower.png"));
	~Tower();

	void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
	void removeBullet();
	void damageEnemy();
	void lostSightOfEnemy();

private slots:
	void shootWeapon();

private:
	bool			m_attacking;
	int				m_attackRange;	// 代表塔可以攻击到敌人的距离
	int				m_damage;		// 代表攻击敌人时造成的伤害
	int				m_fireRate;		// 代表再次攻击敌人的时间间隔
	qreal			m_rotationSprite;

	Enemy *			m_chooseEnemy;
    tScene *        m_game;
	QTimer *		m_fireRateTimer;

    //必备三件套~
    const QPoint	m_pos; //塔的圆心
	const QPixmap	m_sprite;

	static const QSize ms_fixedSize;
};

#endif // TOWER_H
