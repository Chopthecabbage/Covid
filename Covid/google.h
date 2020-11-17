#ifndef GOOGLE_H
#define GOOGLE_H

#include <QWidget>
#include "Common.h"
#include "location.h"

namespace Ui {
class Google;
}

class Google : public QWidget
{
    Q_OBJECT

public:
    explicit Google(QWidget *parent = nullptr);
    ~Google();
    void Black_Sheep_Wall(QString address, Location l, int direction);

private:
    Ui::Google *ui;
    //
    QWebEngineView *view;
};

#endif // GOOGLE_H
