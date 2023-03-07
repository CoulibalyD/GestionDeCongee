#include "authentification.h"
#include "flowcontroller.h"
#include <QApplication>
/*--------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Flowcontroller ctrl;
    ctrl.exec();
    return a.exec();
}
/*--------------------------------------------------------------------------------------------------*/
