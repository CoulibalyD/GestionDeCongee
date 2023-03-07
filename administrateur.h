#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H
#include "dbaccess.h"
#include "authentification.h"
#include "usermodel.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QSqlTableModel>
#include <QDebug>
/*--------------------------------------------------------------------------------------------------*/
namespace Ui {
class Administrateur;
}
/*--------------------------------------------------------------------------------------------------*/
class Administrateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Administrateur(QWidget *parent = nullptr);
    explicit Administrateur(QObject *controller);
    bool closeConfirmation();
    void activateCreate();
    void activateUpdate();
    void infoUser();
    User getAdminConnect(){
        return adminConnect;
    }
    void setAdminConnect(User admin){ adminConnect=admin ;}
    QString readBy(QString nom);
    ~Administrateur(); 
private slots:
    void onPushButtonCreateClicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSearch_clicked();
    void on_radioButtonCreate_clicked();
    void on_radioButtonUpdate_clicked();
    void on_tableViewAdmin_clicked(const QModelIndex &index);
    void on_checkBoxEmploye_clicked();
    void on_checkBoxAdministrateur_clicked();
    void on_checkBoxManager_clicked();
    void on_checkBoxDRH_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Administrateur *ui;
    Administrateur* admin;
    UserModel *model;
    User adminConnect ;
    DBAccess *dbAccess;
    bool getUserInformation(User *user);
    void setUpTableView();
    void populate(uint row);
    void createUser();
    void updateUser();
    void clear();
    void selectFirstRow();

};
/*--------------------------------------------------------------------------------------------------*/
#endif // ADMINISTRATEUR_H
