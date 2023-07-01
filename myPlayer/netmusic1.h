#ifndef NETMUSIC1_H
#define NETMUSIC1_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

namespace Ui {
class netMusic1;
}

class netMusic1 : public QWidget
{
    Q_OBJECT

public:
    explicit netMusic1(QWidget *parent = nullptr);
    ~netMusic1();

    netMusic1 *netmusic1 = NULL;

private:
    Ui::netMusic1 *ui;
    //QLabel *ui->lblLunbo;
    QStringList imagePaths;
    int currentIndex;
    QPropertyAnimation *animation;
    QTimer *timer;

private slots:
    void nextImage();
    void nextImage1();
    void prevImage();
    //void prevImage1();

    void showImage();
    void animateImage(int startX, int endX);
};

#endif // NETMUSIC1_H
