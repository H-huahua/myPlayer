#include "musicplayer.h"
//#include "ui_musicplayer.h"
#include "mouse.h"

#include <QFileDialog>
#include <QDebug>

#pragma execution_character_set("utf-8")

//musicPlayer::musicPlayer(QWidget *parent) : QWidget(parent)
//{

//}


musicPlayer::musicPlayer(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::myPlayer)
{
    //ui->setupUi(this);

    //配置选择关卡场景
    this->setFixedSize(1588,120);

    //设置图标
    this->setWindowIcon(QPixmap(":/image/Icon.png"));

    //设置标题
    this->setWindowTitle("选择音乐");
    // 创建控件
    player = new QMediaPlayer(this);
    playButton = new QPushButton("播放歌曲");
    stopButton = new QPushButton("停止歌曲");
    deleteButton = new QPushButton("删除歌曲");
    songList = new QListWidget;

    QPushButton *addButton = new QPushButton("添加歌曲", this);
    playlist = new QMediaPlaylist(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(songList);
    mainLayout->addWidget(playButton);
    mainLayout->addWidget(stopButton);
    mainLayout->addWidget(deleteButton);
    mainLayout->addWidget(addButton);


    setLayout(mainLayout);

    // 连接按钮的点击事件
    connect(addButton, &QPushButton::clicked, this, &musicPlayer::addSongs);
    connect(playButton, &QPushButton::clicked, this, &musicPlayer::playMusic);
    connect(stopButton, &QPushButton::clicked, this, &musicPlayer::stopMusic);
    connect(songList, &QListWidget::itemDoubleClicked, this, &musicPlayer::playSelectedMusic);
    connect(deleteButton,&QPushButton::clicked,this,&musicPlayer::deleteMusic);

    // 设置播放器
    player->setPlaylist(playlist);
}

//musicPlayer::~musicPlayer()
//{
//    delete ui;
//}

void musicPlayer::addSongs()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "选择歌曲", "", "MP3 Files (*.mp3)");
    foreach (const QString &fileName, fileNames) {
        playlist->addMedia(QUrl::fromLocalFile(fileName));
        qDebug() << "添加歌曲：" << fileName;
    }

    // 更新歌曲列表
    updateSongList();
}

void musicPlayer::updateSongList()
{
    songList->clear();
    for (int i = 0; i < playlist->mediaCount(); ++i) {
        QMediaContent media = playlist->media(i);
        QUrl url = media.canonicalUrl();
        QString fileName = url.fileName();
        songList->addItem(fileName);
    }
}

void musicPlayer::playMusic()
{
    if (playlist->isEmpty())
        return;

    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        playButton->setText("播放");
    } else {
        player->play();
        playButton->setText("暂停");
    }
}

void musicPlayer::stopMusic()
{
    player->stop();
    playButton->setText("播放");
}

void musicPlayer::deleteMusic(){
    // 获取当前选中的歌曲
    QListWidgetItem *selectedItem = songList->currentItem();
    if (!selectedItem)
        return;

    // 获取选中歌曲的索引并从播放列表中删除
    int selectedIndex = songList->row(selectedItem);
    playlist->removeMedia(selectedIndex);

    //playlist->removeMedia(index);
    updateSongList();
}

void musicPlayer::playSelectedMusic()
{
    // 获取当前选中的歌曲
    QListWidgetItem *selectedItem = songList->currentItem();
    if (!selectedItem)
        return;

    // 获取选中歌曲的索引并设置为当前播放索引
    index = songList->row(selectedItem);
    playlist->setCurrentIndex(index);

    // 播放选中的歌曲
    player->play();
    playButton->setText("暂停");
}
