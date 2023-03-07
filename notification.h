#ifndef NOTIFICATION_H
#define NOTIFICATION_H
/*--------------------------------------------------------------------------------------------------*/
#include <QMainWindow>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class Notification;
}
/*--------------------------------------------------------------------------------------------------*/
class Notification : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent = nullptr);
    ~Notification();

private:
    Ui::Notification *ui;
};
/*--------------------------------------------------------------------------------------------------*/
#endif // NOTIFICATION_H
