#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

//血条长度
static const int Health_Bar_Width = 20;
const QSize Enemy::ms_fixedSize(52, 52);
Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/enemy.png")*/)
	: QObject(0)
	, m_active(false)//决定painter是否显示enemy对象，不可通过m_active设置enemy暂停移动
	, m_maxHp(40)
	, m_currentHp(40)
	, m_walkingSpeed(1.0)//可以通过将m_walkingSpeed置0达到暂停移动的效果
	, m_rotationSprite(0.0)
	, m_pos(startWayPoint->pos())
	, m_destinationWayPoint(startWayPoint->nextWayPoint())
	, m_game(game)
	, m_sprite(sprite)
{}
Enemy::~Enemy(){
	m_attackedTowersList.clear();
	m_destinationWayPoint = NULL;
	m_game = NULL;
}
void Enemy::doActivate(){
	m_active = true;
}
void Enemy::move(){
	if (!m_active)
		return;
	if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1)){
		// 敌人抵达了一个航点
		if (m_destinationWayPoint->nextWayPoint()){
			// 还有下一个航点
			m_pos = m_destinationWayPoint->pos();
			m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
		}
		else{
			// 表示进入基地
			m_game->getHpDamage();//修改，减少生命数与敌人类型相关？？？
			m_game->removedEnemy(this);
            return;
		}
	}
	// 还在前往航点的路上
	// 目标航点的坐标
	QPoint targetPoint = m_destinationWayPoint->pos();
	// 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

	// 向量标准化
	qreal movementSpeed = m_walkingSpeed;
	QVector2D normalized(targetPoint - m_pos);
	normalized.normalize();
	m_pos = m_pos + normalized.toPoint() * movementSpeed;

	// 确定敌人选择方向
	// 默认图片向左,需要修正180度转右
	m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}
void Enemy::draw(QPainter *painter) const{
	if (!m_active)//！！！
		return;

	painter->save();

    //m_pos仍然是中心位置
	QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
	// 绘制血条
    //其实就是两个方框，红色方框代表总生命，固定大小不变
    //绿色方框代表当前生命，受m_currentHp / m_maxHp的变化影响
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
	painter->drawRect(healthBarBackRect);

	painter->setBrush(Qt::green);
	QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
	painter->drawRect(healthBarRect);

	// 绘制偏转坐标,由中心+偏移=左上
	static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos); //这里将坐标原点移到m_pos
	painter->rotate(m_rotationSprite);
	// 绘制敌人
	painter->drawPixmap(offsetPoint, m_sprite);

	painter->restore();
}
void Enemy::getRemoved(){
	if (m_attackedTowersList.empty())
		return;

	foreach (Tower *attacker, m_attackedTowersList)
		attacker->targetKilled();
	// 通知game,此敌人已经阵亡
	m_game->removedEnemy(this);
}
void Enemy::getDamage(int bulletKind){
	m_game->audioPlayer()->playSound(LaserShootSound);//日后是否需要实现不同子弹击中敌人音效不同？？？
	
    switch(bulletKind){
    case 0://NormalBullet
        m_currentHp -= 10;//注意未来需要与子弹和塔契合
        break;
    case 1://FireBullet
        m_currentHp -= 8;
        //2个计时器？？？一个用于持续减血，QTimer，connect，（每隔一段时间减一定血 专为火球设计减血函数（考虑减血时长未截止敌人就死亡的情况
                        //一个用于喊停减血过程（即停止上述计时器的执行
        break;
    case 2://IceBullet
        m_currentHp -= 8;
        m_walkingSpeed /= 2.0;
        //计时器恢复原速度QTimer singleshot
        break;
    case 3://LaserBullet
        m_currentHp -= 20;//其他效果？？？
        break;
    }
    

	// 阵亡,需要移除
    //此处是否需要单独设为一函数，方便实现FireBullet持续减血的效果？？？
	if (m_currentHp <= 0){
		m_game->audioPlayer()->playSound(EnemyDestorySound);
		m_game->awardGold(200);//奖金数额与敌人类型相关？？？
		getRemoved();
	}
}
void Enemy::getAttacked(Tower *attacker){
	m_attackedTowersList.push_back(attacker);
}
// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker){
	m_attackedTowersList.removeOne(attacker);
}
QPoint Enemy::pos() const{
	return m_pos;
}

Enemy1::Enemy1(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy1.png")*/)
{
    this->m_active=false;
    this->m_maxHp=40;
    this->m_currentHp=40;
    this->m_walkingSpeed=1.0;
    this->m_rotationSprite=0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}
void Enemy1::getDamage(int damage){
    m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;
    if (m_currentHp <= 0){//敌人阵亡,需要移除
        m_game->audioPlayer()->playSound(EnemyDestorySound);
        m_game->awardGold(200);//奖励金钱
        getRemoved();
    }
}

Enemy2::Enemy2(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/enemy2.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap(":/image/enemy2.png")*/)
{
    this->m_active=false;
    this->m_maxHp=80;
    this->m_currentHp=80;
    this->m_walkingSpeed=2.0;
    this->m_rotationSprite=0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}
void Enemy2::getDamage(int damage){
    m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;
    if (m_currentHp <= 0){//敌人阵亡,需要移除
        m_game->audioPlayer()->playSound(EnemyDestorySound);
        m_game->awardGold(400);//奖励金钱
        getRemoved();
    }
}
