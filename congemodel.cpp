#include "congemodel.h"
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QMessageBox>
#include <QDebug>
/*--------------------------------------------------------------------------------------------------*/
CongeModel::CongeModel()
{}
/*--------------------------------------------------------------------------------------------------*/
 CongeModel::CongeModel(DBAccess *dbAccess)
{
     this->dbAccess = dbAccess;
     clear();
}
/*--------------------------------------------------------------------------------------------------*/
void  CongeModel::clear()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT matricule, nom, prenom, typeconge, status, dateDebit, dateFin FROM table_demandes WHERE matricule=-1", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(2, Qt::Horizontal, tr("Prénom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Type de Conge"));
    this->setHeaderData(4, Qt::Horizontal, tr("Date de Debut"));
    this->setHeaderData(5, Qt::Horizontal, tr("Date de Fin"));
     this->setHeaderData(6, Qt::Horizontal, tr("Statut du Conge"));
    dbAccess->close();
}
 User CongeModel::readByMatricule(uint matricule)
  {
      dbAccess->open();
       User user;
      QSqlQuery query(dbAccess->database());
      query.prepare("SELECT *  FROM t_users WHERE matricule=:matricule");
      query.bindValue(":matricule", matricule);
      query.exec();

      if (query.next()) // Aucun enregistrement trouvé
      {

          QString nom = query.value(1).toString();
          QString prenom = query.value(2).toString();
          QString addre = query.value(3).toString();
          QString numero = query.value(4).toString();
          QString type = query.value(5).toString();
          QString login = query.value(6).toString();
          QString password = query.value(7).toString();
          uint reference = query.value(8).toUInt();
          uint solde = query.value(0).toUInt();
          user.setNumeroMatricule(matricule);
          user.setNom(nom);
          user.setPrenom(prenom);
          user.setAddresse(addre);
          user.setNumeroTel(numero);
          user.setType(type);
          user.setLogin(login);
          user.setPassword(password);
          user.setReference(reference);
          user.setSolde(solde);

      }
      return user;
  }
/*--------------------------------------------------------------------------------------------------*/
void CongeModel::createConge(Conge conge)
{
      DBAccess *singleton = DBAccess::getInstance();
      singleton ->open();


      //recupationde de la reference
      QSqlQuery query1 (singleton ->database());
      query1.prepare("SELECT reference FROM t_users WHERE matricule=:matricule");
      query1.bindValue(":matricule", conge.getMatriculedemandeur());
      query1.exec();

      if(false == query1.next())
      {
          return;
      }
      QSqlRecord record = query1.record();
      uint reference = query1.value(record.indexOf("reference")).toUInt();



      //Creation de la demande
      QSqlQuery query (singleton ->database());
      query.prepare("INSERT INTO t_demandes(matricule,nom,prenom,typeconge,status,dateDebut,dateFin,motif,referenceManager) VALUES (:matricule ,:nom ,:prenom ,:typeconge ,:status ,:dateDebut ,:dateFin ,:motif ,:referenceManager)");
      query.bindValue(":matricule", conge.getMatriculedemandeur());
      query.bindValue(":nom", conge.getNomDemandeur());
      query.bindValue(":prenom", conge.getPrenomDemandeur());
      query.bindValue(":typeconge", conge.getTypeConge());
      query.bindValue(":status", "IN_PROCCESS");
      query.bindValue(":dateDebut", conge.getDateDebut());
      query.bindValue(":dateFin", conge.getDateFin());
      query.bindValue(":motif", conge.getMotif());
      query.bindValue(":referenceManager",reference);
      query.exec();

      qDebug () << "Le Conge de " << conge.getNomDemandeur() << "created in t_demande successfully!";

      singleton  ->close();

}
/*--------------------------------------------------------------------------------------------------*/
void CongeModel::update(Conge conge)
{
   // QString stat = "APPROUVE" ;
    QString stat = conge.getStatus();

    //QString motif = "VALIDE";

    QString motif = conge.getMotif();

    DBAccess *dbAccess = DBAccess::getInstance();
    dbAccess ->open();
    //recuperer duree
    uint dure = conge.getDateDebut().daysTo(conge.getDateFin());
    qDebug () << "La debut : " << conge.getDateDebut();
    qDebug () << "La fin : " << conge.getDateFin();
    qDebug () << "La duree : " << dure;
    //recuperer Solde

    QSqlQuery query1(dbAccess->database());
    query1.prepare("SELECT solde FROM t_users WHERE matricule=:matriule ");

    query1.bindValue(":matriule",conge.getMatriculedemandeur());
    qDebug () << "Mat : " << conge.getMatriculedemandeur();

    query1.exec();
    if(false == query1.next())
    {
        return;
    }

    QSqlRecord record = query1.record();
    uint solde = query1.value(record.indexOf("solde")).toUInt();
    qDebug () << "Solde : " << solde;
    //Nouveau solde
    if(stat.compare("APPROUVE") == 0)
{
    uint soldeNouveau = solde - dure;
    //La mise en jour
    QSqlQuery query(dbAccess->database());
    query.prepare("UPDATE t_demandes SET status=:status ,motif=:motif ,dure=:dure ,referenceManager=:referenceManager WHERE idConge=:idConge ");

    qDebug() << "NOUVEAU SOLDE" << soldeNouveau;

    query.bindValue(":status",stat);
    query.bindValue(":motif","VALIDE");
    query.bindValue(":dure",dure);
    qDebug () << "Mat : " << conge.getMatriculedemandeur();
    query.bindValue(":idConge",conge.getIdConge());
    qDebug () << "Id : " << conge.getIdConge();
    query.bindValue(":referenceManager",conge.getReference());
    query.exec();

    //La mise en jour du nouveau solde
    QSqlQuery query2(dbAccess->database());
    query2.prepare("UPDATE t_users SET solde=:solde WHERE matricule=:matricule ");

    query2.bindValue(":matricule",conge.getMatriculedemandeur());
    query2.bindValue(":solde",soldeNouveau);
    query2.exec();



}
    else if(stat.compare("Rejet") == 0)
    {
        QSqlQuery query4(dbAccess->database());
        query4.prepare("UPDATE t_demandes SET matricule=:matricule ,nom=:nom ,prenom=:prenom ,typeconge=:typeconge ,status=:status ,dateDebut=:dateDebut ,dateFin=:dateFin ,motif=:motif ,referenceManager=:referenceManager WHERE idConge=:idConge ");
        query4.bindValue(":status",stat);
        query4.bindValue(":matricule",conge.getMatriculedemandeur());
        query4.bindValue(":nom",conge.getNomDemandeur());
        query4.bindValue(":prenom",conge.getPrenomDemandeur());
        query4.bindValue(":typeconge",conge.getTypeConge());
        query4.bindValue(":dateDebut",conge.getDateDebut());
        query4.bindValue(":dateFin",conge.getDateFin());

        query4.bindValue(":reference",conge.getReference());
        query4.bindValue(":motif",motif);


        //qDebug () << "Mat : " << conge.getMatriculedemandeur();
        qDebug () << "Mot : " << conge.getMotif();
        query4.bindValue(":idConge",conge.getIdConge());
        qDebug () << "Stat : " << conge.getStatus();
        query4.exec();


    }

    qDebug () << "Conge:" << conge.getTypeConge() << " information envoi successfully!" ;
    dbAccess ->close();


}

/*--------------------------------------------------------------------------------------------------*/
bool CongeModel::readByDemande()
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();
    QSqlQuery query(singleton->database());
    query.prepare("SELECT idConge AS IdConge ,matricule AS Matricule ,nom AS Nom ,prenom AS Prénom ,typeconge AS Type ,status AS Status ,dabeDebit AS DateDebut ,dateFin AS DateFin FROM table_demandes WHERE typeconge=:typeconge");
    query.bindValue(":typeconge", "Approuve");
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    this->setQuery(query);

    singleton ->close();

    return true;
}

void CongeModel::readByDemandeManager(uint reference)
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();
    QSqlQuery query(singleton->database());
    query.prepare("SELECT idConge ,matricule ,nom ,prenom ,typeconge ,dateDebut ,dateFin, referenceManager FROM t_demandes WHERE referenceManager=:referenceManager");
    query.bindValue(":referenceManager",reference);
    query.exec();

    singleton ->close();

    return;
}
/*----------------------------------------------------------------------------------------------------------------*/
void CongeModel::readAll()
{
    dbAccess ->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT idConge ,matricule ,nom ,prenom ,typeconge ,status ,dateDebut ,dateFin FROM t_demandes", database);

    this->setHeaderData(0, Qt::Horizontal, tr("IdConge"));
    this->setHeaderData(1, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(2, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Prénom"));
    this->setHeaderData(4, Qt::Horizontal, tr("Type Du Conge"));
    this->setHeaderData(5, Qt::Horizontal, tr("Status Du Conge"));
    this->setHeaderData(6, Qt::Horizontal, tr("Date Du Debut"));
    this->setHeaderData(7, Qt::Horizontal, tr("Date Du Fin"));
    qDebug () << "Conge displayed successfully!";
    dbAccess ->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
void CongeModel::remove(uint idConge)
{
    dbAccess->open();

    QSqlQuery query(dbAccess ->database());
    query.prepare("DELETE FROM t_users WHERE  idConge=:idConge");
    query.bindValue(":matricule",idConge);
    query.exec();

    readAll();

    qDebug () << "User with matricule :" <<  idConge << " has been deleted successfully!" ;
    dbAccess->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
bool CongeModel::readBy(uint matricule)
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT  idConge AS IdConge ,matricule AS Matricule ,nom AS Nom ,prenom AS Prénom ,typeconge AS Type ,status AS Type ,dateDebit AS DateDebut ,dateFin AS DateFin FROM t_demandes WHERE matricule=:matricule");
    query.bindValue(":matricule", matricule);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    this->setQuery(query);

    qDebug() << "Conge with matricule:" << matricule << "found.";
    singleton ->close();

    return true;
}
/*----------------------------------------------------------------------------------------------------------------*/
bool CongeModel::readBy(uint matricule ,QString type ,Conge *conge)
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();

    QSqlQuery query(singleton ->database());
    query.prepare("SELECT idConge ,matricule ,nom ,prenom ,typeconge ,status ,dateDebit ,dateFin FROM table_demandes WHERE matricule=:matricule AND typeconge=:typeconge");
    query.bindValue(":matricule", matricule);
    query.bindValue(":typeconge", type);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    conge ->setIddemandeur(query.value(record.indexOf("nom")).toUInt());
    conge ->setNom(query.value(record.indexOf("nom")).toString());
    conge ->setPrenom(query.value(record.indexOf("prenom")).toString());
    conge ->setTypeConge(query.value(record.indexOf("typeconge")).toString());
    conge->setDateDebut(query.value(record.indexOf("dateDebut")).toDate());
    conge ->setDateFin(query.value(record.indexOf("dateFin")).toDate());

    qDebug() << "Conge with Matricule:" << conge->getMatriculedemandeur() << "Take a conge:" << conge->getTypeConge() << "found.";
    singleton ->close();

    return true;
}
/*--------------------------------------------------------------------------------------------------*/
QString CongeModel::getConnection()
 {
    return singleton ->database().connectionName();
}
/*----------------------------------------------------------------------------------------------------------------*/
CongeModel::~CongeModel()
 {}
/*----------------------------------------------------------------------------------------------------------------*/
