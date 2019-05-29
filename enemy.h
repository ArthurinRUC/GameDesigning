#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "bullet.h"

class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject{
	Q_OBJECT
public:
	Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
    virtual ~Enemy();
	void draw(QPainter *painter) const;
	void move();
    void getDamage(Bullet *bullet);
	void getRemoved();
    void canRemove();
    void getFireDamage(int damage);
	void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
    QPoint pos() const;

    int             fire; //受到火焰伤害？
    int             fireattack; //每0.5秒钟受到多少火焰伤害
    int             ice; //受到减速？
    qreal           m_normalSpeed; //正常速度
    qreal           m_slowSpeed; //寒冰状态的速度
    //private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
public slots:
	void doActivate();
};

class Enemy1:public Enemy{
    Q_OBJECT
public:
    Enemy1(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy1.png"));
    //void getDamage(int damage);
};

class Enemy2:public Enemy{
    Q_OBJECT
public:
    Enemy2(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy2.png"));
    //void getDamage(int damage);
};

#endif // ENEMY_H
