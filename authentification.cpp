#include "authentification.h"
#include "ui_authentification.h"
#include "usermodel.h"
#include <QMessageBox>
#include <QDebug>
/*--------------------------------------------------------------------------------------------------*/
Authentification::Authentification(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Authentification)
{
    ui->setupUi(this);
    qDebug()<< "Authentification Objet is Created";
}
/*--------------------------------------------------------------------------------------------------*/
Authentification::Authentification(QObject *controller):
 ui(new Ui::Authentification)
{
ui->setupUi(this);
connect(ui->pushButtonSubmit,SIGNAL(clicked()),controller,SLOT(onPushButtonSubmitClicked()));

qDebug() << "Authentification Object is created.";
}
/*--------------------------------------------------------------------------------------------------*/
void Authentification::clearChamp()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}
/*--------------------------------------------------------------------------------------------------*/
bool Authentification::validate()
{
    QString connection;

    QString login = ui->lineEdit ->text();
    QString password = ui->lineEdit_2 ->text();

    if(login.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Authentification",
                              "Veuillez renseignez tous les champs svp !");
        return false;
    }

    UserModel userModel(DBAccess::getInstance());
    User user;

    if ((login.compare("admin") == 0) && (password.compare("passer")== 0))
    {

        QMessageBox::information(this, "Authentification", "Welcome default admin !");
    }
    else if (true == userModel.readBy(login, password, &user))
    {
       // window->incrementSolde();
        this->setUser(user);
        if (user.getType().compare("administrateur") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Administrateur : " + user.getNom() + " " + user.getPrenom() + " !");
        }
        else if (user.getType().compare("employe") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Employe User : " + user.getNom() + " " + user.getPrenom() + " !");

        }
        else if (user.getType().compare("manager") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Manager User : " + user.getNom() + " " + user.getPrenom() + " !");

        }
        else if (user.getType().compare("drh") == 0)
        {
            QMessageBox::information(this, "Authentification",
                                     "Welcome Directeur User : " + user.getNom() + " " + user.getPrenom() + " !");

        }
    }
    else
    {
        QMessageBox::critical(this, "Authentification",
                              "Incorrect Login/Password, please try again !");
        return false;
    }
    clearChamp();

    return true;
}
/*--------------------------------------------------------------------------------------------------*/
bool Authentification::closeConfirmation()
{
    if(QMessageBox::Yes == QMessageBox::information(this,"Authentification","Voulez-vous vraiment quitter",QMessageBox::Button::Yes,QMessageBox::Button::Cancel))
     {
             return true;
     }

        return false;
}
/*--------------------------------------------------------------------------------------------------*/
Authentification::~Authentification()
{
    delete ui;
    qDebug()<< "Authentification Objet has been Deleted";
}
/*--------------------------------------------------------------------------------------------------*/


void Authentification::on_pushButton_clicked()
{
    if(true == closeConfirmation())
    {
        this->close();
    }
}
/*--------------------------------------------------------------------------------------------------*/
