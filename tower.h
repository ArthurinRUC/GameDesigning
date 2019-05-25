#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
	Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"), int attackRange = 70, int damage = 10, int fireRate = 1000);
	~Tower();

	void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
    //void removeBullet();
	void damageEnemy();
	void lostSightOfEnemy();

private slots:
    //不同派生类（不同塔）需要发射不同子弹，需要虚函数
    /*virtual*/ void shootWeapon();

private:
	bool			m_attacking;
	qreal			m_rotationSprite;

	Enemy *			m_chooseEnemy;
	MainWindow *	m_game;
	QTimer *		m_fireRateTimer;

    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔

    const QPoint	m_pos; //塔的圆心
    const QPixmap	m_sprite;

	static const QSize ms_fixedSize;
};

class NormalTower: public Tower
{
public:
    NormalTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"));
    ~NormalTower();

};

class FireTower : public Tower
{
public:
    FireTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/firetower.png"));
    ~FireTower();
};

class IceTower : public Tower
{
public:
    IceTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/icetower.png"));
    ~IceTower();
};

class LaserTower : public Tower
{
public:
    LaserTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/lasertower.png"));
    ~LaserTower();
};

#endif // TOWER_H
