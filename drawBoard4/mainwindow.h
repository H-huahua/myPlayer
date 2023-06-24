#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>
#include <QRect>
#include <QTextEdit>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    //void paintEvent(QPaintEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    int x,y,w,h;


protected:
//    void paintEvent(QPaintEvent *){
//        QPainter painter(this);
//        painter.drawText(rect(),Qt::AlignCenter,text);
//    }

    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *) override;
private:
    Ui::MainWindow *ui;
    QPixmap pix;
    QPixmap tempPix;
    QPoint lastPoint;
    QPoint endPoint;

    QPoint onepoint;



//    QString text;
//    QString currentText;
//    QLineEdit *lineEdit;
    QString text;         // 绘制的文字
    QString currentText;  // 当前正在输入的文字
    QTextEdit *textEdit;  // 用于输入和显示文字的 QTextEdit 控件
    //QTextEdit kuang;


    QList<QTextEdit*> textEdits;
    QTextEdit* selectedTextEdit;
    //QTextEdit* textEdit;




    QColor currentColor;
    QColor fillColor;
    QPoint startPoint; // 存储起始点的坐标


    bool isDrawing;
    bool isChange;
    bool isFilling;


    int originalWidth;
    int originalHeight;


    bool winSizeIsChanged();

    void drawLine();
    void drawEllipse();
    void drawRectangle();
    void onTextEditSelectionChanged();
    //增大字体的槽函数
    void increaseFontSize()
    {
        QFont font = textEdit->currentFont();
        font.setPointSize(font.pointSize() + 1);
        textEdit->setCurrentFont(font);
    }
    //减小字体的槽函数
    void decreaseFontSize()
    {
        if(textEdit){
            QFont font = textEdit->currentFont();
            font.setPointSize(font.pointSize() - 1);
            textEdit->setCurrentFont(font);
        }
    }
    //加粗字体的槽函数
    void toggleBold()
    {
        if(textEdit){
            QFont font = textEdit->currentFont();
            font.setBold(!font.bold());
            textEdit->setCurrentFont(font);
        }
    }
    //字体斜体的槽函数
    void toggleItalic()
    {
        if(textEdit){
            QFont font = textEdit->currentFont();
            font.setItalic(!font.italic());
            textEdit->setCurrentFont(font);
        }
    }
    //添加字体样式的槽函数
    void changeFont()
        {
            QAction *action = qobject_cast<QAction *>(sender());
            if (action)
            {
//                QFont font = textEdit->currentFont();
//                font.setFamily(action->text());
//                textEdit->setCurrentFont(font);
                QString fontFamily = action->text();
                QTextCursor cursor = textEdit->textCursor();
                QTextCharFormat format;
                format.setFontFamily(fontFamily);
                cursor.mergeCharFormat(format);
                textEdit->mergeCurrentCharFormat(format);
            }
        }
    void updateFontControls();
    void onTextEditClicked();


    void changeColor(int index);
    void fillShape(const QPoint &startPoint);
    void chooseFillColor();
    void startFilling();


    void drawText();

    void drawTextFromTextEdit();

    //void startDrawTextFromTextEdit();





};

#endif // MAINWINDOW_H
