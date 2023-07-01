#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QList>
#include <QAbstractButton>

#include "musicplayer.h"
#include "netmusic.h"
#include "netmusic1.h"
#include "musplayer.h"

#pragma execution_character_set("utf-8")


QT_BEGIN_NAMESPACE
namespace Ui { class myPlayer; }
QT_END_NAMESPACE
class myPlayer : public QWidget
{
    Q_OBJECT

public:
    myPlayer(QWidget *parent = nullptr);
    ~myPlayer();

    musicPlayer * player3 = NULL;
    netMusic * netmusic = NULL;
    netMusic1 *netmusic1 = NULL;
    musPlayer *musplayer =NULL;


    QButtonGroup * bg;
    QList<QAbstractButton *> buttons;

    //QString image3;
    void SetButtonColor(QAbstractButton *btn);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::myPlayer *ui;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

    QPoint m_dragPosition;

private slots:



signals:
    //void buttonClicked(int);
};

#endif // MYPLAYER_H
