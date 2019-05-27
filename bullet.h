#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class Enemy1;
class Enemy2;
class MainWindow;

class Bullet : public QObject
{
	Q_OBJECT
    //Qt动画效果
	Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/bullet.png"));

	void draw(QPainter *painter) const;
	void move();
	void setCurrentPos(QPoint pos);
	QPoint currentPos() const;

protected slots:
	void hitTarget();

protected:
	const QPoint	m_startPos;
	const QPoint	m_targetPos;
	const QPixmap	m_sprite;
	QPoint			m_currentPos;
	Enemy *			m_target;
	MainWindow *	m_game;
	int				m_damage;

	static const QSize ms_fixedSize;
};

class NormalBullet: public Bullet
{
    Q_OBJECT

public:
    NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/bullet.png"));
};

class FireBullet: public Bullet
{
    Q_OBJECT

public:
    FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, int fireattack, const QPixmap &sprite = QPixmap(":/image/firebullet.png"));

private:
    int fire_attack;
};

class IceBullet: public Bullet
{
    Q_OBJECT

public:
    IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, int slowspeed, const QPixmap &sprite = QPixmap(":/image/icebullet.png"));

private:
    int slow_speed;
};

class LaserBullet: public Bullet
{
    Q_OBJECT

public:
    LaserBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/laserbullet.png"));

};

#endif // BULLET_H
