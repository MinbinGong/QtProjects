#include "fuzedetector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FuzeDetector w;
    w.show();

    return a.exec();
}
