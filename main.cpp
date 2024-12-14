#include <QApplication>
#include "capp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CApp app;
    //w.show();

    return a.exec();
}
