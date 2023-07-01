#include "musplayer.h"
#include "ui_musplayer.h"
#include "mouse.h"


#include <QFileDialog>
#include <QHBoxLayout>
#include <QSlider>
#include <QTimer>
#include <QFileDialog>

#pragma execution_character_set("utf-8")
musPlayer::musPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::musPlayer)
{
    ui->setupUi(this);
    //配置选择关卡场景
    //this->setFixedSize(1588,120);

    //设置图标
    this->setWindowIcon(QPixmap(":/image/Icon.png"));

    //设置标题
    this->setWindowTitle("选择音乐");
    // 创建控件
    player = new QMediaPlayer(this);
    playButton = new QPushButton("播放歌曲");
    stopButton = new QPushButton("停止歌曲");
    deleteButton = new QPushButton("删除歌曲");
    //创建播放列表，大小为（1158，600）
    songList = new QListWidget;
    songList->setFixedSize(1250,500);
    //songList->move(100,50);

    progressTimer = new QTimer(this);
    //定时器每隔一秒触发一次updateProgress
    connect(progressTimer, &QTimer::timeout, this, &musPlayer::updateProgress);


    //progressSlider = new QSlider(Qt::Horizontal, this);
    //progressSlider->setRange(0, 0); // The range will be updated later when a song is loaded
    //connect(progressSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(ui->progressSlider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->move(1100,960);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // Set default volume to 50%
    connect(volumeSlider, &QSlider::valueChanged, this, &musPlayer::updateVolume);
    player->setVolume(50);


    Mouse *btnLeft = new Mouse(this);
    Mouse *btnright = new Mouse(this);
    //Mouse *btnbegin = new Mouse(this);

    btnLeft->setButton(ui->btnLast,":/image/musicPlayer/left1.JPG",":/image/musicPlayer/left2.JPG",":/image/musicPlayer/left2.JPG");

    btnright->setButton(ui->btnNext,":/image/musicPlayer/Right1.JPG",":/image/musicPlayer/Right2.JPG",":/image/musicPlayer/Right2.JPG");

    ui->btnBegin->setIcon(QIcon(":/image/musicPlayer/play.JPG"));
    ui->btnBegin->setIconSize(QSize(68,65));

    //btnbegin->setButton(ui->btnBegin,);

    QPushButton *addButton = new QPushButton("添加歌曲", this);
    addButton->move(1150,10);
    playlist = new QMediaPlaylist(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    //QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(songList);
//    mainLayout->addWidget(playButton);
//    mainLayout->addWidget(stopButton);
//    mainLayout->addWidget(deleteButton);
//    mainLayout->addWidget(addButton);

    //mainLayout->addWidget(progressSlider);
    //mainLayout->addWidget(volumeSlider);
    setLayout(mainLayout);

    // 连接按钮的点击事件
    connect(addButton, &QPushButton::clicked, this, &musPlayer::addSongs);
//    connect(playButton, &QPushButton::clicked, this, &musPlayer::playMusic);
    connect(stopButton, &QPushButton::clicked, this, &musPlayer::stopMusic);
    connect(songList, &QListWidget::itemDoubleClicked, this, &musPlayer::playSelectedMusic);
//    connect(deleteButton,&QPushButton::clicked,this,&musPlayer::deleteMusic);

    //connect(addButton, &QPushButton::clicked, this, &musPlayer::addSongs);
    connect(ui->btnBegin, &QPushButton::clicked, this, &musPlayer::playMusic);
    connect(ui->btnLast,&QPushButton::clicked,this,&musPlayer::playPreviousMusic);
    connect(ui->btnNext,&QPushButton::clicked,this,&musPlayer::playNextMusic);
    //connect(ui->btnBegin, &QPushButton::clicked, this, &musPlayer::stopMusic);
    //connect(songList, &QListWidget::itemDoubleClicked, this, &musPlayer::playSelectedMusic);
    connect(deleteButton,&QPushButton::clicked,this,&musPlayer::deleteMusic);

    // 设置播放器
    player->setPlaylist(playlist);
}

musPlayer::~musPlayer()
{
    delete ui;
}

void musPlayer::addSongs()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "选择歌曲", "", "MP3 Files (*.mp3)");
    foreach (const QString &fileName, fileNames) {
        playlist->addMedia(QUrl::fromLocalFile(fileName));
        qDebug() << "添加歌曲：" << fileName;
    }

    // 更新歌曲列表
    updateSongList();
}

void musPlayer::updateSongList()
{
    songList->clear();
    for (int i = 0; i < playlist->mediaCount(); ++i) {
        QMediaContent media = playlist->media(i);
        QUrl url = media.canonicalUrl();
        QString fileName = url.fileName();
        songList->addItem(fileName);
    }
}

void musPlayer::playMusic()
{
    if (playlist->isEmpty())
        return;

    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        playButton->setText("播放");
        progressTimer->stop();
        ui->btnBegin->setIcon(QIcon(":/image/musicPlayer/play.JPG"));
    } else {
        player->play();
        playButton->setText("暂停");
        progressTimer->start(1000);
        ui->btnBegin->setIcon(QIcon(":"
                                    "/image/musicPlayer/pause.JPG"));
    }

}

void musPlayer::stopMusic()
{
    player->stop();
    playButton->setText("播放");
    progressTimer->stop();
}

void musPlayer::deleteMusic(){
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

void musPlayer::playSelectedMusic()
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
void musPlayer::updateVolume(int volume)
{

    player->setVolume(volume);
}

void musPlayer::updateProgress()
{
    int position = player->position();
    int duration = player->duration();
    ui->progressSlider->setRange(0, duration);
    ui->progressSlider->setValue(position);
}

void musPlayer::playPreviousMusic()
{
    // 获取当前播放的歌曲索引
    int currentIndex = playlist->currentIndex();
    // 计算上一首歌曲的索引
    int previousIndex = currentIndex - 1;
    if (previousIndex < 0)
        previousIndex = playlist->mediaCount() - 1;
    // 设置上一首歌曲为当前播放索引并播放
    playlist->setCurrentIndex(previousIndex);
    player->play();
    playButton->setText("暂停");
}

void musPlayer::playNextMusic()
{
    // 获取当前播放的歌曲索引
    int currentIndex = playlist->currentIndex();

    // 计算下一首歌曲的索引
    int nextIndex = currentIndex + 1;
    if (nextIndex >= playlist->mediaCount())
        nextIndex = 0;

    // 设置下一首歌曲为当前播放索引并播放
    playlist->setCurrentIndex(nextIndex);
    player->play();
    playButton->setText("暂停");
}

