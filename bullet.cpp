#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
			   MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/bullet.png")*/)
	: m_startPos(startPos)
	, m_targetPos(targetPoint)
	, m_sprite(sprite)
	, m_currentPos(startPos)
	, m_target(target)
	, m_game(game)
	, m_damage(damage)
{}

void Bullet::draw(QPainter *painter) const{
	painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet::move(){
	// 100毫秒内击中敌人
	static const int duration = 100;
    //不同子弹移动速度可以不同，后期可以将Bullet中的move也设为虚函数，在具体子类中实现（LaserBullet移动速度最快.etc）
	QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
	animation->setDuration(duration);
	animation->setStartValue(m_startPos);
	animation->setEndValue(m_targetPos);
	connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

	animation->start();
}

void Bullet::hitTarget(){
	// 这样处理的原因是:
	// 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
	// 后续炮弹再攻击到的敌人就是无效内存区域
	// 因此先判断下敌人是否还有效
	if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(0);
   //将m_damage替换为表示子弹类型的变量m_kind，是否需要添加表示炮塔等级的变量？（高级炮塔所发射的子弹杀伤力更强
	m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos){
	m_currentPos = pos;
}

QPoint Bullet::currentPos() const{
	return m_currentPos;
}

NormalBullet::NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, sprite)
{

}

FireBullet::FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, int fireattack, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, sprite), fire_attack(fireattack)
{

}

IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, int slowspeed, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, sprite), slow_speed(slowspeed)
{

}

LaserBullet::LaserBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, MainWindow *game, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, sprite)
{

}
