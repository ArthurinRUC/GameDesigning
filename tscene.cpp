#include "tscene.h"


tScene::tScene(QWidget *parent) : QLabel(parent)
{

}

tScene::~tScene()
{

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
        if (frame > 500)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 500) / 500.0) +")");
        }
        if (frame < 300)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((300 - frame) / 300.0) +")");
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
    btn1->setMovie(lawn);
    lawn->start();
    btn2->setMovie(dark);
    dark->start();
    btn1->setGeometry(120, 205, 180, 180);
    btn2->setGeometry(500, 205, 180, 180);
    btn1->show();
    btn2->show();
    title->setText("Select a Scene");
    title->setGeometry(290, 0, 240, 100);
    title->setFont(QFont("Consolas", 18));
    title->show();

    /*文件操作 设置从文本读取用户名和时间
    QFile file(":/user.txt");      //文件操作 读取文件中的用户名
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList string_list;
    QString line = in.readLine();
    string_list=line.split(" ");   //分割文本 用元素初始化对象

    QString user_name=string_list[0];
    QString best_time=string_list[1];
    QString str1="User: "+user_name;
    QString str2="BestTime: "+best_time;
    UserName->setGeometry(40, 430, 300, 100);
    BestTime->setGeometry(40,460,300,100);
    UserName->setText(str1);
    BestTime->setText(str2);
    UserName->setFont(QFont("Consolas", 14));
    BestTime->setFont(QFont("Consolas", 14));
    UserName->show();
    BestTime->show();
    file.close();*/

}

tStartScene::~tStartScene()
{
    delete this->background;
    delete this->lawn;
    delete this->dark;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
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
