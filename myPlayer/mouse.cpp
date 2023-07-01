#include "mouse.h"
#include <QDebug>
#include <QMouseEvent>
#include <QStyle>
#include <QRadioButton>
#include <QCursor>
#include <QSize>

#pragma execution_character_set("utf-8")
Mouse::Mouse(QWidget *parent) : QWidget(parent),currentButton(nullptr)
{
    setMouseTracking(true);
}

void Mouse::setButton(QPushButton *btn, const QString &img1, const QString &img2, const QString &img3)
{
    button = btn;
    image1 = img1;
    image2 = img2;
    image3 = img3;

    //button->setProperty("state", false);
    button->setIcon(QIcon(image1));
    QPixmap pixmap(img3);
    //QPixmap pixmap = QPixmap(image1);
    // 获取图像的大小
    button->setIconSize(pixmap.size());
    //button->setIconSize(QSize(300,50));
    qDebug()<<pixmap.size();
    button->setStyleSheet("QPushButton { border: none; }");
    button->installEventFilter(this);
    connect(button,&QPushButton::clicked,[=](){
        isSelected = true;
    });
}

//void Mouse::setRadioButton(QPushButton *button, const QString &image1, const QString &image2, const QString &image3)
//{
//    button->installEventFilter(this);
//    button->setProperty("image1", image1);
//    button->setProperty("image2", image2);
//    button->setProperty("image3", image3);
//}

void Mouse::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (button->property("state").toBool())
        {
            button->setProperty("state", false);
            button->setIcon(QIcon(image2));
            qDebug() << "Button state changed to 1";
        }
        else
        {
            button->setProperty("state", true);
            button->setIcon(QIcon(image3));
            qDebug() << "Button state changed to 2";
        }

        button->style()->unpolish(button);
        button->style()->polish(button);
    }
}

//设置鼠标进入离开
bool Mouse::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == button)
    {
        if (event->type() == QEvent::Enter )
        {
            isSelected = false;
            button->setIcon(QIcon(image2));
            qDebug() << "鼠标进入了按钮";
            QCursor cursor(Qt::PointingHandCursor);
            button->setCursor(cursor);
        }

        else if (event->type() == QEvent::Leave && !isSelected)
        {
            if (!button->property("state").toBool())
            {

                button->setIcon(QIcon(image1));

                qDebug()<<"变成第一张图";
            }
            qDebug() << "鼠标离开了按钮";
            //isSelected = false;
        }
        connect(button,&QPushButton::clicked,[=](){
            button->setIcon(QIcon(image3));
        });
//        else if (event->type() == QEvent::MouseButtonPress)
//        {
//            isSelected = true;
//        }
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//            if (mouseEvent->button() == Qt::LeftButton)
//            {
//                isSelected = true;
//                if (isSelected && (button->icon().isNull() || button->icon().pixmap(button->iconSize()).toImage() == QImage(image2)))
//                {
//                    button->setIcon(QIcon(image3));
//                    qDebug() << "切换成第3状态";
//                }
//                else
//                {
//                    button->setIcon(QIcon(image2));
//                    qDebug() << "切换成第2状态";
//                    isSelected = false;
//                }
//            }
//        }
    }
    return false;
}


