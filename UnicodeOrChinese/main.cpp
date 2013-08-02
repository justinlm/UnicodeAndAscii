#include "unicodeorchinese.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UnicodeOrChinese w;
    w.show();
    
    return a.exec();
}
