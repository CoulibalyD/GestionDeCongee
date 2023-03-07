#include "employemodel.h"
/*--------------------------------------------------------------------------------------------------*/
EmployeModel::EmployeModel()
{}
/*--------------------------------------------------------------------------------------------------*/
void EmployeModel::createConge(Conge conge)
{

    dbAccess->open();
    QSqlQuery query (dbAccess ->database());
    query.prepare("INSERT INTO table_demandes (matricule ,nom ,prenom ,typeconge) VALUES (:matricule,:nom ,:prenom ,:typeconge)");
    query.bindValue(":matricule", 12);
    query.bindValue(":nom", "conge.getNomDemandeur()");
    query.bindValue(":prenom", "conge.getPrenomDemandeur()");
    query.bindValue(":typeconge", "conge.getTypeConge()");
    query.bindValue(":status", conge.getStatus());
    query.bindValue(":dateDebit", "");
   query.bindValue(":dateFin", "");

    query.exec();

    qDebug () << "Conge du " << conge.getNomDemandeur() << "created successfully!";
    dbAccess  ->close();
}
/*--------------------------------------------------------------------------------------------------*/
 QString EmployeModel::getConnection()
 {
     return dbAccess->database().connectionName();
 }
 /*--------------------------------------------------------------------------------------------------*/
 EmployeModel::~EmployeModel()
 {
    qDebug() << "UserDemande Object has been deleted!";
 }
/*--------------------------------------------------------------------------------------------------*/
