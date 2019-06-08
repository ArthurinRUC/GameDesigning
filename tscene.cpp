#include "tscene.h"

static const int TowerCost = 300;

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
}

tStartScreen::tStartScreen(QWidget* parent) : tScene(parent)
{
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

tStartScene::tStartScene(QWidget* parent) : tScene(parent)
{
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
    this->setGeometry(0, 0, 800, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    //loadTowerPositions(); //调用位置函数
    addWayPoints();

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

    Base->setGeometry(725, 55, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);

    btn1->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn1->setMovie(station);
    station->start();
    btn1->setGeometry(50, 220, 70, 70);
    btn1->show();
    btn1->raise();

    btn2->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn2->setMovie(station);
    station->start();
    btn2->setGeometry(50, 145, 70, 70);
    btn2->show();
    btn2->raise();

    btn3->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn3->setMovie(station);
    station->start();
    btn3->setGeometry(120, 70, 70, 70);
    btn3->show();
    btn3->raise();

    btn4->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn4->setMovie(station);
    station->start();
    btn4->setGeometry(205, 235, 70, 70);
    btn4->show();
    btn4->raise();

    btn5->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn5->setMovie(station);
    station->start();
    btn5->setGeometry(305, 235, 70, 70);
    btn5->show();
    btn5->raise();

    btn6->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn6->setMovie(station);
    station->start();
    btn6->setGeometry(205, 315, 70, 70);
    btn6->show();
    btn6->raise();

    btn7->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn7->setMovie(station);
    station->start();
    btn7->setGeometry(305, 315, 70, 70);
    btn7->show();
    btn7->raise();

    btn8->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn8->setMovie(station);
    station->start();
    btn8->setGeometry(460, 125, 70, 70);
    btn8->show();
    btn8->raise();

    btn9->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn9->setMovie(station);
    station->start();
    btn9->setGeometry(460, 200, 70, 70);
    btn9->show();
    btn9->raise();

    btn10->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn10->setMovie(station);
    station->start();
    btn10->setGeometry(540, 200, 70, 70);
    btn10->show();
    btn10->raise();

    btn11->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn11->setMovie(station);
    station->start();
    btn11->setGeometry(400, 385, 70, 70);
    btn11->show();
    btn11->raise();

    btn12->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn12->setMovie(station);
    station->start();
    btn12->setGeometry(480, 385, 70, 70);
    btn12->show();
    btn12->raise();

    btn13->setStyleSheet("QLabel{border: 1px solid #000000;} QLabel:hover{border:1px solid #EE0000;}");
    btn13->setMovie(station);
    station->start();
    btn13->setGeometry(620, 90, 70, 70);
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
}

void easyScene::loadTowerPositions()
{
    //读取文件中的炮塔位置信息，可以不用深究，但是可以修改位置【可改】

    //这里可以改变炮塔的位置，文件是html格式
    QFile file(":/config/TowersPosition.plist");
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
    WayPoint *wayPoint1 = new WayPoint(QPoint(790, 225));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(640, 225));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(640, 335));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(415, 335));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(415, 195));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(145, 195));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(145, 350));
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

        Enemy *enemy = new Enemy(startWayPoint, this);
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

void tScene::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
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
    // addition 6-6
    //delete ui;
}

void tScene::getHpDamage(int damage)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void tScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        //if (!loadWave())
        //{
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        //}
    }
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

AudioPlayer *easyScene::audioPlayer() const
{
    return m_audioPlayer;
}

QList<Enemy *> tScene::enemyList() const
{
    return m_enemyList;
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
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);*/

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
      //  wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    //foreach (const Bullet *bullet, m_bulletList)
        //bullet->draw(&cachePainter);

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
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playerGold -= TowerCost;
            it->setHasTower();

            //Tower *tower = new Tower(it->centerPos(), this);
            //m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            break;
        }

        ++it;
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
    //foreach (Tower *tower, m_towersList)
        //tower->checkEnemyInRange();
    update();
}

void easyScene::gameStart()
{
    loadWave();
}


// 以下是对复杂地图的设计

AudioPlayer *hardScene::audioPlayer() const
{
    return m_audioPlayer;
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
        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();



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
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);*/

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
      //  wayPoint->draw(&cachePainter); //绘制航线

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    //foreach (const Bullet *bullet, m_bulletList)
        //bullet->draw(&cachePainter);

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
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playerGold -= TowerCost;
            it->setHasTower();

            //Tower *tower = new Tower(it->centerPos(), this);
            //m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            break;
        }

        ++it;
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
    //foreach (Tower *tower, m_towersList)
        //tower->checkEnemyInRange();
    update();
}

void hardScene::gameStart()
{
    loadWave();
}

hardScene::hardScene(QWidget* parent)
    : tScene(parent)
  //, ui(new Ui::MainWindow)
{
    this->setGeometry(0, 0, 800, 600);
    //this->cellSize = QPoint(81, 100);
    //this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    //loadTowerPositions(); //调用位置函数
    addWayPoints();

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

void hardScene::uiSetup()
{
    MoneyBar->setGeometry(80, -60, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(-30, 20, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(10, -60, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(80, 20, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(-30, 100, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(10, 20, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);


    WaveBar->setGeometry(700, -60, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(690, 20, 100, 50);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();

    WaveFront->raise();
    WaveLabel->setGeometry(620, -60, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    exit->setGeometry(700, 80, 60, 60); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

}

void hardScene::loadTowerPositions()
{
    //读取文件中的炮塔位置信息，可以不用深究，但是可以修改位置【可改】

    //这里可以改变炮塔的位置，文件是html格式
    QFile file(":/config/TowersPosition.plist");
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

void hardScene::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(795, 525));//终点
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(400, 525));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(400, 400));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(480, 380));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(490, 245));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(400, 210));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(310, 245));
        m_wayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(320, 380));
        m_wayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(400, 400));
        m_wayPointsList.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);

        WayPoint *wayPoint10 = new WayPoint(QPoint(400, 525));
        m_wayPointsList.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);

        WayPoint *wayPoint11 = new WayPoint(QPoint(5, 525));//起点
        m_wayPointsList.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);
}

bool hardScene::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy = new Enemy(startWayPoint, this);
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

    // addition 6-6
    //delete ui;
}
