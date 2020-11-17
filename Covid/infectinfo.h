#ifndef INFECTINFO_H
#define INFECTINFO_H
#include "Common.h"

class InfectInfo
{
private:
    QString Create_DT; //등록일시분초
    QString Death_CNT; //사망자 수
    QString Def_CNT; //확진자 수
    QString Gubun; //시도명
    QString Inc_DEC; //전일대비 증감수
    QString Isol_Clear_CNT; //격리 해제 수
    QString Isol_Ing_CNT; //격리중 환자수
    QString Local_Occ_CNT; //지역발생 수
    QString Over_Flow_CNT; //해외유입 수
    QString Qur_Rate; //10만명당 발생률
    QString Seq; //게시글번호
    QString Std_Day; //기준일시
public:
    InfectInfo();
    InfectInfo(QString createDT,QString deathCNT,QString defCNT,QString gubun,QString incDEC,QString isolclearCNT,QString isolingCNT,QString localoccCNT,QString overflowCNT,QString qurrate,QString seq,QString stdday);
    ~InfectInfo();
    void InfectInfoInit(QString createDT,QString deathCNT,QString defCNT,QString gubun,QString incDEC,QString isolclearCNT,QString isolingCNT,QString localoccCNT,QString overflowCNT,QString qurrate,QString seq,QString stdday);
    void InfectInfoInit(QString tagname,QString text);
    //GET
    QString GetCreatDT() const;
    QString GetDeathCNT() const;
    QString GetDefCNT() const;
    QString GetGubun() const;
    QString GetIncDec() const;
    QString GetIsolClearCNT() const;
    QString GetIsolIngCNT() const;
    QString GetLoclOccCNT() const;
    QString GetOverFlowCNT() const;
    QString GetQurRate() const;
    QString GetSeq() const;
    QString GetStdDay() const;

    //SET
    void SetCreatDT(const QString createDT);
    void SetDeathCNT(const QString deathCNT);
    void SetDefCNT(const QString defCNT);
    void SetGubun(const QString gubun);
    void SetIncDec(const QString incDEC);
    void SetIsolClearCNT(const QString isolclearCNT);
    void SetIsolIngCNT(const QString isolingCNT);
    void SetLoclOccCNT(const QString localoccCNT);
    void SetOverFlowCNT(const QString overflowCNT);
    void SetQurRate(const QString qurrate);
    void SetSeq(const QString seq);
    void SetStdDay(const QString stdday);

};

#endif // INFECTINFO_H
