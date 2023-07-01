#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>

//QT_BEGIN_NAMESPACE
//namespace Ui { class musicPlayer; }
//QT_END_NAMESPACE

class musicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit musicPlayer(QWidget *parent = nullptr);
    int index;

private slots:
    void addSongs();
    void updateSongList();
    void playMusic();
    void stopMusic();
    void deleteMusic();
    void playSelectedMusic();

private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *deleteButton;
    QListWidget *songList;

signals:

};

#endif // MUSICPLAYER_H
