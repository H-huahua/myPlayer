#ifndef NETMUSIC_H
#define NETMUSIC_H

#include <QWidget>
#include "netmusic.h"
#include "netmusic1.h"

namespace Ui {
class netMusic;
}

class netMusic : public QWidget
{
    Q_OBJECT

public:
    explicit netMusic(QWidget *parent = nullptr);
    ~netMusic();

    netMusic1 *netmu1 = NULL;

private:
    Ui::netMusic *ui;
};

#endif // NETMUSIC_H
