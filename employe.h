#ifndef EMPLOYE_H
#define EMPLOYE_H
/*--------------------------------------------------------------------------------------------------*/
#include "user.h"
#include "conge.h"
#include "dbaccess.h"
#include "congemodel.h"
#include "employemodel.h"
#include "authentification.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QDebug>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class Employe;
}
/*--------------------------------------------------------------------------------------------------*/
class Employe : public QMainWindow
{
    Q_OBJECT

public:
     explicit Employe(QWidget *parent = nullptr);
     explicit Employe(QObject *controller);
    bool closeConfirmation();
    void clear();
    Employe();
    ~Employe();
private slots:

   void onpushButtonClearclicked();
   void on_pushButtonSoumet_clicked();
   void on_pushButtonSolde_clicked();
   void on_pushButtonCreateDemande_clicked();

private:

    Ui::Employe *ui;
    CongeModel *model;
    EmployeModel *modelEmploye;
    DBAccess *dbAccess;
    void closeChamp();
    bool getCongeInformation(Conge *conge);
    void createDemande();
    void populate(uint row);

};
/*--------------------------------------------------------------------------------------------------*/
#endif // EMPLOYE_H
