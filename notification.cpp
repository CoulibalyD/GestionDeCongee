#include "notification.h"
#include "ui_notification.h"
/*--------------------------------------------------------------------------------------------------*/
Notification::Notification(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);
}
/*--------------------------------------------------------------------------------------------------*/
Notification::~Notification()
{
    delete ui;
}
/*--------------------------------------------------------------------------------------------------*/
