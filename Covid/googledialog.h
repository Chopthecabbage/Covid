#ifndef GOOGLEDIALOG_H
#define GOOGLEDIALOG_H

#include <QDialog>
#include "point.h"
#include "location.h"
#include "google.h"

namespace Ui {
class GoogleDialog;
}

class GoogleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoogleDialog(QWidget *parent = nullptr);
    ~GoogleDialog();
    void TakeOverSock(QTcpSocket *);
    void SendSignalAndPoint();
    void RecvLocation();
    void ArrangList();
    virtual bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_pushButton_clicked();
    void reply_finished(QNetworkReply*);
    //
    void on_QWebBtn_clicked();
    void on_QDeskBtn_clicked();
    void on_BackBtn_clicked();

private:
    Ui::GoogleDialog *ui;
    //
    QTcpSocket *sock;
    //
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;
    //
    double lat;
    double lng;
    //
    Point p;
    Location l[10];
    int l_cnt;
    int signal;
    //
    Google g;
    //
    void _handleWhatsThisEntry(QWidget * /*sender*/);
};

#endif // GOOGLEDIALOG_H
