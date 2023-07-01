#include "myplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myPlayer w;
    w.show();
    return a.exec();
}
