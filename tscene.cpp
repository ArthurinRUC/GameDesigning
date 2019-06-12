#include "tscene.h"
#include <QMediaPlayer>
#include"tcard.h"

static const int TowerCost = 300;
//static const QString s_curDir = "C:/Users/81915/Desktop/LS/Programming/GD/GameDesigning/music";

tScene::tScene(QWidget *parent) : QLabel(parent)
  , m_waves(0)
  , m_gameEnded(false)
  , m_gameWin(false)
  , m_playerHp(5)
  , m_playerGold(1000)
{
    this->setMouseTracking(true);
    this->grabKeyboard();
}

tScene::~tScene()
{
    if (!(this->MoneyFront == nullptr)) delete this->MoneyFront;
    if (!(this->MoneyBar == nullptr)) delete this->MoneyBar;
    if (!(this->moneybar == nullptr))delete this->moneybar;
    if (!(this->MoneyLabel == nullptr)) delete this->MoneyLabel;
    if (!(this->moneylabel == nullptr)) delete this->moneylabel;

    if (!(this->LifeFront == nullptr))delete this->LifeFront;
    if (!(this->LifeBar == nullptr)) delete this->LifeBar;
    if (!(this->lifebar == nullptr)) delete this->lifebar;
    if (!(this->LifeLabel == nullptr))delete this->LifeLabel;
    if (!(this->lifelabel == nullptr)) delete this->lifelabel;

    if (!(this->WaveFront == nullptr)) delete this->WaveFront;
    if (!(this->WaveBar == nullptr))delete this->WaveBar;
    if (!(this->wavebar == nullptr)) delete this->wavebar;
    if (!(this->WaveLabel == nullptr)) delete this->WaveLabel;
    if (!(this->wavelabel == nullptr))delete this->wavelabel;

    if (!(this->LevelUp == nullptr)) delete this->LevelUp;
    if (!(this->levelup == nullptr)) delete this->levelup;

    if (!(this->LevelFront == nullptr)) delete this->LevelFront;
    if (!(this->levelbar == nullptr)) delete this->levelbar;
    if (!(this->LevelBar == nullptr)) delete this->LevelBar;

    if (!(this->Upgrade_MoneyFront == nullptr))delete this->Upgrade_MoneyFront;
    if (!(this->upgrade_moneybar == nullptr))delete this->upgrade_moneybar;
    if (!(this->Upgrade_MoneyBar == nullptr))delete this->Upgrade_MoneyBar;

    delete Base;
    delete base;

    delete NormalTowerPic;
    delete normalTowerPic;
    delete FireTowerPic;
    delete fireTowerPic;
    delete IceTowerPic;
    delete iceTowerPic;
    delete LaserTowerPic;
    delete laserTowerPic;

    delete currentCard;

}

void tScene::mouseMoveEvent(QMouseEvent *event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}

void tScene::getHpDamage(int damage)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}


void tScene::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void tScene::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void tScene::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}

AudioPlayer *tScene::audioPlayer() const
{
    return m_audioPlayer;
}

void tScene::FireIceattack()
{
    foreach(Enemy *enemy, m_enemyList){
        if (enemy->fire != 0){
            enemy->fire--;
            enemy->getFireDamage(enemy->fireattack);
        }
        if(enemy->ice != 0){
            enemy->ice--;
            if (enemy->ice == 0)
            {
                enemy->m_walkingSpeed = enemy->m_normalSpeed;
                enemy->m_slowSpeed = enemy->m_normalSpeed;
            }
            else
            {
                enemy->m_walkingSpeed = enemy->m_slowSpeed;
            }
        }
    }
}

void tScene::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

        m_audioPlayer->stopBGM();
        m_audioPlayer->playLoseSound();
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

QList<Enemy *> tScene::enemyList() const
{
    return m_enemyList;
}

tStartScreen::tStartScreen(QWidget* parent): QLabel(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/First Page.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
    this->setMouseTracking(true);
    this->grabKeyboard();
    this->setGeometry(0, 0, 800, 600); //界面
    this->setMovie(this->background);  //图片
    this->background->start();      //
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(255,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

tStartScreen::~tStartScreen()
{
    delete this->background;
    delete this->front;
}

void tStartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}

tStartScene::tStartScene(QWidget* parent):QLabel(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/First Page.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
    this->setMouseTracking(true);
    this->grabKeyboard();


    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn2->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn1->setMovie(easy);
    easy->start();
    btn2->setMovie(hard);
    hard->start();
    btn1->setGeometry(120, 205, 180, 180);
    btn2->setGeometry(500, 205, 180, 180);
    btn1->show();
    btn2->show();
    title->setText("choose a level");
    title->setGeometry(250, 0, 300, 100);
    title->setFont(QFont("Consolas", 18));
    title->show();

    QString str1="Easy Map";
    QString str2="Hard Map";
    easyStr->setGeometry(150, 400, 300, 100);
    hardStr->setGeometry(530,400,300,100);
    easyStr->setText(str1);
    hardStr->setText(str2);
    easyStr->setFont(QFont("Consolas", 14));
    hardStr->setFont(QFont("Consolas", 14));
    easyStr->show();
    hardStr->show();
}

tStartScene::~tStartScene()
{
    delete this->background;
    delete this->easy;
    delete this->hard;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
    delete this->easyStr;
    delete this->hardStr;
}

void tStartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(120, 205, 180, 180).contains(event->pos()))
    {
        emit toEasy();
    }
    if (QRect(500, 205, 180, 180).contains(event->pos()))
    {
        emit toHard();
    }
}

easyScene::easyScene(QWidget* parent)
    : tScene(parent)
  //, ui(new Ui::MainWindow)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/easy.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    //m_audioPlayer->getMusic()->setVolume(30);
    m_audioPlayer->startBGM();

    this->setGeometry(0, 0, 800, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    loadTowerPositions(); //调用位置函数
    addWayPoints();

    //m_audioPlayer = new AudioPlayer(this);
    //m_audioPlayer->startBGM();

    //每100ms更新一次灼烧状态
    QTimer *Firetime = new QTimer(this);
    connect(Firetime, SIGNAL(timeout()), this, SLOT(FireIceattack()));
    Firetime->start(100);

    //每30ms发送一个更新信号
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    this->uiSetup();
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

void easyScene::uiSetup()
{
    MoneyBar->setGeometry(120, 400, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(10, 480, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();  
    MoneyLabel->setGeometry(60, 400, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(400, 400, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(290, 480, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(340, 400, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);

    WaveBar->setGeometry(680, 400, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(570, 480, 300, 200);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(615, 400, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    Base->setGeometry(685, 35, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);
    Base->raise();

    LevelUp->setGeometry(100, 410, 50, 50);
    levelup->start();
    LevelUp->show();
    LevelUp->setMovie(levelup);
    LevelUp->raise();

    LevelBar->setGeometry(10, 340, 300, 200);
    levelbar->start();
    LevelBar->show();
    LevelBar->setMovie(levelbar);
    LevelBar->raise();
    LevelFront->setGeometry(-100, 420, 300, 200);
    LevelFront->setFont(QFont("Calibri", 16));
    LevelFront->setText("5");
    LevelFront->setAlignment(Qt::AlignHCenter);
    LevelFront->show();
    LevelFront->raise();

    Upgrade_MoneyBar->setGeometry(170, 340, 300, 200);
    upgrade_moneybar->start();
    Upgrade_MoneyBar->show();
    Upgrade_MoneyBar->setMovie(upgrade_moneybar);
    Upgrade_MoneyBar->raise();

    Upgrade_MoneyFront->setGeometry(60, 420, 300, 200);
    Upgrade_MoneyFront->setFont(QFont("Calibri", 16));
    Upgrade_MoneyFront->setText("100");
    Upgrade_MoneyFront->setAlignment(Qt::AlignHCenter);
    Upgrade_MoneyFront->show();
    Upgrade_MoneyFront->raise();//记得delete！！！

    btn1->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn1->setMovie(station);
    station->start();
    btn1->setGeometry(50, 220, 60, 60);
    btn1->show();
    btn1->raise();

    btn2->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn2->setMovie(station);
    station->start();
    btn2->setGeometry(50, 145, 60, 60);
    btn2->show();
    btn2->raise();

    btn3->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn3->setMovie(station);
    station->start();
    btn3->setGeometry(120, 70, 60, 60);
    btn3->show();
    btn3->raise();

    btn4->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn4->setMovie(station);
    station->start();
    btn4->setGeometry(205, 235, 60, 60);
    btn4->show();
    btn4->raise();

    btn5->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn5->setMovie(station);
    station->start();
    btn5->setGeometry(305, 235, 60, 60);
    btn5->show();
    btn5->raise();

    btn6->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn6->setMovie(station);
    station->start();
    btn6->setGeometry(205, 315, 60, 60);
    btn6->show();
    btn6->raise();

    btn7->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn7->setMovie(station);
    station->start();
    btn7->setGeometry(305, 315, 60, 60);
    btn7->show();
    btn7->raise();

    btn8->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn8->setMovie(station);
    station->start();
    btn8->setGeometry(460, 125, 60, 60);
    btn8->show();
    btn8->raise();

    btn9->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn9->setMovie(station);
    station->start();
    btn9->setGeometry(460, 200, 60, 60);
    btn9->show();
    btn9->raise();

    btn10->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn10->setMovie(station);
    station->start();
    btn10->setGeometry(540, 200, 60, 60);
    btn10->show();
    btn10->raise();

    btn11->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn11->setMovie(station);
    station->start();
    btn11->setGeometry(400, 385, 60, 60);
    btn11->show();
    btn11->raise();

    btn12->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn12->setMovie(station);
    station->start();
    btn12->setGeometry(480, 385, 60, 60);
    btn12->show();
    btn12->raise();

    btn13->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn13->setMovie(station);
    station->start();
    btn13->setGeometry(620, 90, 60, 60);
    btn13->show();
    btn13->raise();

    exit->setGeometry(700, 0, 60, 60); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

    NormalTowerPic->setGeometry(180, 10, 100, 60);
    normalTowerPic->start();
    NormalTowerPic->show();
    NormalTowerPic->setMovie(normalTowerPic);

    FireTowerPic->setGeometry(280, 10 , 100, 60);
    fireTowerPic->start();
    FireTowerPic->show();
    FireTowerPic->setMovie(fireTowerPic);

    IceTowerPic->setGeometry(430, 10 , 100, 60);
    iceTowerPic->start();
    IceTowerPic->show();
    IceTowerPic->setMovie(iceTowerPic);

    LaserTowerPic->setGeometry(530, 10 , 100, 60);
    laserTowerPic->start();
    LaserTowerPic->show();
    LaserTowerPic->setMovie(laserTowerPic);

    tCard *card0 = new tNormalTowerCard(this);
    card0->setGeometry(180, 10 , 100, 60);
    Cards.append(card0);
    card0->show();

    Front1 = new QLabel(this);
    Front1->setText("100");
    Front1->setGeometry(225, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front1->setFont(QFont("Calibri", 11));
    Front1->show();
    Front1->raise();

    tCard *card1 = new tFireTowerCard(this);
    card1->setGeometry(280, 10 , 100, 60);
    Cards.append(card1);
    card1->show();

    Front2 = new QLabel(this);
    Front2->setText("150");
    Front2->setGeometry(325, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front2->setFont(QFont("Calibri", 11));
    Front2->show();
    Front2->raise();

    tCard *card2 = new tIceTowerCard(this);
    card2->setGeometry(430, 10 , 100, 60);
    Cards.append(card2);
    card2->show();

    Front3 = new QLabel(this);
    Front3->setText("150");
    Front3->setGeometry(475, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front3->setFont(QFont("Calibri", 11));
    Front3->show();
    Front3->raise();

    tCard *card3 = new tLaserTowerCard(this);
    card3->setGeometry(530, 10 , 100, 60);
    Cards.append(card3);
    card3->show();

    Front4 = new QLabel(this);
    Front4->setText("200");
    Front4->setGeometry(575, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front4->setFont(QFont("Calibri", 11));
    Front4->show();
    Front4->raise();

}

void easyScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
        m_gameWin = true;
        m_audioPlayer->stopBGM();
        m_audioPlayer->playWinSound();
        // 游戏胜利转到游戏胜利场景
        // 这里暂时以打印处理
        }
    }
}


void easyScene::loadTowerPositions()
{
    //读取文件中的炮塔位置信息，可以不用深究，但是可以修改位置【可改】

    //这里可以改变炮塔的位置，文件是html格式
    QFile file(":/config/easyTowersPosition.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    QList<QVariant> array = reader.data();
    foreach (QVariant dict, array)
    {
        QMap<QString, QVariant> point = dict.toMap();
        int x = point.value("x").toInt();
        int y = point.value("y").toInt();
        m_towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
}

void easyScene::addWayPoints()
{
    //敌人航点【可改】
    WayPoint *wayPoint1 = new WayPoint(QPoint(775, 215));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(645, 215));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(645, 335));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(410, 335));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(410, 185));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(150, 185));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(150, 350));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0, 350));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);
}

bool easyScene::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new normalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new iceEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new fireEnemy(startWayPoint, this);
            break;
        case 3:
            enemy=new fastEnemy(startWayPoint, this);
            break;
        case 4:
            enemy=new bossEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

bool easyScene::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void easyScene::drawWave()
{
    WaveFront->setText(QString("%1").arg(m_waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}

void easyScene::drawHP()
{
    LifeFront->setText(QString("%1").arg(m_playerHp));
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
}

void easyScene::drawPlayerGold()
{
    MoneyFront->setText(QString("%1").arg(m_playerGold));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
}


void easyScene::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

easyScene::~easyScene()
{
    delete this->background;
    delete this->exit;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
    delete this->btn5;
    delete this->btn6;
    delete this->btn7;
    delete this->btn8;
    delete this->btn9;
    delete this->btn10;
    delete this->btn11;
    delete this->btn12;
    delete this->btn13;

    foreach (const Tower *tower, m_towersList)
        delete tower;

    delete Front1;
    delete Front2;
    delete Front3;
    delete Front4;
    foreach (const Enemy *enemy, m_enemyList)
        delete enemy;
    // addition 6-6
    //delete ui;
}


void easyScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    /*case Qt::Key_1:
        this->putZombie(qrand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(qrand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(qrand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(qrand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(qrand() % 5, 4);
        break;
    case Qt::Key_6:
        this->putZombie(qrand() % 5, 5);
        break;
    case Qt::Key_7:
        this->putZombie(qrand() % 5, 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->threat = 6001;
        break;*/
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void easyScene::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        btn1->hide();
        btn2->hide();
        btn3->hide();
        btn4->hide();
        btn5->hide();
        btn6->hide();
        btn7->hide();
        btn8->hide();
        btn9->hide();
        btn10->hide();
        btn11->hide();
        btn12->hide();
        btn13->hide();

        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();
        Base->hide();
        Front1->hide();
        Front2->hide();
        Front3->hide();
        Front4->hide();
        LevelUp->hide();
        LevelFront->hide();
        LevelBar->hide();
        Upgrade_MoneyFront->hide();
        Upgrade_MoneyBar->hide();

        NormalTowerPic->hide();
        FireTowerPic->hide();
        IceTowerPic->hide();
        LaserTowerPic->hide();

        foreach (tCard *card, Cards)
        {
            Q_ASSERT(card);
            Cards.removeOne(card);
            delete card;
        }

        foreach (Tower *tower, m_towersList)
        {
            Q_ASSERT(tower);
            m_towersList.removeOne(tower);
            delete tower;
        }
        foreach (Enemy *enemy, m_enemyList)
        {
            Q_ASSERT(enemy);
            m_enemyList.removeOne(enemy);
            delete enemy;
        }

        if(m_gameWin){
        QPixmap loseScene(":/background/victory_better.jpg");
        //QPainter losePainter(&loseScene);
        QPainter painter(this);
        painter.drawPixmap(0, 0, loseScene);

        /*QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);*/
        }

        if(m_gameEnded)
        {
            QPixmap loseScene(":/background/lose1.jpg");
            //QPainter losePainter(&loseScene);
            QPainter painter(this);
            painter.drawPixmap(0, 0, loseScene);


        }
        return;
    }

    QPixmap cachePix(":/GameMap/easyMap2.jpg"); //背景图片【可改】！！
    //先在背景图片QPixmap上绘制，最后统一绘制QPixmap
    QPainter cachePainter(&cachePix); //缓存，避免直接在界面上绘制而效率低下

    //foreach手法，讲究
    /*foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);*/

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
      //  wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave();
    drawHP();
    drawPlayerGold();

    //初始化画笔
    QPainter painter(this);
    //画背景图片
    painter.drawPixmap(0, 0, cachePix);//QPixmap cachePix(":/image/Bg.png");*/

}

void easyScene::mousePressEvent(QMouseEvent * event)
{
    //单击鼠标后的处理
    QPoint pressPos = event->pos();
    int posx = pressPos.x();
    int posy = pressPos.y();

    if (upgradestate)
    {
        if (posx >= 100 && posx <= 150 && posy >= 410 && posy <= 460)
        {
            //升级,暂时没考虑满级(5级）如何处理
            int level = currenttower->m_level;
            int gold = 80 + level*100;
            if (m_playerGold >= gold)
            {
                m_playerGold -= gold;
                currenttower->levelup();

                LevelFront->setText(QString("level %1").arg(currenttower->m_level));
                LevelFront->show();
                LevelFront->raise();

                Upgrade_MoneyFront->setText(QString("%1").arg(gold+100));
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

            }
        }
        currenttower = nullptr;
        upgradestate = 0;
    }


    if (currentCard == nullptr ){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (currentCard == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;
                //有塔状态：显示等级和升级图表
                LevelFront->setText(QString("level %1").arg(it->m_tower->m_level));
                LevelFront->show();
                LevelFront->raise();
                switch (it->m_tower->m_level)
                {
                case 1:
                    Upgrade_MoneyFront->setText("180");
                    break;
                case 2:
                    Upgrade_MoneyFront->setText("280");
                    break;
                case 3:
                    Upgrade_MoneyFront->setText("380");
                    break;
                case 4:
                    Upgrade_MoneyFront->setText("480");
                    break;
                default:
                    Upgrade_MoneyFront->setText("---");
                    break;
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

                upgradestate = 1;
            }
            ++it;
        }
    }

    if(currentCard != nullptr){
        bool temp = 0;
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (currentCard != nullptr && canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            temp = 1;
            m_audioPlayer->playSound(TowerPlaceSound);

            it->setHasTower();
            Tower *tower;
            switch(currentIndex)
            {
            case 0:tower = new NormalTower(it->centerPos(), this);
                it->m_tower = tower;
                m_playerGold -= 100;
                it->m_towerkind = 0;
                break;
            case 1:tower = new FireTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_tower = tower;
                it->m_towerkind = 1;
                break;
            case 2:tower = new IceTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_towerkind = 2;
                it->m_tower = tower;
                break;
            case 3:tower = new LaserTower(it->centerPos(), this);
                m_playerGold -= 200;
                it->m_towerkind = 3;
                it->m_tower = tower;
                break;
            }
            m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            currentCard->move(currentPos);
            currentCard = nullptr;
            break;
        }

        ++it;
    }
        if(temp == 0)
        {
           currentCard->move(currentPos);
           currentCard = nullptr;
        }
    }

    //if(state == 0) //空状态
    int cardindex = -1;
    if (posx >= 180 && posx <= 280 && posy >= 10 && posy <= 60)
        cardindex = 0;
    else if (posx >= 280 && posx <= 380 && posy >= 10 && posy <= 60)
        cardindex = 1;
    else if (posx >= 430 && posx <= 530 && posy >= 10 && posy <= 60)
        cardindex = 2;
    else if (posx >= 530 && posx <= 630 && posy >= 10 && posy <= 60)
        cardindex = 3;

    if (cardindex >= 0)
    {
        currentPos = Cards[cardindex]->pos();
        this->currentCard = Cards[cardindex];
        currentIndex = cardindex;
    }
    }

void easyScene::onTimer()
{
    /*this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->createZombie();
    if (qrand() % 521 < 100)
    {
        zBonus* sun = new zSunFall(this);
        Bonuses.append(sun);
    }*/
    this->exit->raise();
    //this->judge();
}

void easyScene::leave()
{
    emit toTitle();
}

void easyScene::back()
{
    //MainWindow::back();
}

void easyScene::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void easyScene::gameStart()
{
    loadWave();
}


// 以下是对复杂地图的设计

hardScene::hardScene(QWidget* parent)
    : tScene(parent)
//, ui(new Ui::MainWindow)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/hard.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    //m_audioPlayer->getMusic()->setVolume(30);
    m_audioPlayer->startBGM();

    this->setGeometry(0, 0, 800, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    loadTowerPositions(); //调用位置函数

    //for different enemies
    addNormalWayPoints();
    addIceWayPoints();
    addFireWayPoints();
    addFastWayPoints();
    addBossWayPoints();

    //m_audioPlayer = new AudioPlayer(this);
    //m_audioPlayer->startBGM();

    //每30ms发送一个更新信号
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    this->uiSetup();
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

AudioPlayer *hardScene::audioPlayer() const
{
    return m_audioPlayer;
}

void hardScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
        m_gameWin = true;
        m_audioPlayer->stopBGM();
        m_audioPlayer->playWinSound();
        // 游戏胜利转到游戏胜利场景
        // 这里暂时以打印处理
        }
    }
}


void hardScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    /*case Qt::Key_1:
        this->putZombie(qrand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(qrand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(qrand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(qrand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(qrand() % 5, 4);
        break;
    case Qt::Key_6:
        this->putZombie(qrand() % 5, 5);
        break;
    case Qt::Key_7:
        this->putZombie(qrand() % 5, 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->threat = 6001;
        break;*/
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void hardScene::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        btn1->hide();
        btn2->hide();
        btn3->hide();
        btn4->hide();
        btn5->hide();
        btn6->hide();
        btn7->hide();
        btn8->hide();
        btn9->hide();
        btn10->hide();
        btn11->hide();
        btn12->hide();
        btn13->hide();
        btn14->hide();

        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();
        Base->hide();
        LevelUp->hide();
        LevelFront->hide();
        LevelBar->hide();
        Upgrade_MoneyFront->hide();
        Upgrade_MoneyBar->hide();
        Front1->hide();
        Front2->hide();
        Front3->hide();
        Front4->hide();

        NormalTowerPic->hide();
        FireTowerPic->hide();
        IceTowerPic->hide();
        LaserTowerPic->hide();

        foreach (tCard *card, Cards)
        {
            Q_ASSERT(card);
            Cards.removeOne(card);
            delete card;
        }

        //m_audioPlayer->stopBGM();

        if(m_gameWin){

        QPixmap loseScene(":/background/victory_better.jpg");
        //QPainter losePainter(&loseScene);
        QPainter painter(this);
        painter.drawPixmap(0, 0, loseScene);



        /*QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);*/
        }

        if(m_gameEnded)
        {
            QPixmap loseScene(":/background/lose1.jpg");
            //QPainter losePainter(&loseScene);
            QPainter painter(this);
            painter.drawPixmap(0, 0, loseScene);


        }
        return;
    }

    QPixmap cachePix(":/GameMap/hardMap2.jpg"); //背景图片【可改】！！
    //先在背景图片QPixmap上绘制，最后统一绘制QPixmap
    QPainter cachePainter(&cachePix); //缓存，避免直接在界面上绘制而效率低下

    //foreach手法，讲究
    /*foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);*/

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

   // foreach (const WayPoint *wayPoint, m_wayPointsList)
     //   wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave();
    drawHP();
    drawPlayerGold();

    //初始化画笔
    QPainter painter(this);
    //画背景图片
    painter.drawPixmap(0, 0, cachePix);//QPixmap cachePix(":/image/Bg.png");*/

}

void hardScene::mousePressEvent(QMouseEvent * event)
{
    //单击鼠标后的处理
    QPoint pressPos = event->pos();
    int posx = pressPos.x();
    int posy = pressPos.y();

    if (upgradestate)
    {
        if (posx >= 635 && posx <= 683 && posy >= 20 && posy <= 70)
        {
            //升级,暂时没考虑满级(5级）如何处理
            int level = currenttower->m_level;
            int gold = 80 + level*100;
            if (m_playerGold >= gold)
            {
                m_playerGold -= gold;
                currenttower->levelup();

                LevelFront->setText(QString("level %1").arg(currenttower->m_level));
                LevelFront->show();
                LevelFront->raise();

                Upgrade_MoneyFront->setText(QString("%1").arg(gold+100));
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();
            }
        }
        currenttower = nullptr;
        upgradestate = 0;
    }

    if (currentCard == nullptr ){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (currentCard == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;
                //有塔状态：显示等级和升级图表
                LevelFront->setText(QString("level %1").arg(it->m_tower->m_level));
                LevelFront->show();
                LevelFront->raise();
                switch (it->m_tower->m_level)
                {
                case 1:
                    Upgrade_MoneyFront->setText("180");
                    break;
                case 2:
                    Upgrade_MoneyFront->setText("280");
                    break;
                case 3:
                    Upgrade_MoneyFront->setText("380");
                    break;
                case 4:
                    Upgrade_MoneyFront->setText("480");
                    break;
                default:
                    Upgrade_MoneyFront->setText("---");
                    break;
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

                upgradestate = 1;
            }
            ++it;
        }
    }

    if(currentCard != nullptr){
        bool temp = 0;
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {

        if (currentCard != nullptr && canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            temp = 1;
            m_audioPlayer->playSound(TowerPlaceSound);

            it->setHasTower();
            Tower *tower;
            switch(currentIndex)
            {
            case 0:tower = new NormalTower(it->centerPos(), this);
                it->m_tower = tower;
                m_playerGold -= 100;
                it->m_towerkind = 0;
                break;
            case 1:tower = new FireTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_tower = tower;
                it->m_towerkind = 1;
                break;
            case 2:tower = new IceTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_towerkind = 2;
                it->m_tower = tower;
                break;
            case 3:tower = new LaserTower(it->centerPos(), this);
                m_playerGold -= 200;
                it->m_towerkind = 3;
                it->m_tower = tower;
                break;
            }
            m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            currentCard->move(currentPos);
            currentCard = nullptr;
            break;
        }

        ++it;
    }
    if(temp == 0)
    {
       currentCard->move(currentPos);
       currentCard = nullptr;
    }

    }

    //if(state == 0) //空状态
    int cardindex = -1;
    if (posx >= 180 && posx <= 280 && posy >= 10 && posy <= 60)
        cardindex = 0;
    else if (posx >= 280 && posx <= 380 && posy >= 10 && posy <= 60)
        cardindex = 1;
    else if (posx >= 430 && posx <= 530 && posy >= 10 && posy <= 60)
        cardindex = 2;
    else if (posx >= 530 && posx <= 630 && posy >= 10 && posy <= 60)
        cardindex = 3;

    if (cardindex >= 0)
    {
        currentPos = Cards[cardindex]->pos();
        this->currentCard = Cards[cardindex];
        currentIndex = cardindex;
    }
}

void hardScene::onTimer()
{
    /*this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->createZombie();
    if (qrand() % 521 < 100)
    {
        zBonus* sun = new zSunFall(this);
        Bonuses.append(sun);
    }*/
    this->exit->raise();
    //this->judge();
}

void hardScene::leave()
{
    emit toTitle();
}

void hardScene::back()
{
    //MainWindow::back();
}

void hardScene::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void hardScene::gameStart()
{
    loadWave();
}


void hardScene::uiSetup()
{
    MoneyBar->setGeometry(80, -70, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(-30, 10, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(10, -70, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(80, -10, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(-30, 70, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(10, -10, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);

    WaveBar->setGeometry(80, 50, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(70, 130, 100, 50);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(10, 50, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    Base->setGeometry(685, 325, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);
    Base->raise();

    LevelUp->setGeometry(635, 20, 50, 50);
    levelup->start();
    LevelUp->show();
    LevelUp->setMovie(levelup);
    LevelUp->raise();

    LevelBar->setGeometry(690, -15, 100, 80);
    levelbar->start();
    LevelBar->show();
    LevelBar->setMovie(levelbar);
    LevelBar->raise();
    LevelFront->setGeometry(580,85, 300, 200);
    LevelFront->setFont(QFont("Calibri", 16));
    LevelFront->setText("5");
    LevelFront->setAlignment(Qt::AlignHCenter);
    LevelFront->show();
    LevelFront->raise();

    Upgrade_MoneyBar->setGeometry(690, 35, 80, 50);
    upgrade_moneybar->start();
    Upgrade_MoneyBar->show();
    Upgrade_MoneyBar->setMovie(upgrade_moneybar);
    Upgrade_MoneyBar->raise();
    Upgrade_MoneyFront->setGeometry(690, 45, 80, 50);
    Upgrade_MoneyFront->setFont(QFont("Calibri", 16));
    Upgrade_MoneyFront->setText("100");
    Upgrade_MoneyFront->setAlignment(Qt::AlignHCenter);
    Upgrade_MoneyFront->show();
    Upgrade_MoneyFront->raise();//记得delete！！！

    btn1->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn1->setMovie(station);
    station->start();
    btn1->setGeometry(90, 425, 60, 60);
    btn1->show();
    btn1->raise();

    btn2->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn2->setMovie(station);
    station->start();
    btn2->setGeometry(170, 425, 60, 60);
    btn2->show();
    btn2->raise();

    btn3->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn3->setMovie(station);
    station->start();
    btn3->setGeometry(250, 425, 60, 60);
    btn3->show();
    btn3->raise();

    btn4->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn4->setMovie(station);
    station->start();
    btn4->setGeometry(640, 425, 60, 60);
    btn4->show();
    btn4->raise();

    btn5->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn5->setMovie(station);
    station->start();
    btn5->setGeometry(560, 425, 60, 60);
    btn5->show();
    btn5->raise();

    btn6->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn6->setMovie(station);
    station->start();
    btn6->setGeometry(480, 425, 60, 60);
    btn6->show();
    btn6->raise();

    btn7->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn7->setMovie(station);
    station->start();
    btn7->setGeometry(145, 280, 60, 60);
    btn7->show();
    btn7->raise();

    btn8->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn8->setMovie(station);
    station->start();
    btn8->setGeometry(215, 280, 60, 60);
    btn8->show();
    btn8->raise();

    btn9->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn9->setMovie(station);
    station->start();
    btn9->setGeometry(600, 280, 60, 60);
    btn9->show();
    btn9->raise();

    btn10->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn10->setMovie(station);
    station->start();
    btn10->setGeometry(530, 280, 60, 60);
    btn10->show();
    btn10->raise();

    btn11->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn11->setMovie(station);
    station->start();
    btn11->setGeometry(235, 140, 60, 60);
    btn11->show();
    btn11->raise();

    btn12->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn12->setMovie(station);
    station->start();
    btn12->setGeometry(305, 140, 60, 60);
    btn12->show();
    btn12->raise();

    btn13->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn13->setMovie(station);
    station->start();
    btn13->setGeometry(510, 140, 60, 60);
    btn13->show();
    btn13->raise();

    btn14->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn14->setMovie(station);
    station->start();
    btn14->setGeometry(440, 140, 60, 60);
    btn14->show();
    btn14->raise();


    exit->setGeometry(700, 130, 60, 60); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

    NormalTowerPic->setGeometry(180, 10, 100, 60);
    normalTowerPic->start();
    NormalTowerPic->show();
    NormalTowerPic->setMovie(normalTowerPic);

    FireTowerPic->setGeometry(280, 10 , 100, 60);
    fireTowerPic->start();
    FireTowerPic->show();
    FireTowerPic->setMovie(fireTowerPic);

    IceTowerPic->setGeometry(430, 10 , 100, 60);
    iceTowerPic->start();
    IceTowerPic->show();
    IceTowerPic->setMovie(iceTowerPic);

    LaserTowerPic->setGeometry(530, 10 , 100, 60);
    laserTowerPic->start();
    LaserTowerPic->show();
    LaserTowerPic->setMovie(laserTowerPic);

    tCard *card0 = new tNormalTowerCard(this);
    card0->setGeometry(180, 10 , 100, 60);
    Cards.append(card0);
    card0->show();

    Front1 = new QLabel(this);
    Front1->setText("100");
    Front1->setGeometry(225, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front1->setFont(QFont("Calibri", 11));
    Front1->show();
    Front1->raise();

    tCard *card1 = new tFireTowerCard(this);
    card1->setGeometry(280, 10 , 100, 60);
    Cards.append(card1);
    card1->show();

    Front2 = new QLabel(this);
    Front2->setText("150");
    Front2->setGeometry(325, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front2->setFont(QFont("Calibri", 11));
    Front2->show();
    Front2->raise();

    tCard *card2 = new tIceTowerCard(this);
    card2->setGeometry(430, 10 , 100, 60);
    Cards.append(card2);
    card2->show();

    Front3 = new QLabel(this);
    Front3->setText("150");
    Front3->setGeometry(475, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front3->setFont(QFont("Calibri", 11));
    Front3->show();
    Front3->raise();

    tCard *card3 = new tLaserTowerCard(this);
    card3->setGeometry(530, 10 , 100, 60);
    Cards.append(card3);
    card3->show();

    Front4 = new QLabel(this);
    Front4->setText("200");
    Front4->setGeometry(575, 40, 40, 20);
    //front1->setAlignment(Qt::AlignHCenter);
    Front4->setFont(QFont("Calibri", 11));
    Front4->show();
    Front4->raise();
}

void hardScene::loadTowerPositions()
{
    //读取文件中的炮塔位置信息，可以不用深究，但是可以修改位置【可改】

    //这里可以改变炮塔的位置，文件是html格式
    QFile file(":/config/hardTowersPosition.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    QList<QVariant> array = reader.data();
    foreach (QVariant dict, array)
    {
        QMap<QString, QVariant> point = dict.toMap();
        int x = point.value("x").toInt();
        int y = point.value("y").toInt();
        m_towerPositionsList.push_back(QPoint(x, y));
    }

    file.close();
}

void hardScene::addNormalWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(760, 540));//终点
        normalWayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(365, 540));
        normalWayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(365, 400));
        normalWayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(445, 380));
        normalWayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(455, 270));
        normalWayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(365, 250));
        normalWayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(275, 270));
        normalWayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(285, 380));
        normalWayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(365, 400));
        normalWayPointsList.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);

        WayPoint *wayPoint10 = new WayPoint(QPoint(365, 540));
        normalWayPointsList.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);

        WayPoint *wayPoint11 = new WayPoint(QPoint(5, 540));//起点
        normalWayPointsList.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);
}

void hardScene::addIceWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(765, 545));//终点
    iceWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(370, 545));
    iceWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(370, 400));
    iceWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(450, 410));
    iceWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(650, 400));
    iceWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(685, 330));
    iceWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(675, 270));
    iceWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(600, 225));
    iceWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(595, 155));
    iceWayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(575, 120));
    iceWayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(505, 105));
    iceWayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(380, 105));
    iceWayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(380, 230));
    iceWayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(285, 270));
    iceWayPointsList.push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);

    WayPoint *wayPoint15 = new WayPoint(QPoint(285, 380));
    iceWayPointsList.push_back(wayPoint15);
    wayPoint15->setNextWayPoint(wayPoint14);

    WayPoint *wayPoint16 = new WayPoint(QPoint(370, 400));
    iceWayPointsList.push_back(wayPoint16);
    wayPoint16->setNextWayPoint(wayPoint15);

    WayPoint *wayPoint17 = new WayPoint(QPoint(370, 545));
    iceWayPointsList.push_back(wayPoint17);
    wayPoint17->setNextWayPoint(wayPoint16);

    WayPoint *wayPoint18 = new WayPoint(QPoint(5, 545));//起点
    iceWayPointsList.push_back(wayPoint18);
    wayPoint18->setNextWayPoint(wayPoint17);
}

void hardScene::addFireWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(770, 540));//终点
    fireWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(375, 540));
    fireWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(385, 405));
    fireWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(465, 385));
    fireWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(465, 270));
    fireWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(385, 215));
    fireWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(385, 105));
    fireWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(240, 105));
    fireWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(200, 105));
    fireWayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(190, 125));
    fireWayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(170, 160));
    fireWayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(165, 230));
    fireWayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(90,275));
    fireWayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(80, 335));
    fireWayPointsList.push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);

    WayPoint *wayPoint15 = new WayPoint(QPoint(105, 385));
    fireWayPointsList.push_back(wayPoint15);
    wayPoint15->setNextWayPoint(wayPoint14);

    WayPoint *wayPoint16 = new WayPoint(QPoint(295, 395));
    fireWayPointsList.push_back(wayPoint16);
    wayPoint16->setNextWayPoint(wayPoint15);

    WayPoint *wayPoint17 = new WayPoint(QPoint(375, 405));
    fireWayPointsList.push_back(wayPoint17);
    wayPoint17->setNextWayPoint(wayPoint16);

    WayPoint *wayPoint18 = new WayPoint(QPoint(375, 540));
    fireWayPointsList.push_back(wayPoint18);
    wayPoint18->setNextWayPoint(wayPoint17);

    WayPoint *wayPoint19 = new WayPoint(QPoint(5, 540));//起点
    fireWayPointsList.push_back(wayPoint19);
    wayPoint19->setNextWayPoint(wayPoint18);
}

void hardScene::addFastWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(795, 545));//终点
    fastWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(420, 545));
    fastWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(420, 400));
    fastWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(480, 400));
    fastWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(670, 400));
    fastWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(700, 330));
    fastWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(685, 270));
    fastWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(630, 240));
    fastWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(400, 250));
    fastWayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(170, 250));
    fastWayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(105, 270));
    fastWayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(95, 330));
    fastWayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(110, 400));
    fastWayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(320, 400));
    fastWayPointsList.push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);

    WayPoint *wayPoint15 = new WayPoint(QPoint(400, 400));
    fastWayPointsList.push_back(wayPoint15);
    wayPoint15->setNextWayPoint(wayPoint14);

    WayPoint *wayPoint16 = new WayPoint(QPoint(400, 545));
    fastWayPointsList.push_back(wayPoint16);
    wayPoint16->setNextWayPoint(wayPoint15);

    WayPoint *wayPoint17 = new WayPoint(QPoint(5, 545));
    fastWayPointsList.push_back(wayPoint17);
    wayPoint17->setNextWayPoint(wayPoint16);//起点
}

void hardScene::addBossWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(795, 545));//终点
    bossWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(400, 545));
    bossWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(400, 400));
    bossWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(480, 380));
    bossWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(680, 390));
    bossWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(700, 330));
    bossWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(695, 270));
    bossWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(680, 220));
    bossWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(625, 215));
    bossWayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(610, 155));
    bossWayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(575, 100));
    bossWayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(535, 100));
    bossWayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(400,100));
    bossWayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(265, 100));
    bossWayPointsList.push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);

    WayPoint *wayPoint15 = new WayPoint(QPoint(215, 90));
    bossWayPointsList.push_back(wayPoint15);
    wayPoint15->setNextWayPoint(wayPoint14);

    WayPoint *wayPoint16 = new WayPoint(QPoint(185, 100));
    bossWayPointsList.push_back(wayPoint16);
    wayPoint16->setNextWayPoint(wayPoint15);

    WayPoint *wayPoint17 = new WayPoint(QPoint(180, 155));
    bossWayPointsList.push_back(wayPoint17);
    wayPoint17->setNextWayPoint(wayPoint16);

    WayPoint *wayPoint18 = new WayPoint(QPoint(180, 215));
    bossWayPointsList.push_back(wayPoint18);
    wayPoint18->setNextWayPoint(wayPoint17);

    WayPoint *wayPoint19 = new WayPoint(QPoint(110, 215));
    bossWayPointsList.push_back(wayPoint19);
    wayPoint19->setNextWayPoint(wayPoint18);

    WayPoint *wayPoint20 = new WayPoint(QPoint(100, 270));
    bossWayPointsList.push_back(wayPoint20);
    wayPoint20->setNextWayPoint(wayPoint19);

    WayPoint *wayPoint21 = new WayPoint(QPoint(90, 330));
    bossWayPointsList.push_back(wayPoint21);
    wayPoint21->setNextWayPoint(wayPoint20);

    WayPoint *wayPoint22= new WayPoint(QPoint(150, 400));
    bossWayPointsList.push_back(wayPoint22);
    wayPoint22->setNextWayPoint(wayPoint21);

    WayPoint *wayPoint23 = new WayPoint(QPoint(320, 390));
    bossWayPointsList.push_back(wayPoint23);
    wayPoint23->setNextWayPoint(wayPoint22);

    WayPoint *wayPoint24 = new WayPoint(QPoint(400, 400));
    bossWayPointsList.push_back(wayPoint24);
    wayPoint24->setNextWayPoint(wayPoint23);

    WayPoint *wayPoint25 = new WayPoint(QPoint(400, 545));
    bossWayPointsList.push_back(wayPoint25);
    wayPoint25->setNextWayPoint(wayPoint24);

    WayPoint *wayPoint26 = new WayPoint(QPoint(5, 545));
    bossWayPointsList.push_back(wayPoint26);
    wayPoint26->setNextWayPoint(wayPoint25);
}


bool hardScene::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    //WayPoint *startWayPoint= iceWayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new normalEnemy(normalWayPointsList.back(), this);
            break;
        case 1:
            enemy=new iceEnemy(iceWayPointsList.back(), this);
            break;
        case 2:
            enemy=new fireEnemy(fireWayPointsList.back(), this);
            break;
        case 3:
            enemy=new fastEnemy(fastWayPointsList.back(), this);
            break;
        case 4:
            enemy=new bossEnemy(bossWayPointsList.back(), this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

bool hardScene::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void hardScene::drawWave()
{
    WaveFront->setText(QString("%1").arg(m_waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}

void hardScene::drawHP()
{
    LifeFront->setText(QString("%1").arg(m_playerHp));
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
}

void hardScene::drawPlayerGold()
{
    MoneyFront->setText(QString("%1").arg(m_playerGold));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
}

void hardScene::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

hardScene::~hardScene()
{
    delete this->background;
    delete this->exit;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
    delete this->btn5;
    delete this->btn6;
    delete this->btn7;
    delete this->btn8;
    delete this->btn9;
    delete this->btn10;
    delete this->btn11;
    delete this->btn12;
    delete this->btn13;
    delete this->btn14;

    foreach (const Tower *tower, m_towersList)
        delete tower;
    foreach (const Enemy *enemy, m_enemyList)
        delete enemy;
    // addition 6-6
    //delete ui;
}
