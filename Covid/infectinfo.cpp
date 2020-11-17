#include "infectinfo.h"

InfectInfo::InfectInfo()
{}
InfectInfo::InfectInfo(QString createDT,QString deathCNT,QString defCNT,QString gubun,QString incDEC,QString isolclearCNT,QString isolingCNT,QString localoccCNT,QString overflowCNT,QString qurrate,QString seq,QString stdday)
{
    Create_DT=createDT;
    Death_CNT=deathCNT;
    Def_CNT=defCNT;
    Gubun=gubun;
    Inc_DEC=incDEC;
    Isol_Clear_CNT=isolclearCNT;
    Isol_Ing_CNT=isolingCNT;
    Local_Occ_CNT=localoccCNT;
    Over_Flow_CNT=overflowCNT;
    Qur_Rate=qurrate;
    Seq=seq;
    Std_Day=stdday;
}
InfectInfo::~InfectInfo() {}
void InfectInfo::InfectInfoInit(QString createDT,QString deathCNT,QString defCNT,QString gubun,QString incDEC,QString isolclearCNT,QString isolingCNT,QString localoccCNT,QString overflowCNT,QString qurrate,QString seq,QString stdday)
{
    Create_DT=createDT;
    Death_CNT=deathCNT;
    Def_CNT=defCNT;
    Gubun=gubun;
    Inc_DEC=incDEC;
    Isol_Clear_CNT=isolclearCNT;
    Isol_Ing_CNT=isolingCNT;
    Local_Occ_CNT=localoccCNT;
    Over_Flow_CNT=overflowCNT;
    Qur_Rate=qurrate;
    Seq=seq;
    Std_Day=stdday;
}
void InfectInfo::InfectInfoInit(QString tagname, QString text)
{
    if(tagname=="createDt")
        Create_DT=text;
    else if(tagname=="deathCnt")
        Death_CNT=text;
    else if(tagname=="defCnt")
        Def_CNT=text;
    else if(tagname=="gubun")
        Gubun=text;
    else if(tagname=="incDec")
        Inc_DEC=text;
    else if(tagname=="isolClearCnt")
        Isol_Clear_CNT=text;
    else if(tagname=="isolIngCnt")
        Isol_Ing_CNT=text;
    else if(tagname=="localOccCnt")
        Local_Occ_CNT=text;
    else if(tagname=="overFlowCnt")
        Over_Flow_CNT=text;
    else if(tagname=="qurRate")
        Qur_Rate=text;
    else if(tagname=="seq")
        Seq=text;
    else if(tagname=="stdDay")
        Std_Day=text;
}
//GET
QString InfectInfo::GetCreatDT() const
{
    return Create_DT;
}
QString InfectInfo::GetDeathCNT() const
{
    return Death_CNT;
}
QString InfectInfo::GetDefCNT() const
{
    return Def_CNT;
}
QString InfectInfo::GetGubun() const
{
    return Gubun;
}
QString InfectInfo::GetIncDec() const
{
    return Inc_DEC;
}
QString InfectInfo::GetIsolClearCNT() const
{
    return Isol_Clear_CNT;
}
QString InfectInfo::GetIsolIngCNT() const
{
    return Isol_Ing_CNT;
}
QString InfectInfo::GetLoclOccCNT() const
{
    return Local_Occ_CNT;
}
QString InfectInfo::GetOverFlowCNT() const
{
    return Over_Flow_CNT;
}
QString InfectInfo::GetQurRate() const
{
    return Qur_Rate;
}
QString InfectInfo::GetSeq() const
{
    return Seq;
}
QString InfectInfo::GetStdDay() const
{
    return Std_Day;
}

//SET
void InfectInfo::SetCreatDT(const QString createDT)
{
    Create_DT=createDT;
}
void InfectInfo::SetDeathCNT(const QString deathCNT)
{
    Death_CNT=deathCNT;
}
void InfectInfo::SetDefCNT(const QString defCNT)
{
    Def_CNT=defCNT;
}
void InfectInfo::SetGubun(const QString gubun)
{
    Gubun=gubun;
}
void InfectInfo::SetIncDec(const QString incDEC)
{
    Inc_DEC=incDEC;
}
void InfectInfo::SetIsolClearCNT(const QString isolclearCNT)
{
    Isol_Clear_CNT=isolclearCNT;
}
void InfectInfo::SetIsolIngCNT(const QString isolingCNT)
{
    Isol_Ing_CNT=isolingCNT;
}
void InfectInfo::SetLoclOccCNT(const QString localoccCNT)
{
    Local_Occ_CNT=localoccCNT;
}
void InfectInfo::SetOverFlowCNT(const QString overflowCNT)
{
    Over_Flow_CNT=overflowCNT;
}
void InfectInfo::SetQurRate(const QString qurrate)
{
    Qur_Rate=qurrate;
}
void InfectInfo::SetSeq(const QString seq)
{
    Seq=seq;
}
void InfectInfo::SetStdDay(const QString stdday)
{
    Std_Day=stdday;
}
