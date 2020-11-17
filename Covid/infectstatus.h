#ifndef INFECTSTATUS_H
#define INFECTSTATUS_H

#include "Common.h"
#include "infectinfo.h"
#include "chartdata.h"
// ¿ìÇü¼·
#include "googledialog.h"
// ¾È¹Î±Ù
#include "disaster_handler.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class InfectStatus; }
QT_END_NAMESPACE

class InfectStatus : public QMainWindow
{
    Q_OBJECT

public:
    InfectStatus(QWidget *parent = nullptr);
    ~InfectStatus();
    void SetBtnText();
    void ShowDetailInfo(InfectInfo info);
    void InfectNetworkAccess();
    void ChartNetworkAccess();
    void SetData();
    void ShowLineChart();
    void ShowPieChart(InfectInfo info);
    void ShowAllPieChart();
private slots:
    void GetInfectReply(QNetworkReply* reply);
    void GetChartReply(QNetworkReply* reply);
    void on_incheonBtn_clicked();

    void on_seoulBtn_clicked();

    void on_gyeonggiBtn_clicked();

    void on_gangwonBtn_clicked();

    void on_sejongBtn_clicked();

    void on_chungbukBtn_clicked();

    void on_chungnamBtn_clicked();

    void on_daejeonBtn_clicked();

    void on_gyeongbukBtn_clicked();

    void on_jeonbukBtn_clicked();

    void on_daeguBtn_clicked();

    void on_gwangjuBtn_clicked();

    void on_jeonnamBtn_clicked();

    void on_gyeongnamBtn_clicked();

    void on_ulsanBtn_clicked();

    void on_busanBtn_clicked();

    void on_jejuBtn_clicked();

    void on_examineBtn_clicked();

    void on_totalBtn_clicked();

    void on_GoogleBtn_clicked();

    void on_DisasterBtn_clicked();

private:
    Ui::InfectStatus *ui;
    QNetworkAccessManager Infectmanager;
    QNetworkAccessManager Chartmanager;
    QStringList Infectlist;
    QStringList Chartlist;
    InfectInfo *infectinfo;
    ChartData *chartdata;
    QChart *chart;
    // ¿ìÇü¼·
    QTcpSocket *sock;
    GoogleDialog *googledialog;
    // ¾È¹Î±Ù
    Disaster_Handler disaster;

signals:
    void Send_Selected_Loc(QString);

};
#endif // INFECTSTATUS_H
