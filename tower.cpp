#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(42, 42);

Tower::Tower(QPoint pos, MainWindow *game, const QPixmap &sprite, int attackRange, int damage, int fireRate, int level)
    : m_attacking(false)
	, m_rotationSprite(0.0)
    , m_chooseEnemy(nullptr)
    , m_game(game)
    , m_attackRange(attackRange)
    , m_damage(damage)
    , m_fireRate(fireRate)
    , m_level(level)
    , m_pos(pos)
    , m_sprite(sprite)
{
	m_fireRateTimer = new QTimer(this);
	connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
	delete m_fireRateTimer;
    m_fireRateTimer = nullptr;
}

void Tower::checkEnemyInRange()
{
	if (m_chooseEnemy)
	{
		// 这种情况下,需要旋转炮台对准敌人
		// 向量标准化
		QVector2D normalized(m_chooseEnemy->pos() - m_pos);
		normalized.normalize();
		m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

		// 如果敌人脱离攻击范围
		if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
			lostSightOfEnemy();
	}
	else
	{
		// 遍历敌人,看是否有敌人在攻击范围内
		QList<Enemy *> enemyList = m_game->enemyList();
		foreach (Enemy *enemy, enemyList)
		{
			if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
			{
				chooseEnemyForAttack(enemy);
				break;
			}
		}
	}
}

void Tower::draw(QPainter *painter) const
{
    painter->save(); //保存当前画笔状态
    painter->setPen(Qt::white); //颜色【可改】
	// 绘制攻击范围
	painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

	// 绘制偏转坐标,由中心+偏移=左上
	static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
	// 绘制炮塔并选择炮塔
    painter->translate(m_pos); //这里将坐标原点移到m_pos
	painter->rotate(m_rotationSprite);
	painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore(); //恢复画笔状态
}

void Tower::attackEnemy()
{
    //启动打炮模式
	m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    //选择敌人，同时设置对敌人开火
	m_chooseEnemy = enemy;
    //启动timer，开始打炮
	attackEnemy();
    //敌人自己要关联一个攻击者，这个用QList管理攻击者，因为可能有多个
	m_chooseEnemy->getAttacked(this);
}


void Tower::targetKilled()
{
	if (m_chooseEnemy)
        m_chooseEnemy = nullptr;

    //停止计时器
	m_fireRateTimer->stop();
	m_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{
	m_chooseEnemy->gotLostSight(this);
	if (m_chooseEnemy)
        m_chooseEnemy = nullptr;

	m_fireRateTimer->stop();
	m_rotationSprite = 0.0;
}

void Tower::levelup()
{

}

NormalTower::NormalTower(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

NormalTower::~NormalTower()
{

}


void NormalTower::shootWeapon()
{
    Bullet *bullet = new NormalBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void NormalTower::levelup()
{

}

FireTower::FireTower(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

FireTower::~FireTower()
{

}

void FireTower::shootWeapon()
{
    Bullet *bullet = new FireBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, fireattack);
    bullet->move();
    m_game->addBullet(bullet);
}

void FireTower::levelup()
{

}

IceTower::IceTower(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

IceTower::~IceTower()
{

}

void IceTower::levelup()
{

}

void IceTower::shootWeapon()
{
    Bullet *bullet = new IceBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, slowspeed);
    bullet->move();
    m_game->addBullet(bullet);
}

LaserTower::LaserTower(QPoint pos, MainWindow *game, const QPixmap &sprite)
: Tower(pos, game, sprite)
{

}

LaserTower::~LaserTower()
{

}

void LaserTower::levelup()
{

}

void LaserTower::shootWeapon()
{
    Bullet *bullet = new LaserBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}
