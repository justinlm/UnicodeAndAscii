#include "unicodeorchinese.h"
#include "ui_unicodeorchinese.h"
#include <qstring.h>
#include"YCodec.h"
#include "QDataWidgetMapper.h"

UnicodeOrChinese::UnicodeOrChinese(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnicodeOrChinese)
{
    ui->setupUi(this);
    //this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed));
    setMaximumSize(this->width(), this->height());
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);//隐藏最大化按钮
    //setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowTitleHint)

    comboxCurIndex = 0;

    ui->downTextEdit->installEventFilter(this);

    ui->UpTextEdit->installEventFilter(this);

    isUnicodeTOAscii = false;

    //    m_pMapper = new QDataWidgetMapper(this);

    //    m_pMapper->addMapping(ui->UpTextEdit, 0);

    //    connect(ui->comboBox, SIGNAL(currentIndexChanged(int))
    //            , m_pMapper, SLOT(on_UpTextEdit_textChanged()));
}

UnicodeOrChinese::~UnicodeOrChinese()
{
    delete ui;
}

void UnicodeOrChinese::on_UpTextEdit_textChanged()
{
    strUpTextedit = ui->UpTextEdit->toPlainText();

    if(strUpTextedit.length() == 0)
    {
        ui->downTextEdit->setText(strUpTextedit);
        return;
    }

    YCodec yCodec;
    QString tmp;


    if(isUnicodeTOAscii)
    {
        wchar_t *pwcharStr = NULL;
        if(comboxCurIndex == id_downText_String)
        {
            int len = strUpTextedit.length()/* * _size*/;

            if(len < 12) return;

            QString str = strUpTextedit.mid(4, len-8);
            QByteArray qb =  str.toLatin1();
            char *hexs =  qb.data();

            int wchslen = 0;
            if(yCodec.HexStr2WChars(hexs, len, 4, NULL, &wchslen) != -1)
            {
                pwcharStr = new wchar_t[wchslen +1];
                memset(pwcharStr, 0, wchslen +1);

                int n = yCodec.HexStr2WChars(hexs, len, 4, pwcharStr, &wchslen);
                if(n != -1)
                {
                    tmp = QString::fromWCharArray(pwcharStr, wchslen);
                }
            }

        }
        else
        {
             //{ 0x0077, 0x006F, 0x0000, };///
            QString str(strUpTextedit);

            if(str.length()<=0)
                return;

            for(int i = 0 ; i< str.length(); ++i)
            {
                if(str[i] == ';')
                {
                    str = str.mid(0,i);
                    break;
                }
            }

            QString a[] = {" ", "{", "}", ",", "0x",};
            int size =  sizeof(a)/sizeof(QString);
            for(int i = 0 ; i < size; ++i)
            {
                str.remove(a[i]);
            }

            str = str.mid(0, str.length()-4);

            int len = str.length();

            QByteArray qb =  str.toLatin1();
            char *hexs =  qb.data();

            int wchslen = 0;
            if(yCodec.HexStr2WChars(hexs, len, 4, NULL, &wchslen) != -1)
            {
                pwcharStr = new wchar_t[wchslen +1];
                memset(pwcharStr, 0, wchslen +1);

                int n = yCodec.HexStr2WChars(hexs, len, 4, pwcharStr, &wchslen);
                if(n != -1)
                {
                    tmp = QString::fromWCharArray(pwcharStr, wchslen);
                }
            }
        }
        if(pwcharStr) delete []pwcharStr;
        ui->downTextEdit->setText(tmp);
    }
    else
    {
        int len = strUpTextedit.length();
        wchar_t *wchs = new wchar_t[len+1];
        memset(wchs, 0, sizeof(wchar_t)*(len+1));
        strUpTextedit.toWCharArray(wchs);

        if(comboxCurIndex == id_downText_String)
        {
            tmp.append("~!--");

            // wchar_t* to hex string
            int hexlen = 0;
            if(yCodec.Wchart2HexStr(wchs, len, 4, NULL, &hexlen) != -1){
                char* hexstr = new char[hexlen+1];
                memset(hexstr, 0, hexlen+1);
                int n = yCodec.Wchart2HexStr(wchs, len, 4, hexstr, &hexlen);
                if(n != -1){
                    // char* to CString
                    char* p = hexstr;
                    for(int i=0; i<hexlen; i++)	tmp.append(*p++);
                }
                if(hexstr)	delete []hexstr;
            }

            tmp.append("~!--");
        }
        else if(comboxCurIndex == TextShowType_Array)
        {
            //{ 0x0077, 0x006F, 0x0000, };//3 = wo

            tmp.append("{ ");

            // wchar_t* to hex string
            int hexlen = 0;
            int eachchar = 4;
            if(yCodec.Wchart2HexStr(wchs, len, eachchar, NULL, &hexlen) != -1){
                char* hexstr = new char[hexlen+1];
                memset(hexstr, 0, hexlen+1);
                int n = yCodec.Wchart2HexStr(wchs, len, eachchar, hexstr, &hexlen);
                if(n != -1){
                    // char* to CString
                    char* p = hexstr;
                    for(int i=0; i<hexlen; i+=eachchar)
                    {
                        tmp.append("0x");
                        for(int j = 0 ; j < eachchar; ++j)
                        {
                            tmp.append(*p++);
                        }
                        tmp.append(", ");
                    }
                }
                if(hexstr)	delete []hexstr;
            }


            QString strLen = QString::number(len);

            tmp.append((QString)"0x0000 };" + "//" + strLen + " = " + strUpTextedit);
        }

        if(wchs)	delete []wchs;

        ui->downTextEdit->setText(tmp);
    }
}

void UnicodeOrChinese::on_comboBox_currentIndexChanged(int index)
{
    comboxCurIndex = index;

    on_UpTextEdit_textChanged();
}


bool UnicodeOrChinese::eventFilter(QObject *watched, QEvent *event)
{
    if (watched==ui->UpTextEdit)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
        {
            ui->UpTextEdit->selectAll();
        }
        else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
        {
            //ui->UpTextEdit->clear();
        }
    }
    if (watched==ui->downTextEdit)           //这里来处理 lineEdit2 , 和处理lineEdit1 是一样的
    {
        if (event->type()==QEvent::FocusIn)
        {
            ui->downTextEdit->selectAll();
        }
        else if (event->type()==QEvent::FocusOut)
        {
            //ui->downTextEdit->select(-1, 0);
        }
    }
    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}

void UnicodeOrChinese::on_reverseButton_clicked()
{
    int x =  ui->pushButton->x();
    int y = ui->pushButton->y();


    ui->pushButton->setGeometry(ui->comboBox->x(), ui->comboBox->y(),
                                ui->pushButton->width(),  ui->pushButton->height());

    ui->comboBox->setGeometry(x, y, ui->comboBox->width(), ui->comboBox->height());

    isUnicodeTOAscii = !isUnicodeTOAscii;
}
