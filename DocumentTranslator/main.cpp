#include "smarttranslator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartTranslator w;
    w.show();

    return a.exec();
}
