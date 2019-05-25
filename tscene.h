#ifndef TSCENE_H
#define TSCENE_H

#include <QWidget>
#include<QMovie>
#include<QTimer>
#include<QLabel>


class tScene : public QLabel
{
    Q_OBJECT
public:
    explicit tScene(QWidget *parent = 0);
    ~tScene();

    QTimer* timer = nullptr;


signals:
    void toTitle();

public slots:
};

class tStartScreen : public tScene
{
    Q_OBJECT
public:
    explicit tStartScreen(QWidget* parent = 0);
    ~tStartScreen();
private:
    QMovie* background = new QMovie(":/background/scene1.jpg");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
};

#endif // TSCENE_H
