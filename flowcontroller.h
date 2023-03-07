#ifndef FLOWCONTROLLER_H
#define FLOWCONTROLLER_H
/*--------------------------------------------------------------------------------------------------*/
#include "authentification.h"
#include "administrateur.h"
#include "employe.h"
#include "congemodel.h"
#include "windowemploye.h"
#include "manager.h"
#include "directeurrh.h"
#include "QString"
/*--------------------------------------------------------------------------------------------------*/
class Flowcontroller:public QObject
{
    Q_OBJECT

private:
    Authentification *authentification;
    Administrateur *admin;
    Employe *employe;
    Manager *manager;
    DirecteurRH *drh;
    CongeModel *model;
    WindowEmploye *window;
    QString connection;
public slots:

    void onPushButtonSubmitClicked();
    void onPushButtonCancelClicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonCancelManager_clicked();
    void on_pushButtonCancelAdmin_clicked();
    void on_pushButtonQuit_clicked();
public:
    void exec();
    Flowcontroller();
    ~Flowcontroller();
};
/*--------------------------------------------------------------------------------------------------*/
#endif // FLOWCONTROLLER_H
