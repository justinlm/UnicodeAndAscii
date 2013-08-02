#ifndef UNICODEORCHINESE_H
#define UNICODEORCHINESE_H

#include <QWidget>

class QString;
class QDataWidgetMapper;

#define test

namespace Ui {
class UnicodeOrChinese;
}

class UnicodeOrChinese : public QWidget
{
    Q_OBJECT
    
    enum TextShowType
    {
        TextShowType_Array,
        id_downText_String
    };

public:
    explicit UnicodeOrChinese(QWidget *parent = 0);
    ~UnicodeOrChinese();
private test:
    int i;

private slots:
    void on_UpTextEdit_textChanged();

    void on_comboBox_currentIndexChanged(int index);

    bool eventFilter(QObject *watched, QEvent *event);

    void on_reverseButton_clicked();

private:

    Ui::UnicodeOrChinese *ui;

    QString strUpTextedit;

    int comboxCurIndex;

    QDataWidgetMapper *m_pMapper;

    bool isUnicodeTOAscii;
};

#endif // UNICODEORCHINESE_H
