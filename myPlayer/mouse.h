#ifndef MOUSE_H
#define MOUSE_H


#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include<QRadioButton>
#include <QButtonGroup>
#include <QList>
#include <QAbstractButton>
#include <QPushButton>

#pragma execution_character_set("utf-8")
class Mouse : public QWidget
{
    Q_OBJECT
public:
    explicit Mouse(QWidget *parent = nullptr);


    void setButton(QPushButton *btn, const QString &img1, const QString &img2, const QString &img3);
    bool isSelected = false;

    //void setRadioButton (QPushButton *button; *button,const QString &image1, const QString &image2, const QString &originalImage);


    QButtonGroup *bg;
    QList<QAbstractButton *> buttons;
    //void handleRadioButtonClicked();
    QPushButton *button;

    QString image1;
    QString image2;
    QString image3;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;



private:
    QString originalImage;
    QRadioButton *currentButton;

public slots:

signals:
};

#endif // MOUSE_H
