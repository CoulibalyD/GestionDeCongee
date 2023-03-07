#include "manager.h"
#include "ui_manager.h"
#include <QDate>
/*--------------------------------------------------------------------------------------------------*/
Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
}
/*--------------------------------------------------------------------------------------------------*/
Manager::Manager(QObject *controller):
ui(new Ui::Manager)
{
    ui->setupUi(this);
    this->setUpTableViews();
    closechamp();
    model->readAll();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this , SLOT(on_timeOut()) );
    connect(ui->pushButton, SIGNAL(clicked()), controller, SLOT(on_pushButtonCancelManager_clicked()));
    connect(ui->tableViewManager, SIGNAL(clicked Modelidex &), this, SLOT(on_tableViewManager_clicked(const QModelIndex &index)));
    m_timer->start(86400000);
    qDebug() << "UIManager Object is created.";

}
/*--------------------------------------------------------------------------------------------------*/
bool Manager::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Manager",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
   {
        return true;
    }
    return false;
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::managerConge()
{
    DBAccess *singleton = DBAccess::getInstance();
    singleton ->open();


    //recupationde de la reference
    QSqlQuery query1 (singleton ->database());
    query1.prepare("SELECT status,referenceManager FROM t_demandes WHERE matricule=:matricule");
    query1.bindValue(":matricule", managerConnecte.getNumeroMatricule());

    query1.exec();


    if(false == query1.next())
    {
        return;
    }
    QSqlRecord record = query1.record();
    uint reference = query1.value(record.indexOf("referenceManager")).toUInt();
    QString stat = query1.value(record.indexOf("status")).toString();
    qDebug () << "Reference du  : " << reference;
    qDebug () << "Le status est  : " << stat;
    if((reference == managerConnecte.getNumeroMatricule())&&(stat.compare("IN_PROCESS")))
    {
        QMessageBox::information(this, "MANAGER " , " VOUS AVEZ REUSSI Une DEMANDE !!!" ) ;

    }

    singleton->close();
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::on_timeOut()
{
   managerConge();
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::infoManager()
{
    QMessageBox::information(this, "ALERT" , "BIENVENUE MANAGER NOM : " + managerConnecte.getNom() + " " +

                             "PRENOM : " + managerConnecte.getPrenom());
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::initialise()
{
    uint reference = managerConnecte.getNumeroMatricule();
    model->readByDemandeManager(reference);
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::closechamp()
{
    ui->labelMotif->close();
    ui->textEdit->close();
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::setUpTableViews()
{
    model = new CongeModel(DBAccess::getInstance());
    ui->tableViewManager->setModel(model);
    //ui->tableViewManager->hideColumn(7);
    selectFirstRow();
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);
    ui->lineEdit->setText(field.value().toString());
    ui->lineEdit_2->setText(record.field(1).value().toString());
    ui->lineEdit_3->setText(record.field(2).value().toString());
    ui->lineEdit_4->setText(record.field(3).value().toString());
    ui->lineEdit_5->setText(record.field(4).value().toString());
    ui->lineEdit_6->setText(record.field(6).value().toString());
    ui->lineEdit_7->setText(record.field(7).value().toString());
    ui->lineEdit_8 ->clear();
}
/*--------------------------------------------------------------------------------------------------*/
void  Manager::selectFirstRow()
 {
    if (model->rowCount() > 0)
    {
        populate(0);
    }
 }
/*--------------------------------------------------------------------------------------------------*/
void Manager::clear()
{
   ui->lineEdit->clear();
   ui->lineEdit_2->clear();
   ui->lineEdit_3->clear();
   ui->lineEdit_4->clear();
   ui->lineEdit_5->clear();
   ui->lineEdit_6->clear();
   ui->lineEdit_7->clear();
   ui->lineEdit_8->clear();
   ui->textEdit->clear();
}
/*----------------------------------------------------------------------------------------------------------------*/
bool Manager::getCongeInformation(Conge *conge)
{
    QString idConge = ui->lineEdit->text();
    QString matricule = ui->lineEdit_2->text();
    QString nom = ui->lineEdit_3->text();
    QString prenom = ui->lineEdit_4->text();
    QString type = ui->lineEdit_5->text();
    QString status = ui->lineEdit_8->text();

    QVariant dateD  = ui->lineEdit_6->text();
    QDate debut = dateD.toDate();

    QVariant dateF = ui->lineEdit_7->text();
    QDate fin = dateF.toDate();

    QString motif  = ui->textEdit->toPlainText();
    uint reference = conge->getReference();

    qDebug() << "Nom."  <<nom;
    qDebug() << "Prenom." << prenom;
    qDebug() << "Matricule."  << matricule;

    if (nom.isEmpty() || prenom.isEmpty()|| matricule.isEmpty())
    {
        QMessageBox::critical(this, "Manager", "Veuillez remplir tous les champs!");
        return false;
    }
        conge->setIdconge(idConge.toUInt());
        conge->setIddemandeur(matricule.toUInt());
        conge->setNom(nom);
        conge->setPrenom(prenom);
        conge->setTypeConge(type);
        conge->setStatus(status);
        conge->setDateDebut(debut);
        conge->setDateFin(fin);
        conge->setMotif(motif);
        conge->setRefence(reference);

        return true;
}
/*----------------------------------------------------------------------------------------------------------------*/
 void Manager::updateConge()
 {
     Conge conge;
     if(true == getCongeInformation(&conge))
     {
        model->update(conge);
        clear();
        QMessageBox::information(this, "Manager", "Envoi effectuer avec succès!");
      }
 }
/*----------------------------------------------------------------------------------------------------------------*/
void Manager::on_pushButton_4_clicked()//push boutton envoi
{
    updateConge();
}
/*----------------------------------------------------------------------------------------------------------------*/
void Manager::on_pushButton_3_clicked()//push Boutton approuve
{
    int mat = getManagerConnect().getNumeroMatricule();
    ui->lcdNumber->display(mat);
    if(ui->pushButton_3->isEnabled())    {
        ui->labelMotif->close();
        ui->textEdit->close();
        ui->lineEdit_8->setText("APPROUVE");
    }
}
/*----------------------------------------------------------------------------------------------------------------*/
void Manager::on_pushButton_2_clicked()//Boutton rejet
{
    ui->lineEdit_8->clear();
    ui->lineEdit_8->setText("Rejet");
    ui->labelMotif->show();
    ui->textEdit->show();

}
/*--------------------------------------------------------------------------------------------------*/
Manager::~Manager()
{
    delete ui;
}
/*--------------------------------------------------------------------------------------------------*/

void Manager::on_pushButtonDel_clicked()
{
    QString idconge = ui->lineEdit ->text();
    if (idconge.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez sélectionner une Demande!");
    }
    else
    {
        if (QMessageBox::Yes == QMessageBox::information(this, "Confirmation", "Voulez-vous vraiment supprimer cette Demande ?",
                                                         QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
        {
            model->remove(idconge.toUInt());
            selectFirstRow();
        }
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Manager::on_tableViewManager_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        populate(index.row());
    }
}
/*--------------------------------------------------------------------------------------------------*/
