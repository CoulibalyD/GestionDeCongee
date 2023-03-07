#include "employe.h"
/*--------------------------------------------------------------------------------------------------*/
//Employe::Employe(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::Employe)
//{
//   // ui->setupUi(this);
//}
/*--------------------------------------------------------------------------------------------------*/
//Employe::Employe(QObject *controller):
//ui(new Ui::Employe){

////      ui->setupUi(this);
////      closeChamp();
////      connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(on_pushButtonCancel_clicked()));
////      connect(ui ->pushButtonCreateDemande, SIGNAL(clicked()), this, SLOT(on_pushButtonCreateDemande_clicked()));
////       connect(ui ->pushButtonSoumet, SIGNAL(clicked()), this, SLOT(on_pushButtonSoumet_clicked()));
////      connect(ui ->pushButtonSolde, SIGNAL(clicked()), this, SLOT(on_pushButtonSolde_clicked()));
////      connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(onpushButtonClearclicked()));

//      model = new CongeModel();
//}
//--------------------------------------------------------------------------------------------------
//void  Employe::closeChamp()
//{
////    ui->lineEditMatricule->close();
////    ui->lineEditNom->close();
//    ui->lineEditPrenom->close();
//    ui->lineEditTypeconge->close();
//    ui->lineEditStatuts->close();
//    ui->label_15->close();
//    ui->dateEditFin->close();
//    ui->dateEditDebut->close();
//    ui->label_17->close();
//    ui->label_13->close();
//    ui->label_2->close();
//    ui->label_16->close();
//    ui->label_14->close();
//    ui->label_18->close();

//}
//--------------------------------------------------------------------------------------------------
//bool Employe::getCongeInformation(Conge *conge)
//{

////    QString matricule = ui->lineEditMatricule->text();
////    QString nom = ui->lineEditNom->text();
////    QString prenom = ui->lineEditPrenom->text();
////    QString type = ui->lineEditTypeconge ->text();
////    QDate datedebut = ui->dateEditDebut->date();
////    QDate datefin = ui->dateEditFin->date();

////    if (nom.isEmpty() || prenom.isEmpty()|| matricule.isEmpty())
////    {
////        QMessageBox::critical(this, "Employe", "Veuillez remplir tous les champs!");
////        return false;
////    }

////        conge->setIddemandeur(matricule.toUInt());
////        conge->setNom(nom);
////        conge->setPrenom(prenom);
////        conge->setTypeConge(type);
////        conge->setDateDebut(datedebut);
////        conge->setDateFin(datefin);

////        return true;

////}
//--------------------------------------------------------------------------------------------------
////bool Employe::closeConfirmation()
////{
////    if (QMessageBox::Yes == QMessageBox::information(this, "Employe",
////                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
////   {
////        return true;
////    }
////    return false;
////}
////--------------------------------------------------------------------------------------------------*/
////void Employe::createDemande()
////{
////    Conge conge;
////    if(true == getCongeInformation(&conge))
////    {

//         model ->createConge(conge);
//         clear();
//         QMessageBox::information(this, "Employe", "Prenom: " + conge.getPrenomDemandeur() + " Nom: " + conge.getNomDemandeur() +" is Create");
//    }
//}
///*--------------------------------------------------------------------------------------------------*/
//void Employe::clear()
//{
//   /* ui->lineEditMatricule->clear();
//    ui->lineEditNom->clear();
//    ui->lineEditPrenom->clear();
//    ui->lineEditTypeconge->clear();*/
// }
///*--------------------------------------------------------------------------------------------------*/
//void Employe::onpushButtonClearclicked()
//{
//    clear();
//}
///*--------------------------------------------------------------------------------------------------*/
//void  Employe::populate(uint row)
//{
//    //QSqlRecord record = modelEmploye ->record(row);
//   // QSqlField field = record.field(0);
// //   ui->lineEditMatricule->setText(field.value().toString());
//}
///*--------------------------------------------------------------------------------------------------*/
//Employe::~Employe()
//{
//    delete ui;
//    delete modelEmploye;
//    qDebug() << "Interface Employe Object has been deleted!";
//}
///*--------------------------------------------------------------------------------------------------*/
//void Employe::on_pushButtonSoumet_clicked()
//{
////    ui->lineEditMatricule->show();
////    ui->lineEditNom->show();
////    ui->lineEditPrenom->show();
////    ui->lineEditTypeconge->show();
////    ui->dateEditDebut->show();
////    ui->dateEditFin->show();
////    ui->label_17->show();
////    ui->label_13->show();
////    ui->label_2->show();
////    ui->label_16->show();
////    ui->label_14->show();
////    ui->label_18->show();
//}

//void Employe::on_pushButtonSolde_clicked()
//{

//}

//void Employe::on_pushButtonCreateDemande_clicked()
//{
//    createDemande();
//}
