#include "chartdata.h"

ChartData::ChartData() : Daydecide(0),Dayclear(0)
{}
ChartData::~ChartData()
{}
void ChartData::DataInit(QString tagname, QString text)
{
    if(tagname=="stateDt")
        State_DT=text;
    else if(tagname=="decideCnt")
        Decide_CNT=text;
    else if(tagname=="clearCnt")
        Clear_CNT=text;
}
//GET
QString ChartData::GetStateDT() const
{
    return State_DT;
}
QString ChartData::GetDecideCNT() const
{
    return Decide_CNT;
}
QString ChartData::GetClearCNT() const
{
    return Clear_CNT;
}
int ChartData::GetDaydecide() const
{
    return Daydecide;
}
int ChartData::GetDayclear() const
{
    return Dayclear;
}

//SET
void ChartData::SetStateDT(const QString statedt)
{
    State_DT=statedt;
}
void ChartData::SetDecideCNT(const QString decidecnt)
{
    Decide_CNT=decidecnt;
}
void ChartData::SetClearCNT(const QString clearcnt)
{
    Clear_CNT=clearcnt;
}
void ChartData::SetDaydecide(const int daydecide)
{
    Daydecide=daydecide;
}
void ChartData::SetDayclear(const int dayclear)
{
    Dayclear=dayclear;
}
