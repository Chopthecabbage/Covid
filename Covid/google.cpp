#include "google.h"
#include "ui_google.h"

Google::Google(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Google)
{
    ui->setupUi(this);
    view = new QWebEngineView;
    //QNetworkProxyFactory :: setUseSystemConfiguration ( false );
}

Google::~Google()
{
    //delete ui;
    delete view;
}

void Google::Black_Sheep_Wall(QString address, Location l, int direction)
{
    if(direction==QWEB)
    {
        address.replace(" ","+");
        address.replace("_","+");
        view->load(QUrl(QString("https://www.google.com/maps/search/")+address+QString("/@%1,%2,16z").arg(l.GetLat()).arg(l.GetLng())));
        //QDesktopServices::openUrl(QString("https://www.google.com/maps/search/")+address+QString("/@%1,%2,16z").arg(l.GetLat()).arg(l.GetLng()));
        view->move(900, 0);
        view->resize(1024, 768);
        view->show();
    }
    else if(direction==QDESK)
    {
        address.replace(" ","+");
        address.replace("_","+");
        //view->load(QUrl(QString("https://www.google.com/maps/search/")+address+QString("/@%1,%2,16z").arg(l.GetLat()).arg(l.GetLng())));
        QDesktopServices::openUrl(QString("https://www.google.com/maps/search/")+address+QString("/@%1,%2,16z").arg(l.GetLat()).arg(l.GetLng()));
    }
}

