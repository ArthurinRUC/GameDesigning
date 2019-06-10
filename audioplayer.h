#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

// 为了解决mac下声音无法输出,总之发现使用绝对路径可以完成目标,蛋疼,因此以此种方式暂时处理.
static const QString s_curDir = "C:/Users/81915/Desktop/LS/Programming/GD/GameDesigning/music";

class QMediaPlayer;

enum SoundType
{
	TowerPlaceSound,		// 放塔时的声音
	LifeLoseSound,			// 基地费血时的声音
    LaserShootSound,		// 打中敌人时的声音，需继续修改
    EnemyDestorySound		// 敌人升天时的声音，需继续修改
};

class AudioPlayer : public QObject
{
public:
    explicit AudioPlayer(QUrl backgroundMusicUrl,QObject *parent = 0);
	void startBGM();
	void playSound(SoundType soundType);

private:
	QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
};



#endif // AUDIOPLAYER_H
