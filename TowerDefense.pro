#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    audioplayer.cpp \
    plistreader.cpp \
    tscene.cpp

HEADERS  += mainwindow.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    audioplayer.h \
    plistreader.h \
    tscene.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    uml_class.qmodel \
    music/easy.mp3 \
    music/First Page.mp3 \
    music/hard.mp3 \
    music/bossEnemyDie.mp3 \
    music/fastEnemyDie.mp3 \
    music/fireEnemyDie.mp3 \
    music/iceEnemyDie.mp3 \
    music/normalEnemyDie.mp3 \
    music/Lose.mp3 \
    music/Win.mp3 \
    music/fireBullet.mp3 \
    music/iceBulet.mp3 \
    music/laserBullet.mp3 \
    music/normalBullet.mp3
