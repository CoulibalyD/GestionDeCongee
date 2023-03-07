#ifndef MANAGER_H
#define MANAGER_H
/*--------------------------------------------------------------------------------------------------*/
#include "dbaccess.h"
#include "authentification.h"
#include "congemodel.h"
#include "conge.h"
#include "employe.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QDebug>
#include <QVariant>
#include <QTimer>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class Manager;
}
 class QTimer ;

/*--------------------------------------------------------------------------------------------------*/
class Manager : public QMainWindow
{
    Q_OBJECT



public:

    explicit Manager(QWidget *parent = nullptr);
    explicit Manager(QObject *controller);
    void initialise();
    bool closeConfirmation();
    void clear();
    void populate(uint row);
    void closechamp();
    void infoManager();

    User getManagerConnect(){return managerConnecte;}
    void setManagerConnect(User manager){managerConnecte = manager;}
    void managerConge();
    void on_timeOut();
    ~Manager();

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButtonDel_clicked();
    void on_tableViewManager_clicked(const QModelIndex &index);


private:
    Ui::Manager *ui;
    CongeModel *model;
    DBAccess *dbAccess;
    void setUpTableView();
    void setUpTableViews();
    User managerConnecte;
    void updateConge();
    void selectFirstRow();
    bool getCongeInformation(Conge *conge);
      QTimer *m_timer ;

};
/*--------------------------------------------------------------------------------------------------*/
#endif // MANAGER_H
