#ifndef DIRECTEURRH_H
#define DIRECTEURRH_H
/*--------------------------------------------------------------------------------------------------*/
#include <QMainWindow>
#include <QSqlTableModel>
#include "dbaccess.h"
#include <QPrinter>
#include <QPrintDialog>
//#include "exportexcelobject.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QVariant>
#include <QTimer>
#include <QDateTime>
#include "authentification.h"
#include "congemodel.h"
#include "conge.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRecord>
#include <QString>
#include <QSqlResult>
#include <QSqlField>
#include <QDebug>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class DirecteurRH;
}

class QStandardItemModel;

/*--------------------------------------------------------------------------------------------------*/
class DirecteurRH : public QMainWindow
{
    Q_OBJECT

public:
     explicit DirecteurRH(QWidget *parent = nullptr);
     explicit DirecteurRH(QObject *controller);
    bool closeConfirmation();
    void infoDrh();
    User getDrh() { return drhConnecte;}
    void setDrh(User drh){ drhConnecte = drh;}
    ~DirecteurRH();

private slots:
    void on_pushButtonDashboard_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButtonExcel_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    //void on_pushButtonQuit_clicked();

private:
    Ui::DirecteurRH *ui;
    CongeModel *model;
    QVariant getValueAt(int ix, int jx);
    DBAccess *dbAccess;
    void setUpTableView();
    void setUpTableViews();
    void populate(uint row);
    void selectFirstRow();
    User drhConnecte ;
};
/*--------------------------------------------------------------------------------------------------*/

#endif // DIRECTEURRH_H

