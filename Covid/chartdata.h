#ifndef CHARTDATA_H
#define CHARTDATA_H

#include "Common.h"

class ChartData
{
private:
    QString State_DT; //기준일
    QString Decide_CNT; //확진자 수
    QString Clear_CNT; //격리해제수
    int Daydecide; //일별 확진자수
    int Dayclear; //일별 격리해제 수
public:
    ChartData();
    ~ChartData();
    void DataInit(QString tagname, QString text);
    //GET
    QString GetStateDT() const;
    QString GetDecideCNT() const;
    QString GetClearCNT() const;
    int GetDaydecide() const;
    int GetDayclear() const;

    //SET
    void SetStateDT(const QString statedt);
    void SetDecideCNT(const QString decidecnt);
    void SetClearCNT(const QString clearcnt);
    void SetDaydecide(const int daydecide);
    void SetDayclear(const int dayclear);
};

#endif // CHARTDATA_H
