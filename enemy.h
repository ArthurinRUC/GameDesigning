#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include<tscene.h>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class easyScene;
class tScene;

class Enemy : public QObject
{
	Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, tScene *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
	~Enemy();

	void draw(QPainter *painter) const;
	void move();
	void getDamage(int damage);
	void getRemoved();
	void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
	QPoint pos() const;

public slots:
	void doActivate();

private:
	bool			m_active;
	int				m_maxHp;
	int				m_currentHp;
	qreal			m_walkingSpeed;
	qreal			m_rotationSprite;

	QPoint			m_pos;
	WayPoint *		m_destinationWayPoint;
    tScene *        m_game;
	QList<Tower *>	m_attackedTowersList;

	const QPixmap	m_sprite;
	static const QSize ms_fixedSize;
};

#endif // ENEMY_H
