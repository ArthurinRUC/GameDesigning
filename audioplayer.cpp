#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>

// 为了解决mac下声音无法输出,总之发现使用绝对路径可以完成目标,蛋疼,因此以此种方式暂时处理.
static const QString s_curDir = "C:/Users/81915/Desktop/LS/Programming/GD/GameDesigning/music";

AudioPlayer::AudioPlayer(QUrl backgroundMusicUrl,QObject *parent)
	: QObject(parent)
	, m_backgroundMusic(NULL)
{
	// 创建一直播放的背景音乐
    //QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "music/8bitDungeonLevel.mp3");搬出去！
	if (QFile::exists(backgroundMusicUrl.toLocalFile()))
	{
		m_backgroundMusic = new QMediaPlayer(this);
		QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();

		QMediaContent media(backgroundMusicUrl);
		backgroundMusicList->addMedia(media);
		backgroundMusicList->setCurrentIndex(0);
		// 设置背景音乐循环播放
		backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
		m_backgroundMusic->setPlaylist(backgroundMusicList);
	}
}

void AudioPlayer::startBGM()
{
	if (m_backgroundMusic)
		m_backgroundMusic->play();
}

void AudioPlayer::playSound(SoundType soundType)
{
	static const QUrl mediasUrls[] =
	{
        QUrl::fromLocalFile(s_curDir + "/tower_place.mp3"),
        QUrl::fromLocalFile(s_curDir + "/life_lose.mp3"),
        QUrl::fromLocalFile(s_curDir + "/laser_shoot.wav"),
        QUrl::fromLocalFile(s_curDir + "/enemy_destroy.wav")
	};
	static QMediaPlayer player;

	if (QFile::exists(mediasUrls[soundType].toLocalFile()))
	{
		player.setMedia(mediasUrls[soundType]);
		player.play();
	}
}


