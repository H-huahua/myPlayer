#include "netmusic.h"
#include "ui_netmusic.h"
#include "mouse.h"
#include "netmusic1.h"

#include <QStackedWidget>

#pragma execution_character_set("utf-8")

netMusic::netMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::netMusic)
{
    ui->setupUi(this);
    //setFixedSize(1280,950);
    ui->groupBox->setStyleSheet("QGroupBox { border: none; }");

    Mouse *jingxuan = new Mouse;
    Mouse *guangchang = new Mouse;
    Mouse *paihang = new Mouse;
    Mouse *singer = new Mouse;
    Mouse *vip = new Mouse;

    jingxuan->setButton(ui->jingxuan,":/image/netMusic/jingxuan1",":/image/netMusic/jingxuan2",":/image/netMusic/jingxuan2");
    guangchang->setButton(ui->guangchang,":/image/netMusic/guangchang1",":/image/netMusic/guangchang2",":/image/netMusic/guangchang2");
    paihang->setButton(ui->paihang,":/image/netMusic/paihang1.JPG",":/image/netMusic/paihang2.JPG",":/image/netMusic/paihang2.JPG");
    singer->setButton(ui->singer,":/image/netMusic/singer1.JPG",":/image/netMusic/singer2.JPG",":/image/netMusic/singer2.JPG");
    vip->setButton(ui->vip,":/image/netMusic/vip1",":/image/netMusic/vip2",":/image/netMusic/vip2");


    QStackedWidget *stackedWidget2 = new QStackedWidget(this);
    stackedWidget2->setFixedSize(1280,950);
    stackedWidget2->move(0,50);
    stackedWidget2->setStyleSheet("background-color: rgb(247, 249, 252);");

    netmu1 = new netMusic1;
    stackedWidget2->addWidget(netmu1);
    //stackedWidget2->addWidget(ui->);

    connect(ui->jingxuan,&QPushButton::clicked,[=](){
        stackedWidget2->setCurrentWidget(netmu1);
    });

}

netMusic::~netMusic()
{
    delete ui;
}
