
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtWidgets>
#include <QPushButton>
#include <QFontDatabase>
#include <QStringList>
#include <QTextEdit>
#include <QStringList>
#include <QColor>
#include <QColorDialog>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(900,600);
    //设置标题
    setWindowTitle("华华编写的绘图窗口");
    pix=QPixmap(this->width(),this->height());
    pix.fill(Qt::white);
    isDrawing=false;
    isChange=false;
    originalWidth=this->width();
    originalHeight=this->height();

    // 创建 textEdit 框，并将其存储在 textEdits 容器中

    connect(ui->actionExit,&QAction::triggered, this, &MainWindow::close);
    //字体的增大、减小、加粗、斜体
    connect(ui->decreaseBtn,&QPushButton::clicked,this,&MainWindow::decreaseFontSize);
    connect(ui->IncreaseBtn,&QPushButton::clicked,this,&MainWindow::increaseFontSize);
    connect(ui->boldBtn,&QPushButton::clicked,this,&MainWindow::toggleBold);
    connect(ui->italicBtn,&QPushButton::clicked,this,&MainWindow::toggleItalic);

    //通过点击选择线条颜色，然后触发changeColor槽函数，将颜色信息保存在currentColor中
    connect(ui->colorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeColor);

    //点击按钮控件，跳出选择框
    connect(ui->fillColorButton,&QPushButton::clicked,this,&MainWindow::chooseFillColor);


//    connect(ui->finishBtn, &QPushButton::clicked, [=](){
//        //if()
//        this->drawTextFromTextEdit();
//        delete textEdit;
//        //textEdit->hide();

//        delete ui->textEdit;
//        //textEdit = nullptr;

//        qDebug()<<"删除textEdit";
//    });

    //connect(textEdit, &QTextEdit::selectionChanged, this, &MainWindow::onTextEditClicked);
    //connect(textEdit,&QTextEdit::currentCharFormatChanged,this,&MainWindow::onTextEditSelectionChanged);
    //connect(textEdit,&QTextEdit::currentCharFormatChanged,this,&MainWindow::updateFontControls);
    //创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    //添加字体样式栏
    QFontDatabase fontDatabase;
    QMenu *menu = menuBar->addMenu("字体样式");
    QStringList fontFamilies = fontDatabase.families();
    //添加字体样式
    foreach (const QString &fontFamily, fontFamilies)
    {
        QAction *fontAction = new QAction(fontFamily, this);
        connect(fontAction, &QAction::triggered, this, &MainWindow::changeFont);
        menu->addAction(fontAction);
    }

    // 获取颜色列表
    QStringList colorNames = QColor::colorNames();
    // 添加颜色选项到组合框
    foreach (const QString &colorName, colorNames) {
        QPixmap pixmap(20, 20);
        pixmap.fill(QColor(colorName));
        ui->colorComboBox->addItem(QIcon(pixmap), colorName);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


//主要的绘制函数：
void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    //int x,y,w,h;
    x=lastPoint.x();
    y=lastPoint.y();
    w=endPoint.x()-x;
    h=endPoint.y()-y;
    QPainter painter(this);
    //绘制运动中的图形
    if(isDrawing){
        tempPix=pix;
        QPainter pp(&tempPix);
        if(ui->rectangleCheckBox->isChecked()){
            pp.setPen(currentColor);
            pp.drawRect(x,y,w,h);
        }
        if(ui->LineCheckBox->isChecked()){
            pp.setPen(currentColor);
            pp.drawLine(x,y,w+x,h+y);
        }
        if(ui->circleCheckBox->isChecked()){
            pp.setPen(currentColor);
            pp.drawEllipse(x,y,w,h);
        }
        if(ui->textCheckBox->isChecked()){
            //textEdit = new QTextEdit(this);
            textEdit = new QTextEdit(this);
            textEdit->setGeometry(x, y, w, h);
            //textEdit->show();
            //qDebug()<<"添加";

        }
        if(ui->fillCheckBox->isChecked()){
            //如果填充按钮打上勾，那么就可以进行填充：
            this->startFilling();
        }
        painter.drawPixmap(0,0,tempPix);
    }
    //绘制定格在最终的图形
    else{
        QPainter pp(&pix);
        if(ui->rectangleCheckBox->isChecked()&&isChange){
            pp.setPen(currentColor);
            pp.drawRect(x,y,w,h);
        }
        if(ui->LineCheckBox->isChecked()&&isChange){
            pp.setPen(currentColor);
            pp.drawLine(x,y,w+x,h+y);
        }
        if(ui->circleCheckBox->isChecked()&&isChange){
            pp.setPen(currentColor);
            pp.drawEllipse(x,y,w,h);
        }
        if(ui->textCheckBox->isChecked()&&isChange){
            textEdit->setGeometry(x, y, w, h);
            textEdit->show();
            //textEdits.append(textEdit);
            qDebug()<<"多添加一个框到总体";
        }
        painter.drawPixmap(0,0,pix);

    }

    if(winSizeIsChanged()){
        pix=QPixmap(this->width(),this->height());
        pix.fill(Qt::white);
        painter.drawPixmap(0,0,pix);
    }
    isChange=false;
}

bool MainWindow::winSizeIsChanged(){
    if(this->width()!=originalWidth||this->height()!=originalHeight){
        originalHeight=this->height();
        originalWidth=this->width();
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        lastPoint=event->pos();
        endPoint=lastPoint;
        isDrawing=true;//按下开始绘制，该布尔值为true
        qDebug()<<"按下了";

        if(textEdit && !textEdit->geometry().contains(event->pos())){
            qDebug()<<"点击位置不在框内，开始绘制文字";
            this->drawTextFromTextEdit();
            qDebug()<<"绘制文字结束";
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::LeftButton){
        endPoint=event->pos();
        update();
        qDebug()<<"移动了";

    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        isChange=true;//完成绘制，该布尔值为true
        endPoint=event->pos();
        isDrawing=false;//完成绘制，isDrawing的布尔值是false
        update();
        qDebug()<<"松开了";
        update();
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {

            // 当按下回车键时，更新文字并触发重绘
            text = currentText;
            qDebug()<<"已经赋给text";
            update();
            currentText.clear();
            qDebug()<<"已经清除";
        }
        else if (event->key() == Qt::Key_Backspace)
        {
            // 当按下退格键时，删除最后一个字符
            if (!currentText.isEmpty())
                currentText.chop(1);
        }
        else
        {
            // 其他键盘按键将被添加到当前文字中
            currentText += event->text();
        }
    }

void MainWindow::onTextEditSelectionChanged(){
    QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(sender());
    if(currentTextEdit){
        textEdit = currentTextEdit;
    }
}

void MainWindow::onTextEditClicked()
{
    textEdit = qobject_cast<QTextEdit*>(sender());
}

void MainWindow::changeColor(int index){
    QString colorName = ui->colorComboBox->itemText(index);
    currentColor = QColor(colorName);
}

void MainWindow::fillShape(const QPoint &startPoint)
{
    if (!pix.rect().contains(startPoint))
        return;

    QColor targetColor = pix.toImage().pixel(startPoint);
    if (targetColor == fillColor)
        return;

    QStack<QPoint> stack;
    stack.push(startPoint);

    while (!stack.isEmpty()&& pix.rect().contains(stack.top()))
    {
        QPoint point = stack.pop();
        int x = point.x();
        int y = point.y();

        if (QColor(pix.toImage().pixel(point)) != targetColor)
            continue;

        int left = x;
        int right = x;

        while (left >= 0 && QColor(pix.toImage().pixel(left, y)) == targetColor)
            --left;

        while (right < pix.width() && QColor(pix.toImage().pixel(right, y)) == targetColor)
            ++right;

        QImage image = pix.toImage();
        for (int i = left + 1; i < right; ++i)
        {
            image.setPixelColor(i, y, fillColor);
            if (y > 0 && QColor(image.pixel(i, y - 1)) == targetColor)
                stack.push(QPoint(i, y - 1));

            if (y < image.height() - 1 && QColor(image.pixel(i, y + 1)) == targetColor)
                stack.push(QPoint(i, y + 1));
        }

        pix = QPixmap::fromImage(image);
    }

    update();
}

//编写一个选择颜色的函数，让其能够弹出颜色
void MainWindow::chooseFillColor()
{
    fillColor = QColorDialog::getColor(Qt::white, this, "选择填充颜色");
}

//编写一个开始填充的槽函数，使其能够调用fillShape函数
void MainWindow::startFilling()
{
    isFilling = true;
    // 获取当前鼠标点击位置作为起始点
    startPoint = mapFromGlobal(QCursor::pos());
    // 调用 fillShape 函数进行填充
    fillShape(startPoint);
    update();
}

void MainWindow::drawText(){
    //QPainter painter(&pix);
    QPainter pp(&pix);
    pp.setPen(Qt::red);
    pp.drawText(QRect(10,20,100,50),"绘制文字");
    qDebug()<<"绘制文字了";
}


void MainWindow::drawTextFromTextEdit()
{
    QString text = textEdit->toPlainText(); // 获取textEdit框的文字
    QFont font = textEdit->currentFont(); // 获取textEdit框的当前字体样式
    QColor color = textEdit->textColor(); // 获取textEdit框的文字颜色

    // 在绘图板上绘制文字
    QPainter painter(&pix);
    painter.setFont(font);
    painter.setPen(color);
    //painter.drawText(x,y,text);
    painter.drawText(QRect(x+5,y+5,textEdit->width(),textEdit->height()),text);
    // 删除textEdit对象并将其设置为nullptr
    delete textEdit;
    textEdit = nullptr;
    qDebug() << "删除textEdit";
}

//void MainWindow::startDrawTextFromTextEdit(){
//    //QMainWindow::mousePressEvent(event);
//    if(!textEdit->geometry().contains(lastPoint)){
//        qDebug()<<"123";
//    }
//}
