#ifndef DISASTER_HANDLER_H
#define DISASTER_HANDLER_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTextBrowser>
#include "disaster_msg.h"
#include "disaster_api.h"

namespace Ui {
class Disaster_Handler;
}

class Disaster_Handler : public QDialog
{
    Q_OBJECT
private:
    Ui::Disaster_Handler *ui;
    QVector<Disaster_Msg> loc_msg; // 원하는 지역, 날짜 결과들
    QString selected_loc; // 선택한 지역이름
    QDate selected_date; // 선택한 날짜

public:
    explicit Disaster_Handler(QWidget *parent = nullptr);
    ~Disaster_Handler();
    void Get_Msg_Data(); // API호출해서 원하는 데이터 loc_msg 벡터에 넣음
    void Set_Msg_UI(); // 호출한 데이터 UI에 출력

private slots:
    void Recv_Selected_Loc(QString selected_loc); // 부모 위젯에서 지역 선택시 값 받아옴
    void on_dateEdit_userDateChanged(const QDate &date); // 날짜 변경시
};

#endif // DISASTER_HANDLER_H
