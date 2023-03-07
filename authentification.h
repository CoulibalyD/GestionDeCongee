#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H
#include "user.h"
#include "usermodel.h"
#include <QMainWindow>


/*--------------------------------------------------------------------------------------------------*/
QT_BEGIN_NAMESPACE
namespace Ui { class Authentification; }
QT_END_NAMESPACE

class Authentification : public QMainWindow
{
    Q_OBJECT
public:
    Authentification(QWidget *parent = nullptr);
    explicit Authentification(QObject *controller);

    bool validate();
    bool closeConfirmation();
    User getUser() { return user; }
    void setUser (User obj) { user = obj; }
    void clearChamp();

    ~Authentification();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Authentification *ui;
   // WindowEmploye *window;
    User user;
};
/*--------------------------------------------------------------------------------------------------*/
#endif // AUTHENTIFICATION_H
