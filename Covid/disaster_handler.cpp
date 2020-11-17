#include "disaster_handler.h"
#include "ui_disaster_handler.h"

Disaster_Handler::Disaster_Handler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Disaster_Handler)
{
    ui->setupUi(this);
    selected_loc = " ";
    ui->groupBox->setTitle(QString::fromLocal8Bit("긴급 재난 문자"));
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
    selected_date = ui->dateEdit->date();
}

Disaster_Handler::~Disaster_Handler()
{
    delete ui;
}

void Disaster_Handler::Recv_Selected_Loc(QString sel_loc)
{
    selected_loc = sel_loc;
    QString title = QString::fromLocal8Bit("긴급 재난 문자 ");
    title += '[';
    title += selected_loc;
    title += ']';
    ui->groupBox->setTitle(title);
    Get_Msg_Data(); // API에서 데이터 가져옴
    Set_Msg_UI(); // UI에 재난문자 출력
}

void Disaster_Handler::on_dateEdit_userDateChanged(const QDate &date)
{
     selected_date = ui->dateEdit->date();
     if(selected_loc != " ")
     {
         Get_Msg_Data(); // API에서 데이터 가져옴
         Set_Msg_UI(); // UI에 재난문자 출력
     }
}

void Disaster_Handler::Get_Msg_Data()
{
    int before_size, after_size;
    int page = 1;
    int max = 30; // api 총 데이터 약 30000개, api 한번 읽을때 1000개씩 읽음

    loc_msg.clear();
    Set_Msg_UI();
    QLabel *load = new QLabel;
    load->setText(QString::fromLocal8Bit("데이터 찾는중..."));
    load->setAlignment(Qt::AlignCenter);
    load->setStyleSheet(QString::fromUtf8("QLabel{font: bold 16pt;}"));
    ui->scrollArea->setWidget(load);

    while(max > 0)
    {
        before_size = loc_msg.size();
        Disaster_API d_api(selected_date, selected_loc, page);
        d_api.Request_API(loc_msg);
        after_size = loc_msg.size();
        page++;
        if((before_size == after_size) && after_size != 0 ) break;
        max--;
    }
}

void Disaster_Handler::Set_Msg_UI()
{
    //qDebug() << "Set_Msg_UI() Vector size : " << loc_msg.size();

    QWidget *scrollWidget = new QWidget;
    QVBoxLayout *vbox_layout = new QVBoxLayout;

    for(int i = loc_msg.size() - 1; i > 0; i--)
    {
        QHBoxLayout *hbox_layout = new QHBoxLayout;
        QTextBrowser  *m_text = new QTextBrowser;
        QTextDocument *doc = new QTextDocument(m_text);
        QLabel *time_label = new QLabel;
        QString time_text;
        QWidget *temp = new QWidget;

        // 메시지 셋팅
        doc->setHtml(loc_msg[i].Get_Msg());
        m_text->setDocument(doc);
        m_text->setFixedHeight(m_text->document()->size().height()*2.5);
        m_text->setFixedWidth(250);
        hbox_layout->addWidget(m_text);

        // 시간 셋팅
        QStringList str = loc_msg[i].Get_Time().split(':');
        if(str[0].toInt() < 12)
            time_text = QString::fromLocal8Bit("오전 ")+str[0]+":"+str[1];
        else if(str[0].toInt() == 12)
            time_text = QString::fromLocal8Bit("오후 ")+str[0]+":"+str[1];
        else
            time_text = QString::fromLocal8Bit("오후 ")+QString::number(str[0].toInt()-12)+":"+str[1];

        time_label->setText(time_text);
        time_label->setAlignment(Qt::AlignBottom);
        hbox_layout->addWidget(time_label);
        hbox_layout->setAlignment(Qt::AlignBottom);
        temp->setLayout(hbox_layout);
        vbox_layout->addWidget(temp);
    }

    if(loc_msg.size() < 5)
    {
        for(int i = 0; i < 5-loc_msg.size(); i++)
        {
            QWidget *temp_w = new QWidget;
            temp_w->setFixedHeight(85);
            vbox_layout->addWidget(temp_w);
        }
    }
    scrollWidget->setLayout(vbox_layout);
    ui->scrollArea->setWidget(scrollWidget);
    if(loc_msg.size() == 0)
    {
        QLabel *empty_result = new QLabel;
        empty_result->setText(QString::fromLocal8Bit("해당하는 데이터가 없습니다"));
        empty_result->setAlignment(Qt::AlignCenter);
        empty_result->setStyleSheet(QString::fromUtf8("QLabel{font: bold 16pt;}"));
        ui->scrollArea->setWidget(empty_result);
    }
}
