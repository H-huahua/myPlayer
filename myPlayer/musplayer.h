#ifndef MUSPLAYER_H
#define MUSPLAYER_H

#include <QWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class musPlayer; }
QT_END_NAMESPACE

class musPlayer : public QWidget
{
    Q_OBJECT

public:
    musPlayer(QWidget *parent = nullptr);
    ~musPlayer();
    int index;
    void addSongs();
    void updateSongList();
    void playMusic();
    void stopMusic();
    void deleteMusic();
    void playSelectedMusic();

    void updateVolume(int volume);
    void updateProgress();
    void playPreviousMusic();
    void playNextMusic();

private slots:
//    void addSongs();
//    void updateSongList();
//    //void playMusic();
//    void stopMusic();
//    void deleteMusic();
//    void playSelectedMusic();

//    void updateVolume(int volume);
//    void updateProgress();
//    void playPreviousMusic();
//    void playNextMusic();




private:
    Ui::musPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *deleteButton;
    QListWidget *songList;

    QSlider *progressSlider;
    QSlider *volumeSlider;
    QTimer *progressTimer;
};
#endif // MUSPLAYER_H
