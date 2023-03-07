#ifndef WINDOWEMPLOYE_H
#define WINDOWEMPLOYE_H
/*--------------------------------------------------------------------------------------------------*/
#include "user.h"
#include "conge.h"
#include "dbaccess.h"
#include "congemodel.h"
#include "authentification.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QDebug>
#include <QTimer>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class WindowEmploye;
}

class QTimer;

/*--------------------------------------------------------------------------------------------------*/
class WindowEmploye : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowEmploye(QWidget *parent = nullptr);
    explicit WindowEmploye(QObject *controller);
    User getUserConnect() { return userConnecte;}

    void setUserConnecte(User user){ userConnecte = user;}
    ~WindowEmploye();

    bool closeConfirmation();
    void clear();
    void alertEmploye();
    void incrementSolde();
    void infoEmploye();
    void statusConge();
    int on_dateTime();

private slots:

    void on_pushButtonCreateDemande_clicked();
    void on_pushButtonSoumet_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSolde_clicked();
    void on_timeOut();


private:

    Ui::WindowEmploye *ui;
    CongeModel *model;
    UserModel *modelUser;
    DBAccess *dbAccess;
    void closeChamp();
    bool getCongeInformation(Conge *conge);
    void createDemande();
    QTimer *m_timer ;
    QTimer *d_timer ;

    User userConnecte;


};
/*--------------------------------------------------------------------------------------------------*/
#endif // WINDOWEMPLOYE_H
