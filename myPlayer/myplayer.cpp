#include "myplayer.h"
#include "ui_myplayer.h"
#include "mouse.h"
#include "musicplayer.h"
#include "netmusic.h"
#include "netmusic1.h"
#include "musplayer.h"

#include <QPainter>
#include <QObject>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDebug>
#include <QButtonGroup>
#include <QPalette>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include <QMouseEvent>
#include <QStackedWidget>
//#include <QOverload>


#pragma execution_character_set("utf-8")
myPlayer::myPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myPlayer)
{
    ui->setupUi(this);
    //ui->lblleft

    // 创建背景颜色
    QColor leftColor(240, 243, 246);  // 使用 RGB 值设置颜色，这里为红色
    QColor rightColor(247,249,252);

    // 创建调色板，并将背景颜色设置为调色板的 Window 属性
    QPalette palette1;
    QPalette palette2;

    palette1.setColor(QPalette::Window, leftColor);
    palette2.setColor(QPalette::Window, rightColor);

    // 应用调色板到 QLabel
    ui->lblleft->setAutoFillBackground(true);
    ui->lblright->setAutoFillBackground(true);
    ui->lblleft->setPalette(palette1);
    ui->lblright->setPalette(palette2);

    //ui->lblNameImage->setPixmap(QPixmap(":/image/name.png"));

    //ui->lblNameImage->setPixmap(QPixmap(":/image/name.png"));



    //ui->btnName->setFixedSize(250, 100);  // 设置按钮的固定大小


    //创建图标
    //QPixmap pixmap = QPixmap(":/image/name.png");
    ui->btnName->setIcon(QPixmap(":/image/name2.png"));
    ui->btnName->setIconSize(QSize(315,132));
    QPainter p(ui->btnName);
    p.setRenderHint(QPainter::Antialiasing);


    setWindowIcon(QIcon(":/image/Icon.png"));
    setWindowTitle("华华做的网易云音乐");
    //setFixedSize(1586,1128);
    setWindowFlags(Qt::FramelessWindowHint);

    // 创建3个QRadioButton对象
//    button1 = new QRadioButton();
//    button2 = new QRadioButton();
//    button3 = new QRadioButton();


    button1 = new QPushButton();
    button2 = new QPushButton();
    button3 = new QPushButton();
//    button1->setStyleSheet("border-image:url(:/timg.jpg)");
//    button2->setStyleSheet("border-image:url(:/timg.jpg)");
//    button3->setStyleSheet("border-image:url(:/timg.jpg)");

    // 创建Mouse类对象
    //我喜欢的音乐 最近播放 下载管理（无语无语） 本地音乐
    Mouse *myLikeMusic = new Mouse(this);
    Mouse *recentlyPlayed = new Mouse(this);
    Mouse *localMusic = new Mouse(this);

    //云音乐 播客 社区
    Mouse *netMusic_ = new Mouse(this);
    Mouse *boke = new Mouse(this);
    Mouse *community = new Mouse(this);

    //返回 搜索
    Mouse *back = new Mouse(this);
    Mouse *research = new Mouse(this);

    //右上角6个图标
    Mouse *Msg = new Mouse(this);
    Mouse *setting = new Mouse(this);
    Mouse *setStyle = new Mouse(this);
    Mouse *setmin = new Mouse(this);
    Mouse *setmax = new Mouse(this);
    Mouse *setClose = new Mouse(this);

    // 设置按钮的图片和鼠标事件
    myLikeMusic->setButton(ui->Button1, ":/image/myLikeMusic1", ":/image/myLikeMusic2", ":/image/myLikeMusic3");
    recentlyPlayed->setButton(button2, ":/image/recentlyPlayed1", ":/image/recentlyPlayed2", ":/image/recentlyPlayed3");
    localMusic->setButton(button3, ":/image/localMusic1.png", ":/image/localMusic2.png", ":/image/localMusic3.png");

    netMusic_->setButton(ui->btnNetMusic,":/image/netMusic1.png",":/image/netMusic2.png",":/image/netMusic3.png");
    boke->setButton(ui->btnBoke,":/image/boke1.png",":/image/boke2.png",":/image/boke3.png"); 
    community->setButton(ui->btnCommunity,":/image/community1.png",":/image/community2.png",":/image/community3.png");

    back->setButton(ui->btnBack,":/image/btnBack.png",":/image/btnBack_light.png",":/image/btnBack_light.png");
    research->setButton(ui->btnResearch,":/image/research2.png",":/image/research3.png",":/image/research3.png");

    ui->btnResearch2->setStyleSheet("border-image:url(:/timg.jpg)");

    Msg->setButton(ui->btnMsg,":/image/msg1.png",":/image/msg2.png",":/image/msg2.png");
    setting->setButton(ui->btnSetting,":/image/setting1.png",":/image/setting2.png",":/image/setting2.png");
    setStyle->setButton(ui->btnStyle,":/image/style1",":/image/style2",":/image/style2");
    setmin->setButton(ui->btnMin,":/image/min1",":/image/min2",":/image/min2");
    setmax->setButton(ui->btnMax,":/image/max1",":/image/max2",":/image/max2");
    setClose->setButton(ui->btnClose,":/image/close1",":/image/close2",":/image/close2");
    connect(ui->btnClose,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(ui->btnMin,&QPushButton::clicked,[=](){
        this->showMinimized();
    });
    connect(ui->btnMax,&QPushButton::clicked,[=](){
        this->showMaximized();
    });




    QVBoxLayout *layout1 = new QVBoxLayout(this);  // 创建垂直布局，将当前窗口作为布局的父窗口

    layout1->addWidget(ui->Button1);  // 将左侧按钮添加到布局中
    layout1->addWidget(button2);
    layout1->addWidget(button3);


    layout1->setAlignment(Qt::AlignLeft);

    //setLayout(layout1);  // 设置窗口布局

//    QButtonGroup *buttonGroup = new QButtonGroup(this);  // 创建按钮组
//    buttonGroup->addButton(button1);  // 将单选按钮添加到按钮组
//    buttonGroup->addButton(button2);
//    buttonGroup->addButton(button3);


    buttons = QList<QAbstractButton*>();
    bg = new QButtonGroup(this);

    buttons.append(ui->Button1);
    buttons.append(button2);
    buttons.append(button3);


    bg->setExclusive(true);

    foreach (QAbstractButton *btn, buttons) {
        btn->setEnabled(true);
        qDebug()<<"按钮设置成可选项";
    }

    int i = 0;
    foreach (QAbstractButton *btn, buttons) {
        bg->addButton(btn, i++);
        qDebug()<<"每个按钮都加入bg了";
    }

    // 创建堆叠窗口
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    stackedWidget->setFixedSize(1280,1200);
    stackedWidget->move(305,130);
    stackedWidget->setStyleSheet("background-color: rgb(247, 249, 252);");





    player3 = new musicPlayer;
    netmusic = new netMusic;
    musplayer = new musPlayer;
    //musplayer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    stackedWidget->addWidget(netmusic);
    stackedWidget->addWidget(player3);
    stackedWidget->addWidget(musplayer);

//    ui->widMusplayer->addWidget(musplayer);

//    ui->widMusplayer->setCurrentIndex(0);





    //stackedWidget->addWidget(player3);
    //stackedWidget->addWidget(netmusic);



    //connect(bg, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,&myPlayer::SetButtonColor);



    //创建云音乐精选界面：
    connect(ui->btnNetMusic,&QPushButton::clicked,[=](){
        // 加载要嵌入的界面
        //stackedWidget->setCurrentWidget(netmusic);
        stackedWidget->move(305,130);
        stackedWidget->setCurrentIndex(0);

    });

    //创建绘制音乐的场景
    connect(button3,&QPushButton::clicked,[=](){
        //button3->setIcon(QIcon(":/image/localMusic3"));
        //stackedWidget->setCurrentIndex(1);
        stackedWidget->setCurrentIndex(2);
        //stackedWidget->move(305,1000);

    });
}


myPlayer::~myPlayer()
{
    delete ui;
}

void myPlayer::SetButtonColor(QAbstractButton *btn)
{
    foreach (QAbstractButton *button, buttons) {
        Mouse mouse;
        bool isSelected = mouse.isSelected;
        if(bg->id(btn) == buttons.indexOf(button)){
            //button->setIcon(QIcon(":/image/localMusic3.png"));
            button->setStyleSheet("background-color: rgb(239, 41, 41);");
            isSelected = true;
        }
        else
            button->setStyleSheet("background-color: rgb(238, 238, 236);");
    }
}


// 鼠标按下事件
void myPlayer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录当前鼠标位置和窗口位置
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

// 鼠标移动事件
void myPlayer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // 移动窗口到当前鼠标位置
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}
