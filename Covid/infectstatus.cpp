#include "infectstatus.h"
#include "ui_infectstatus.h"

InfectStatus::InfectStatus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfectStatus)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("COVID-19 확진자 현황"));
    this->setStyleSheet("background-color:white");
    // 우형섭
    sock = new QTcpSocket(this);
    QHostAddress IP("61.108.2.70");
    sock->connectToHost(IP,PORT);
    // 안민근
    connect(this, SIGNAL(Send_Selected_Loc(QString)), &disaster, SLOT(Recv_Selected_Loc(QString)));
    //
    ChartNetworkAccess();
    InfectNetworkAccess();
}

InfectStatus::~InfectStatus()
{
    delete ui;
    delete [] infectinfo;
    delete [] chartdata;
    qDebug() << QString::fromLocal8Bit("InfectStatus 소멸자");
}

void InfectStatus::InfectNetworkAccess()
{
    infectinfo=new InfectInfo[INFECTSIZE]; //시도,합계,검역- 데이터 갯수만큼 할당
    Infectlist<<"createDt"<<"deathCnt"<<"defCnt"<<"gubun"<<"incDec"<<"isolClearCnt";
    Infectlist<<"isolIngCnt"<<"localOccCnt"<<"overFlowCnt"<<"qurRate"<<"seq"<<"stdDay";
    QString url="http://openapi.data.go.kr/openapi/service/rest/Covid19/getCovid19SidoInfStateJson?serviceKey=";
    url+="Ti9P%2FIn%2F2LaQ0RVnKA8aUVlSGRfh4OxFitOj%2F0H%2FMqVUcufMQ04sicdgQDoOFuEFzOZJP5URg5JVV8aXe%2Fk1Dw%3D%3D";
    url+="&pageNo=1&numOfRows=1";
    url+="&startCreateDt="+QDate::currentDate().toString(QString::fromUtf8("yyyyMMdd"));
    //url+="&startCreateDt=20200911";
    url+="&endCreateDt="+QDate::currentDate().toString(QString::fromUtf8("yyyyMMdd"));
    //url+="&endCreateDt=20200911";
    connect(&Infectmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(GetInfectReply(QNetworkReply*)));
    Infectmanager.get(QNetworkRequest(QUrl(url)));
}

void InfectStatus::ChartNetworkAccess()
{
    chartdata=new ChartData[CHARTSIZE];
    Chartlist<<"stateDt"<<"decideCnt"<<"clearCnt";
    QString url="http://openapi.data.go.kr/openapi/service/rest/Covid19/getCovid19InfStateJson?serviceKey=";
    url+="Ti9P%2FIn%2F2LaQ0RVnKA8aUVlSGRfh4OxFitOj%2F0H%2FMqVUcufMQ04sicdgQDoOFuEFzOZJP5URg5JVV8aXe%2Fk1Dw%3D%3D";
    url+="&pageNo=1&numOfRows=7";
    url+="&startCreateDt="+QDate::currentDate().addDays(-5).toString(QString::fromUtf8("yyyyMMdd"));
    //url+="&startCreateDt=20200906";
    url+="&endCreateDt="+QDate::currentDate().toString(QString::fromUtf8("yyyyMMdd"));
    //url+="&endCreateDt=20200911";
    qDebug() << QDate::currentDate().addDays(-5).toString(QString::fromUtf8("yyyyMMdd"));
    qDebug() << QDate::currentDate().toString(QString::fromUtf8("yyyyMMdd"));
    connect(&Chartmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(GetChartReply(QNetworkReply*)));
    Chartmanager.get(QNetworkRequest(QUrl(url)));
}

void InfectStatus::GetChartReply(QNetworkReply* reply)
{
    int cnt=0;
    QByteArray data;
    QString text;
    QDomDocument doc;
    data=reply->readAll();
    doc.setContent(data); //문서를 data로 초기화

    QDomElement root=doc.firstChildElement("response");
    QDomElement xml=root.firstChildElement("body");
    xml=xml.firstChildElement("items");
    xml=xml.firstChildElement("item");
    for(; !xml.isNull(); xml=xml.nextSiblingElement("item")) {
        QDomElement info;
        for(int i=0;i<Chartlist.count();i++)
        {
            info=xml.firstChildElement(Chartlist[i]);
            chartdata[cnt].DataInit(info.tagName(),info.text());
            qDebug()<<"Chart_tagname: "<< info.tagName();
            qDebug()<<"Chart_text: "<< info.text();
        }
        cnt++;
        qDebug()<<"cnt: "<<cnt;
    }
    SetData();
    ShowLineChart();
}

void InfectStatus::GetInfectReply(QNetworkReply*reply)
{
    int cnt=0;
    QByteArray data;
    QString text;
    QDomDocument doc;
    data=reply->readAll();
    doc.setContent(data); //문서를 data로 초기화

    QDomElement root=doc.firstChildElement("response");
    QDomElement xml=root.firstChildElement("body");
    xml=xml.firstChildElement("items");
    xml=xml.firstChildElement("item");
    for(; !xml.isNull(); xml=xml.nextSiblingElement("item")) {
        QDomElement info;
        for(int i=0;i<Infectlist.count();i++)
        {
            info=xml.firstChildElement(Infectlist[i]);
            infectinfo[cnt].InfectInfoInit(info.tagName(),info.text());
            qDebug()<<"Infect_tagname: "<< info.tagName();
            qDebug()<<"Infect_text: "<< info.text();
        }
        cnt++;
        qDebug()<<"cnt: "<<cnt;
    }
    SetBtnText();
    ShowDetailInfo(infectinfo[18]);
    ShowAllPieChart();
}

void InfectStatus::ShowDetailInfo(InfectInfo info)
{
    if(info.GetGubun()=="합계")
        ui->gubunLabel->setText("전국");
    else
        ui->gubunLabel->setText(info.GetGubun()); //시,도 이름
    ui->confirmLabel->setText(info.GetDefCNT()); //확진자 수
    ui->increaseLabel->setText("(+"+info.GetIncDec()+')'); //전일 대비 증감
    ui->isolaionLabel->setText(info.GetIsolIngCNT()); //격리중 수
    ui->releaseLabel->setText(info.GetIsolClearCNT()); //격리 해제 수
    ui->deathLabel->setText(info.GetDeathCNT()); //사망자 수
    ui->rateLabel->setText(info.GetQurRate()); //10만명당 발생률
}

void InfectStatus::SetBtnText()
{
    ui->statusbar->showMessage(QString::fromLocal8Bit("기준 일시 : ")+infectinfo[0].GetStdDay());
    ui->statusbar->setFont(QFont("새굴림", 9));
    ui->examineBtn->setText(infectinfo[0].GetGubun()+'\n'+infectinfo[0].GetDefCNT()+'\n'+"(+"+infectinfo[0].GetIncDec()+')'); //검역
    ui->jejuBtn->setText(infectinfo[1].GetGubun()+'\n'+infectinfo[1].GetDefCNT()+'\n'+"(+"+infectinfo[1].GetIncDec()+')'); //제주
    ui->gyeongnamBtn->setText(infectinfo[2].GetGubun()+'\n'+infectinfo[2].GetDefCNT()+'\n'+"(+"+infectinfo[2].GetIncDec()+')'); //경남
    ui->gyeongbukBtn->setText(infectinfo[3].GetGubun()+'\n'+infectinfo[3].GetDefCNT()+'\n'+"(+"+infectinfo[3].GetIncDec()+')'); //경북
    ui->jeonnamBtn->setText(infectinfo[4].GetGubun()+'\n'+infectinfo[4].GetDefCNT()+'\n'+"(+"+infectinfo[4].GetIncDec()+')'); //전남
    ui->jeonbukBtn->setText(infectinfo[5].GetGubun()+'\n'+infectinfo[5].GetDefCNT()+'\n'+"(+"+infectinfo[5].GetIncDec()+')'); //전북
    ui->chungnamBtn->setText(infectinfo[6].GetGubun()+'\n'+infectinfo[6].GetDefCNT()+'\n'+"(+"+infectinfo[6].GetIncDec()+')'); //충남
    ui->chungbukBtn->setText(infectinfo[7].GetGubun()+'\n'+infectinfo[7].GetDefCNT()+'\n'+"(+"+infectinfo[7].GetIncDec()+')'); //충북
    ui->gangwonBtn->setText(infectinfo[8].GetGubun()+'\n'+infectinfo[8].GetDefCNT()+'\n'+"(+"+infectinfo[8].GetIncDec()+')'); //강원
    ui->gyeonggiBtn->setText(infectinfo[9].GetGubun()+'\n'+infectinfo[9].GetDefCNT()+'\n'+"(+"+infectinfo[9].GetIncDec()+')'); //경기
    ui->sejongBtn->setText(infectinfo[10].GetGubun()+'\n'+infectinfo[10].GetDefCNT()+'\n'+"(+"+infectinfo[10].GetIncDec()+')'); //세종
    ui->ulsanBtn->setText(infectinfo[11].GetGubun()+'\n'+infectinfo[11].GetDefCNT()+'\n'+"(+"+infectinfo[11].GetIncDec()+')'); //울산
    ui->daejeonBtn->setText(infectinfo[12].GetGubun()+'\n'+infectinfo[12].GetDefCNT()+'\n'+"(+"+infectinfo[12].GetIncDec()+')'); //대전
    ui->gwangjuBtn->setText(infectinfo[13].GetGubun()+'\n'+infectinfo[13].GetDefCNT()+'\n'+"(+"+infectinfo[13].GetIncDec()+')'); //광주
    ui->incheonBtn->setText(infectinfo[14].GetGubun()+'\n'+infectinfo[14].GetDefCNT()+'\n'+"(+"+infectinfo[14].GetIncDec()+')'); //인천
    ui->daeguBtn->setText(infectinfo[15].GetGubun()+'\n'+infectinfo[15].GetDefCNT()+'\n'+"(+"+infectinfo[15].GetIncDec()+')'); //대구
    ui->busanBtn->setText(infectinfo[16].GetGubun()+'\n'+infectinfo[16].GetDefCNT()+'\n'+"(+"+infectinfo[16].GetIncDec()+')'); //부산
    ui->seoulBtn->setText(infectinfo[17].GetGubun()+'\n'+infectinfo[17].GetDefCNT()+'\n'+"(+"+infectinfo[17].GetIncDec()+')'); //서울
}

void InfectStatus::SetData()
{
    for(int i=0;i<CHARTSIZE;i++)
    {
        chartdata[i].SetStateDT(chartdata[i].GetStateDT().remove(0,4));
        qDebug() << chartdata[i].GetStateDT();
        if(i!=5)
        {
            chartdata[i].SetDaydecide(chartdata[i].GetDecideCNT().toInt()-chartdata[i+1].GetDecideCNT().toInt());
            chartdata[i].SetDayclear(chartdata[i].GetClearCNT().toInt()-chartdata[i+1].GetClearCNT().toInt());
            qDebug() <<chartdata[i].GetDaydecide();
            qDebug() <<chartdata[i].GetDayclear();
        }
    }
}

void InfectStatus::ShowLineChart()
{
    QSplineSeries *lineseries = new QSplineSeries();
    lineseries->setName(QString::fromLocal8Bit("확진"));
    lineseries->append(QPoint(0, chartdata[4].GetDaydecide()));
    lineseries->append(QPoint(1, chartdata[3].GetDaydecide()));
    lineseries->append(QPoint(2, chartdata[2].GetDaydecide()));
    lineseries->append(QPoint(3, chartdata[1].GetDaydecide()));
    lineseries->append(QPoint(4, chartdata[0].GetDaydecide()));

    QSplineSeries *lineseries1 = new QSplineSeries();
    lineseries1->setName(QString::fromLocal8Bit("완치"));
    lineseries1->append(QPoint(0, chartdata[4].GetDayclear()));
    lineseries1->append(QPoint(1, chartdata[3].GetDayclear()));
    lineseries1->append(QPoint(2, chartdata[2].GetDayclear()));
    lineseries1->append(QPoint(3, chartdata[1].GetDayclear()));
    lineseries1->append(QPoint(4, chartdata[0].GetDayclear()));

    chart = new QChart();
    chart->addSeries(lineseries);
    chart->addSeries(lineseries1);
    chart->setTitle(QString::fromLocal8Bit("최근 5일간 확진 및 완치 현황 그래프"));

    QStringList categories;
    categories << chartdata[4].GetStateDT() << chartdata[3].GetStateDT() << chartdata[2].GetStateDT() << chartdata[1].GetStateDT() << chartdata[0].GetStateDT();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    lineseries->attachAxis(axisX);
    lineseries1->attachAxis(axisX);
    axisX->setRange(chartdata[4].GetStateDT(), chartdata[0].GetStateDT());

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisY);
    lineseries1->attachAxis(axisY);
    axisY->setRange(0, 500);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->resize(600,300);
    ui->chartgraphicsView->setChart(chart);
    ui->chartgraphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
}

void InfectStatus::ShowPieChart(InfectInfo info)
{
    QPieSeries *series=new QPieSeries();
    series->setPieSize(0.3);
    //
    series->append(info.GetGubun(),info.GetDefCNT().toInt());
    qDebug() << QString::fromLocal8Bit("info: ")<<info.GetDefCNT().toInt();
    series->append(info.GetGubun(),infectinfo[18].GetDefCNT().toInt());
    qDebug() << QString::fromLocal8Bit("infectinfo: ")<<infectinfo[18].GetDefCNT().toInt();

    QPieSlice *slice=series->slices().at(0);
    slice->setLabel(QString("%1 %2%").arg(slice->label()).arg(100*slice->percentage(), 0, 'f', 2)); //확률 구하기
    slice->setLabelVisible();
    slice->setExploded();
    slice->setPen(QPen(Qt::darkBlue,2));
    slice->setBrush(Qt::darkBlue);

    QPieSlice *slice1=series->slices().at(1);
    slice1->setBrush(Qt::lightGray);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromLocal8Bit("전국대비 확진자 비율"));
    chart->legend()->hide();
    ui->PiegraphicsView->setChart(chart);
    ui->PiegraphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
}

void InfectStatus::ShowAllPieChart()
{
    QPieSeries *series=new QPieSeries();
    int etc=0;
    vector<pair<int,string>> count;

    for(int i=0;i<INFECTSIZE-1;i++)
    {
        count.push_back(pair<int,string>(infectinfo[i].GetDefCNT().toInt(),infectinfo[i].GetGubun().toStdString()));
    }
    sort(count.begin(),count.end(),greater<>());
    for(int i=4;i<INFECTSIZE-1;i++)
    {
        etc+=count[i].first;
    }
    for(int i=0;i<5;i++)
    {
        if(i<4)
        {
            QString temp=QString::fromUtf8(count[i].second.c_str());
            series->append(temp,count[i].first);
        }
        else
            series->append(QString::fromLocal8Bit("기타"),etc);
    }
    series->setLabelsVisible();
    series->setPieSize(0.3);
    //
    for(auto slice : series->slices())
        slice->setLabel(QString("%1 %2%").arg(slice->label()).arg(100*slice->percentage(), 0, 'f', 1));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromLocal8Bit("전국 확진자 비율"));
    chart->legend()->hide();
    ui->PiegraphicsView->setChart(chart);
    ui->PiegraphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
}
/*
QString select_loc =  "지역명";
emit Send_Selected_Loc(select_loc);

"강원도";
"경기도";
"경상남도";
"경상북도";
"광주광역시";
"대구광역시";
"대전광역시";
"부산광역시";
"서울특별시";
"울산광역시";
"인천광역시";
"전라남도";
"전라북도";
"제주특별자치도";
"충청남도";
"충청북도";
"세종특별자치시";
*/
void InfectStatus::on_incheonBtn_clicked() //인천 버튼 클릭
{
    ShowDetailInfo(infectinfo[14]);
    ShowPieChart(infectinfo[14]);
    QString select_loc = QString::fromLocal8Bit("인천광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_seoulBtn_clicked() //서울 버튼 클릭
{
    ShowDetailInfo(infectinfo[17]);
    ShowPieChart(infectinfo[17]);
    QString select_loc = QString::fromLocal8Bit("서울특별시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_gyeonggiBtn_clicked() //경기 버튼 클릭
{
    ShowDetailInfo(infectinfo[9]);
    ShowPieChart(infectinfo[9]);
    QString select_loc = QString::fromLocal8Bit("경기도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_gangwonBtn_clicked() //강원 버튼 클릭
{
    ShowDetailInfo(infectinfo[8]);
    ShowPieChart(infectinfo[8]);
    QString select_loc = QString::fromLocal8Bit("강원도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_sejongBtn_clicked() //세종 버튼 클릭
{
    ShowDetailInfo(infectinfo[10]);
    ShowPieChart(infectinfo[10]);
    QString select_loc = QString::fromLocal8Bit("세종특별자치시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_chungbukBtn_clicked() //충북 버튼 클릭
{
    ShowDetailInfo(infectinfo[7]);
    ShowPieChart(infectinfo[7]);
    QString select_loc = QString::fromLocal8Bit("충청북도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_chungnamBtn_clicked() //충남 버튼 클릭
{
    ShowDetailInfo(infectinfo[6]);
    ShowPieChart(infectinfo[6]);
    QString select_loc = QString::fromLocal8Bit("충청남도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_daejeonBtn_clicked() //대전 버튼 클릭
{
    ShowDetailInfo(infectinfo[12]);
    ShowPieChart(infectinfo[12]);
    QString select_loc = QString::fromLocal8Bit("대전광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_gyeongbukBtn_clicked() //경북 버튼 클릭
{
    ShowDetailInfo(infectinfo[3]);
    ShowPieChart(infectinfo[3]);
    QString select_loc = QString::fromLocal8Bit("경상북도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_jeonbukBtn_clicked() //전북 버튼 클릭
{
    ShowDetailInfo(infectinfo[5]);
    ShowPieChart(infectinfo[5]);
    QString select_loc = QString::fromLocal8Bit("전라북도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_daeguBtn_clicked() //대구 버튼 클릭
{
    ShowDetailInfo(infectinfo[15]);
    ShowPieChart(infectinfo[15]);
    QString select_loc = QString::fromLocal8Bit("대구광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_gwangjuBtn_clicked() //광주 버튼 클릭
{
    ShowDetailInfo(infectinfo[13]);
    ShowPieChart(infectinfo[13]);
    QString select_loc = QString::fromLocal8Bit("광주광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_jeonnamBtn_clicked() //전남 버튼 클릭
{
    ShowDetailInfo(infectinfo[4]);
    ShowPieChart(infectinfo[4]);
    QString select_loc = QString::fromLocal8Bit("전라남도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_gyeongnamBtn_clicked() //경남 버튼 클릭
{
    ShowDetailInfo(infectinfo[2]);
    ShowPieChart(infectinfo[2]);
    QString select_loc = QString::fromLocal8Bit("경상남도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_ulsanBtn_clicked() //울산 버튼 클릭
{
    ShowDetailInfo(infectinfo[11]);
    ShowPieChart(infectinfo[11]);
    QString select_loc = QString::fromLocal8Bit("울산광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_busanBtn_clicked() //부산 버튼 클릭
{
    ShowDetailInfo(infectinfo[16]);
    ShowPieChart(infectinfo[16]);
    QString select_loc = QString::fromLocal8Bit("부산광역시");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_jejuBtn_clicked() //제주 버튼 클릭
{
    ShowDetailInfo(infectinfo[1]);
    ShowPieChart(infectinfo[1]);
    QString select_loc = QString::fromLocal8Bit("제주특별자치도");
    emit Send_Selected_Loc(select_loc);
}

void InfectStatus::on_examineBtn_clicked() //검역 버튼 클릭
{
    ShowDetailInfo(infectinfo[0]);
    ShowPieChart(infectinfo[0]);
}

void InfectStatus::on_totalBtn_clicked() //전국 버튼 클릭
{
    ShowDetailInfo(infectinfo[18]);
    ShowAllPieChart();
}

void InfectStatus::on_GoogleBtn_clicked()
{
    googledialog = new GoogleDialog(this);
    googledialog->setFixedSize(561,700);
    googledialog->TakeOverSock(sock);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::darkCyan);
    googledialog->setAutoFillBackground(true);
    googledialog->setPalette(pal);

    googledialog->show();
    //googledialog->exec();
}

void InfectStatus::on_DisasterBtn_clicked()
{
    disaster.show();
}
