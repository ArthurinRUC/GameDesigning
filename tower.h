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
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"), int attackRange = 70, int damage = 10, int fireRate = 1000, int level = 1);
	~Tower();

	void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
    //void removeBullet();
	void damageEnemy();
	void lostSightOfEnemy();

    //炮塔升级
    virtual void levelup() = 0;

protected slots:
    //不同派生类（不同塔）需要发射不同子弹，需要虚函数
    virtual void shootWeapon() = 0;

protected:
	bool			m_attacking;
	qreal			m_rotationSprite;

	Enemy *			m_chooseEnemy;
	MainWindow *	m_game;
	QTimer *		m_fireRateTimer;

    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    int             m_level;        //等级

    const QPoint	m_pos; //塔的圆心
    const QPixmap	m_sprite;

	static const QSize ms_fixedSize;
};

class NormalTower: public Tower
{
public:
    NormalTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"));
    ~NormalTower();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

class FireTower : public Tower
{
public:
    FireTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/firetower.png"));
    ~FireTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int fireattack; //每秒的灼烧伤害
};

class IceTower : public Tower
{
public:
    IceTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/icetower.png"));
    ~IceTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int slowspeed; //减慢速度百分比
};

class LaserTower : public Tower
{
public:
    LaserTower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/lasertower.png"));
    ~LaserTower();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

#endif // TOWER_H
