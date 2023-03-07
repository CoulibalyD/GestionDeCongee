#include "windowemploye.h"
#include "ui_windowemploye.h"

/*----------------------------------------------------------------------------------------------------------------*/
WindowEmploye::WindowEmploye(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowEmploye)
{
    ui->setupUi(this);
}
/*----------------------------------------------------------------------------------------------------------------*/
 WindowEmploye::WindowEmploye(QObject *controller):
     ui(new Ui::WindowEmploye)
 {
     ui->setupUi(this);
     closeChamp();
     m_timer = new QTimer(this);
     d_timer = new QTimer(this);
     connect(m_timer, SIGNAL(timeout()), this , SLOT(on_timeOut()) );
     connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(on_pushButtonCancel_clicked()));
     m_timer->start(86400000);
      d_timer->start(86400000);
}
 /*----------------------------------------------------------------------------------------------------------------*/
WindowEmploye::~WindowEmploye()
{
    delete ui;
    delete m_timer;
    delete d_timer;
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::closeChamp()
{
    ui->labelMatricule->close();
    ui->labelNom->close();
    ui->labelPrenom->close();
    ui->labelType->close();
    ui->labelStatus->close();
    ui->lineEditMatricule->close();
    ui->lineEditNom->close();
    ui->lineEditPrenom->close();
    ui->dateEditDebut->close();
    ui->dateEditFin->close();
    ui->lineEditType->close();
    ui->lineEditStatuts->close();
    ui->labelDateDebut->close();
    ui->labelDateFin->close();
}
/*--------------------------------------------------------------------------------------------------*/
void WindowEmploye::statusConge()
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();

    //recupation du status
    QSqlQuery query1 (singleton ->database());
    query1.prepare("SELECT status FROM t_demandes WHERE matricule=:matricule");
    query1.bindValue(":matricule", userConnecte.getNumeroMatricule());
    query1.exec();

    if(false == query1.next())
    {
        return;
    }

    QSqlRecord record = query1.record();
    QString status = query1.value(record.indexOf("status")).toString();
    qDebug() << "Le status est:" <<  status;
    if(status.compare("APPROUVE"))
    {
        QMessageBox::information(this, "EMPLOYE " , " VOTRE DEMANDE A ETE APPROUVEE AVEC SUCCES!" ) ;

    }else
    {
        QMessageBox::information(this, "EMPLOYE " , " VOTRE DEMANDE A ETE Rejet!" ) ;
    }

    singleton->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
bool WindowEmploye::getCongeInformation(Conge *conge)
{
    QString matricule = ui->lineEditMatricule->text();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString type = ui->lineEditType->text();
    QDate dateDeb = ui->dateEditDebut->date();
    QDate dateFin   = ui->dateEditFin->date();
    QString status = ui->lineEditType->text();
    if(nom.isEmpty()|| prenom.isEmpty()||type.isEmpty())
    {
        QMessageBox::critical(this, "Employe", "Veuillez remplir tous les champs!");
        return false;
    }

    conge->setIddemandeur(matricule.toUInt());
    conge->setNom(nom);
    conge->setPrenom(prenom);
    conge->setTypeConge(type);
    conge->setDateDebut(dateDeb);
    conge->setDateFin(dateFin);
    //conge->setStatus(status);

    return true;

}
/*--------------------------------------------------------------------------------------------------*/
void WindowEmploye::on_timeOut()
{
   statusConge();
}
/*--------------------------------------------------------------------------------------------------*/
int WindowEmploye::on_dateTime()
{
    int compteur = 0 ;
    if(compteur <= 31)
    {
        return compteur++;
    }
    else
    {
        return 0;
    }
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::createDemande()
{
    Conge conge;
    if(true == getCongeInformation(&conge))
    {
        model ->createConge(conge);
        clear();
        closeChamp();
        if(conge.getMatriculedemandeur() != 0)
        {
             QMessageBox::information(this, "Employe", "Votre Demande a été envoyé avec success!!!");
        }


    }
}
/*--------------------------------------------------------------------------------------------------*/
void  WindowEmploye::infoEmploye()
{
    QMessageBox::information(this, "ALERT" , "BIENVENUE A L'EMPLOYE NOM : " + userConnecte.getNom() + " " +

                             "PRENOM : " + userConnecte.getPrenom());
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::clear()
{
    ui->lineEditMatricule->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->lineEditType->clear();
}
/*----------------------------------------------------------------------------------------------------------------*/
 bool WindowEmploye::closeConfirmation()
 {
     if (QMessageBox::Yes == QMessageBox::information(this, "EMPLOYE",
                                  "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
    {
         return true;
     }
     return false;
 }
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::on_pushButtonCreateDemande_clicked()
{
   createDemande();

}
void WindowEmploye::alertEmploye()
{
    if(userConnecte.getSolde() <= 6 )
    {
        QMessageBox::critical(this, "EMPLOYE",
                                         "Votre solde est epuise Monsieur");
    }
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::on_pushButtonSoumet_clicked()
{
    ui->labelMatricule->show();
    ui->labelNom->show();
    ui->labelPrenom->show();
    ui->labelType->show();
    ui->lineEditMatricule->show();
    ui->lineEditNom->show();
    ui->lineEditPrenom->show();
    ui->lineEditType->show();
    ui->dateEditDebut->show();
    ui->dateEditFin->show();
    ui->labelDateDebut->show();
    ui->labelDateFin->show();
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::on_pushButtonClear_clicked()
{
    clear();
}
/*----------------------------------------------------------------------------------------------------------------*/
void WindowEmploye::on_pushButtonSolde_clicked()
{
    int solde = getUserConnect().getSolde();
    ui->labelNom_2->setText(userConnecte.getNom());
    ui->lcdNumber->display(solde);

}
/*--------------------------------------------------------------------------------------------------*/
void WindowEmploye::incrementSolde()
{

    DBAccess *dbAccess = DBAccess::getInstance();
    dbAccess->open() ;
    int solde = userConnecte.getSolde();
    QDate mont = userConnecte.getJob();
    QDate selectedDate = QDate::currentDate();
    int selectmois = selectedDate.month();

    if ( mont.month() == 1){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde = 2;   //+2jr
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde= 6;
                break;
            case 4 :
                solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case 7 :
                 solde =14;
                break;
            case 8 :
                 solde =16;
                break;
            case 9 :
                 solde =18;
                break;
            case 10 :
                 solde = 20;
                break;
            case 11 :
                 solde =25;  //+5jr
                QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30; //+5jr
                break;
            }

    } else if ( mont.month() == 2){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde = 4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                 solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case 7 :
                 solde =14;
                break;
            case 8 :
                 solde =16;
                break;
            case 9 :
                 solde =18;
                break;
            case 10 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;

            }

            }else  if ( mont.month() == 3){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                 solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case 7 :
                 solde =14;
                break;
            case 8 :
                 solde =16;
                break;
            case 9 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 4){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                 solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case 7 :
                 solde =14;
                break;
            case 8 :
                 solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                solde =20;
                break;
            case -1 :
                 solde =25;
                QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 5){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case 7 :
                solde =14;
                break;
            case -4 :
                solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                solde =30;
                break;
            }
            }else   if ( mont.month() == 6){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                solde =6;
                break;
            case 4 :
                solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case 6 :
                 solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 7){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                solde =8;
                break;
            case 5 :
                 solde =10;
                break;
            case -6 :
                 solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 8){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case 4 :
                solde =8;
                break;
            case -7 :
                 solde =10;
                break;
            case -6 :
                 solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                solde = 18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                solde =30;
                break;
            }
            }else  if ( mont.month() == 9){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case 3 :
                 solde =6;
                break;
            case -8 :
                 solde =8;
                break;
            case -7 :
                 solde =10;
                break;
            case -6 :
                 solde =12;
                break;
            case -5 :
                 solde = 14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                 QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 10){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                 solde =2;
                break;
            case 2 :
                 solde =4;
                break;
            case -9 :
                 solde =6;
                break;
            case -8 :
                 solde =8;
                break;
            case -7 :
                 solde =10;
                break;
            case -6 :
                 solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }
            }else  if ( mont.month() == 11){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case 1 :
                solde =2;
                break;
            case -10 :
                 solde =4;
                break;
            case -9 :
                 solde =6;
                break;
            case -8 :
                 solde =8;
                break;
            case -7 :
                 solde =10;
                break;
            case -6 :
                 solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                 solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                 QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =30;
                break;
            }

            }else if( mont.month() == 12){

            int reponse = selectmois - mont.month();
            switch (reponse) {
            case -11 :
                 solde =2;
                break;
            case -10 :
                 solde =4;
                break;
            case -9 :
                 solde =6;
                break;
            case -8 :
                 solde=8;
                break;
            case -7 :
                 solde =10;
                break;
            case -6 :
                solde =12;
                break;
            case -5 :
                 solde =14;
                break;
            case -4 :
                solde =16;
                break;
            case -3 :
                 solde =18;
                break;
            case -2 :
                 solde =20;
                break;
            case -1 :
                 solde =25;
                  QMessageBox::information(this, "ALERT", "ATTENTION VOTRE SOLDE EST SUPERIEUR A 24 MR : ", userConnecte.getNom());
                break;
            case 0 :
                 solde =3;
                break;

            }
            }

      else
            {
                QMessageBox::information(this, "ALERT", "RIEN A FAIRE!!") ;
            }
        qDebug() << "increment" <<  solde;
        userConnecte.setSolde( solde);

        QSqlQuery query2(dbAccess->database());
        query2.prepare("UPDATE t_users SET matricule=:matricule ,nom=:nom ,prenom=:prenom ,addresse=:addresse ,numeroTelephone=:numeroTelephone ,type=:type ,login=:login ,password=:password ,reference=:reference ,solde=:solde WHERE matricule=:matricule ");
        query2.bindValue(":matricule",userConnecte.getNumeroMatricule());
        query2.bindValue(":nom", userConnecte.getNom());
        query2.bindValue(":prenom", userConnecte.getPrenom());
        query2.bindValue(":addresse", userConnecte.getAddresse());
        query2.bindValue(":numeroTelephone", userConnecte.getNumeroTelephone());
        query2.bindValue(":type", userConnecte.getType());
        query2.bindValue(":login", userConnecte.getLogin());
        query2.bindValue(":password",userConnecte.getPassword());
        query2.bindValue(":reference",userConnecte.getReference());
        query2.bindValue(":solde",userConnecte.getSolde());
        query2.exec();
        dbAccess ->close();
}
/*----------------------------------------------------------------------------------------------------------------*/


