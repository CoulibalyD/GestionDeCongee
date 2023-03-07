#include "ui_employe.h"
#include "ui_ui_employe.h"

Ui_Employe::Ui_Employe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ui_Employe)
{
    ui->setupUi(this);
}
//QString Ui_Employe::getConnection()
//{
//    return dbAccess->database().connectionName();
//}
//bool Ui_Employe::getCongeInformation(Conge *conge)
//{

//}
//void Ui_Employe::createConge(Conge conge)
//{
//    dbAccess ->open();
//    QSqlQuery query (dbAccess ->database());
//    query.prepare("INSERT INTO t_demande(matricule ,nom ,prenom ,typeconge) VALUES (:matricule ,:nom ,:prenom ,:typeconge)");
//    query.bindValue(":matricule", conge.getMatriculedemandeur());
//    query.bindValue(":nom", conge.getNomDemandeur());
//    query.bindValue(":prenom", conge.getPrenomDemandeur());
//    query.bindValue(":typeconge", conge.getTypeConge());
//    query.bindValue(":status", conge.getStatus());
//    query.bindValue(":dateDebit", "20201");
//    query.bindValue(":dateFin","2020-01-01");
//    query.exec();
//    qDebug () << "Le Conge de " << conge.getNomDemandeur() << "created successfully!";
//    dbAccess  ->close();
//}

//Ui_Employe::~Ui_Employe()
//{
//    delete ui;
//}

//void Ui_Employe::on_pushButton_5_clicked()
//{

//}
