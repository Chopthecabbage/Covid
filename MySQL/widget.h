#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
//#include <QDebug>
#include <QTableView>
#include <QSqlTableModel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void reply_finished(QNetworkReply*);

private:
    Ui::Widget *ui;
    //QSqlTableModel *model;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;
    //
    QSqlDatabase db;
    QSqlQuery *query;
};
#endif // WIDGET_H
