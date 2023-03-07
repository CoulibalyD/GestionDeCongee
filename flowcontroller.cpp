#include "flowcontroller.h"
#include <QMessageBox>
#include <QDebug>
/*----------------------------------------------------------------------------------------------------------------*/
Flowcontroller::Flowcontroller() : authentification(nullptr), admin (nullptr),employe(nullptr),manager(nullptr),drh(nullptr),window(nullptr)
{
     connection = DBAccess::getInstance()->database().connectionName();
}
/*----------------------------------------------------------------------------------------------------------------*/
void Flowcontroller::onPushButtonSubmitClicked()
{
    if (true == authentification->validate())
    {
        User user;
        user = authentification->getUser();
        //QString type(authentification->getUser().getType());
        if(((user.getType().compare("administrateur"))==0))
           {
                 authentification->close();
                 admin = new Administrateur(this);
                 admin ->setAdminConnect(user);

                 admin->show();
                 admin->infoUser();
        }else if(((user.getType().compare("employe"))== 0)){
                  authentification->close();
                  window = new WindowEmploye(this);
                  window->setUserConnecte(user);       
                  window->show();

                 // window->incrementSolde();
                  window->alertEmploye();
                  window->infoEmploye();

         }else if(((user.getType().compare("manager"))== 0))
        {
            authentification->close();
            manager = new Manager(this);
            manager->setManagerConnect(user);
            manager->show();
            manager->initialise();
            manager->infoManager();
            manager->on_timeOut();
        }else if(((user.getType().compare("drh"))== 0))
        {
           authentification->close();
           drh = new DirecteurRH(this);
           drh->setDrh(user);
           drh->show();
           drh->infoDrh();

        }
       }
}
/*--------------------------------------------------------------------------------------------------*/
void Flowcontroller::on_pushButtonCancel_clicked()
{
    if(window ->closeConfirmation())
    {
        window ->close();
        authentification->show();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Flowcontroller::on_pushButtonCancelManager_clicked()
{
    if(manager->closeConfirmation())
    {
        manager->close();
        authentification->show();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void  Flowcontroller::on_pushButtonCancelAdmin_clicked()
{
    if(admin->closeConfirmation())
    {
        admin->close();
        authentification->show();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Flowcontroller::on_pushButtonQuit_clicked()
{
    if(drh->closeConfirmation())
    {
        drh->close();
        authentification->show();
    }
}
/*----------------------------------------------------------------------------------------------------------------*/
void Flowcontroller::onPushButtonCancelClicked()
{
    if (authentification->closeConfirmation() == true)
    {
        authentification->close();
        admin->close();
        employe->close();
        manager->close();
        drh->close();

    }
}
/*----------------------------------------------------------------------------------------------------------------*/
void Flowcontroller:: exec()
{
   authentification = new Authentification(this);
   authentification->show();
}
/*----------------------------------------------------------------------------------------------------------------*/
Flowcontroller::~Flowcontroller()
{
    if (authentification != nullptr)
    {
        delete authentification;
    }

    if (admin != nullptr)
    {
        delete admin;
    }

    DBAccess::release();
    QSqlDatabase::removeDatabase(connection);
}
/*--------------------------------------------------------------------------------------------------*/
