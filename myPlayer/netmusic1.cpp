#include "netmusic1.h"
#include "ui_netmusic1.h"
#include "mouse.h"

#include <QVBoxLayout>
#include <QTimer>


netMusic1::netMusic1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::netMusic1)
{
    ui->setupUi(this);
    Mouse *btn1 = new Mouse(this);
    Mouse *btn2 = new Mouse(this);
    Mouse *btn3 = new Mouse(this);
    Mouse *btn4 = new Mouse(this);
    Mouse *gedan = new Mouse(this);
    Mouse *lBtn = new Mouse(this);
    Mouse *rBtn = new Mouse(this);

    btn1->setButton(ui->btn1,":/image/songsList/1_1.png",":/image/songsList/1_2.png",":/image/songsList/1_2.png");
    btn2->setButton(ui->btn2,":/image/songsList/2_1.png",":/image/songsList/2_2.png",":/image/songsList/2_2.png");
    btn3->setButton(ui->btn3,":/image/songsList/3_1.png",":/image/songsList/3_2.png",":/image/songsList/3_2.png");
    btn4->setButton(ui->btn4,":/image/songsList/4_1.png",":/image/songsList/4_2.png",":/image/songsList/4_2.png");
    gedan->setButton(ui->BtnGedan,":/image/songsList/gedan.png",":/image/songsList/gedan.png",":/image/songsList/gedan.png");

    lBtn->setButton(ui->lBtn,":/image/lunbo/left1.png",":/image/lunbo/left2.png",":/image/lunbo/left2.png");
    rBtn->setButton(ui->rBtn,":/image/lunbo/right1.png",":/image/lunbo/right2.png",":/image/lunbo/right2.png");



    //ui->lblLunbo = new QLabel(this);

    //ui->lblLunbo->setScaledContents(true);
    //ui->lblLunbo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblLunbo->setStyleSheet("background-color: transparent;");
    ui->lblLunbo->move(0,0);

    connect(ui->rBtn,&QPushButton::clicked,[=](){
        nextImage();
    });

    //connect(prevButton, SIGNAL(clicked()), this, SLOT(prevImage()));
    connect(ui->lBtn,&QPushButton::clicked,[=](){
        prevImage();
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->insertWidget(0,ui->lblLunbo , 0, Qt::AlignTop);
    //layout->addWidget(ui->lblLunbo);
    //setLayout(layout);

    // 添加图片路径
    imagePaths <<":/lunbo/11.JPG"
            <<":/lunbo/12.JPG"
            <<":/lunbo/13.JPG"
            <<":/lunbo/14.JPG";
    // 设置初始图片
    showImage();

    // 创建动画对象
    animation = new QPropertyAnimation(ui->lblLunbo, "geometry", this);
    animation->setDuration(1000); // 动画持续时间为1000毫秒
    // 创建定时器，设置自动切换图片
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &netMusic1::nextImage);
    timer->start(4000); // 设置定时器间隔为2000毫秒（4秒）
}


netMusic1::~netMusic1()
{
    delete ui;
}

void netMusic1::showImage()
{
    if (currentIndex >= 0 && currentIndex < imagePaths.size())
    {
        QPixmap image(imagePaths[currentIndex]);
        ui->lblLunbo->setPixmap(image);
        //ui->lblLunbo->adjustSize();
    }
}

void netMusic1::animateImage(int startX, int endX)
{
    QRect startRect(startX, 0, ui->lblLunbo->width(), ui->lblLunbo->height());
    QRect endRect(endX, 0, ui->lblLunbo->width(), ui->lblLunbo->height());

    animation->setStartValue(startRect);
    animation->setEndValue(endRect);
    animation->start();
}


void netMusic1::nextImage()
{
    currentIndex = (currentIndex + 1) % imagePaths.size();
    animateImage(width(), 0); // 从右侧滑出，左侧滑入
    showImage();
}

void netMusic1::nextImage1(){
    currentIndex = currentIndex;
    animateImage(0,-width());
    showImage();
}



void netMusic1::prevImage()
{
    currentIndex = (currentIndex - 1 + imagePaths.size()) % imagePaths.size();
    animateImage(-width(), 0); // 从左侧滑出，右侧滑入
    showImage();
}

