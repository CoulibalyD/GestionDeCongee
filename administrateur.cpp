#include "administrateur.h"
#include "ui_administrateur.h"
/*--------------------------------------------------------------------------------------------------*/
Administrateur::Administrateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrateur)
{
    ui->setupUi(this);
}
/*--------------------------------------------------------------------------------------------------*/
Administrateur::Administrateur(QObject *controller):
ui(new Ui::Administrateur)
{

    ui->setupUi(this);
    this->setUpTableView();

    ui->lineEditReference->close();
    ui->label_9->close();


    connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(on_pushButtonCancelAdmin_clicked()));
    connect(ui->pushButtonCreate, SIGNAL(clicked()), this, SLOT(onPushButtonCreateClicked()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(on_pushButtonClear_clicked()));
    connect(ui->checkBoxAdministrateur, SIGNAL(clicked()), this, SLOT(on_checkBoxAdministrateur_clicked()));
    connect(ui->checkBoxDRH, SIGNAL(clicked()), this, SLOT(on_checkBoxDRH_clicked()));
    connect(ui->checkBoxEmploye, SIGNAL(clicked()), this, SLOT(on_checkBoxEmploye_clicked()));
    connect(ui->checkBoxManager, SIGNAL(clicked()), this, SLOT(on_checkBoxManager_clicked()));
    connect(ui->pushButtonSearch, SIGNAL(clicked()), this, SLOT(on_pushButtonSearch_clicked()));
    connect(ui->radioButtonCreate, SIGNAL(clicked()), this, SLOT(on_radioButtonCreate_clicked()));
    connect(ui->radioButtonUpdate, SIGNAL(clicked()), this, SLOT(on_radioButtonUpdate_clicked()));
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_tableViewAdmin_clicked(const QModelIndex &index)));

    qDebug() << "UIAdmin Object is created.";
}
/*--------------------------------------------------------------------------------------------------*/
bool Administrateur::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "Authentification",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
   {
        return true;
    }
    return false;
}

void Administrateur::infoUser()
{

    QMessageBox::information(this, "ALERT" , "BIENVENUE ADMIN NOM : " + adminConnect.getNom() +

                             " PRENOM :" + adminConnect.getPrenom());

}

/*--------------------------------------------------------------------------------------------------*/
void Administrateur::activateCreate()
{
    ui->radioButtonCreate->setChecked(true);
    ui->pushButtonCreate->setText("Create");
    ui->lineEditMatricule->setVisible(false);
    ui->label->setVisible(false);
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::activateUpdate()
{
    ui->radioButtonUpdate->setChecked(true);
    ui->pushButtonCreate->setText("Update");
    ui->lineEditMatricule->setVisible(true);
    ui->label->setVisible(true);
}
/*--------------------------------------------------------------------------------------------------*/
bool Administrateur::getUserInformation(User *user)
{
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString adresse = ui->lineEditAddresse->text();
    QString numeroTel = ui->lineEditNTelephone->text();
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    QString reference = ui->lineEditReference->text();

    if (nom.isEmpty() || prenom.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez remplir tous les champs!");
        return false;
    }

    if (ui->radioButtonUpdate->isChecked()) // Update process ...
    {
        QString matricule = ui->lineEditMatricule ->text();
        if (matricule.isEmpty())
        {
            QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur svp!");
            return false;
        }

        user->setNumeroMatricule(matricule.toUInt());
    }
    user->setNom(nom);
    user->setPrenom(prenom);
    user->setAddresse(adresse);
    user->setNumeroTel(numeroTel);
    user->setLogin(login);
    user->setPassword(password);
    user->setReference(reference.toUInt());
    user->setSolde(30);
    user->setJob(QDate::currentDate());
    if (ui->checkBoxAdministrateur->isChecked())
    {
        if(ui->checkBoxEmploye->isChecked()||ui->checkBoxDRH->isChecked()||ui->checkBoxManager->isChecked())
        {
            QMessageBox::critical(this, "Error", "Veuillez desactive le deuxieme check!");
            return false;
         }else{
            user->setType("administrateur");
        }
    }
    else if(ui->checkBoxEmploye->isChecked())
    {
        if(ui->checkBoxAdministrateur->isChecked()||ui->checkBoxDRH->isChecked()||ui->checkBoxManager->isChecked())
        {
            QMessageBox::critical(this, "Error", "Veuillez desactive le deuxieme check!");
            return false;
        }else
        {
            user->setType("employe");
        }

    } else if(ui->checkBoxManager->isChecked())
    {
        if(ui->checkBoxDRH->isChecked()||ui->checkBoxEmploye->isChecked()||ui->checkBoxAdministrateur->isChecked())
        {
            QMessageBox::critical(this, "Error", "Veuillez desactive le deuxieme check!");
            return false;
        }else{
            user->setType("manager");
        }
    }else if(ui->checkBoxDRH->isChecked())
    {
        if(ui->checkBoxAdministrateur->isChecked()||ui->checkBoxEmploye->isChecked()||ui->checkBoxAdministrateur->isChecked())
        {
            QMessageBox::critical(this, "Error", "Veuillez desactive le deuxieme check!");
            return false;
        }else{
            user->setType("drh");
        }
    }
   return true;
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::setUpTableView()
{
    model = new UserModel(DBAccess::getInstance());
    ui->tableView->setModel(model);
    ui->tableView ->hideColumn(7); // don't show user
    ui->tableView ->show();

    selectFirstRow();
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);
    ui->lineEditMatricule->setText(field.value().toString());
    ui->lineEditNom->setText(record.field(1).value().toString());
    ui->lineEditPrenom->setText(record.field(2).value().toString());
    ui->lineEditAddresse->setText(record.field(3).value().toString());
    ui->lineEditNTelephone->setText(record.field(4).value().toString());
    ui->lineEditLogin->setText(record.field(5).value().toString());
    ui->lineEditPassword->clear();
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::createUser()
{
    User user;
    if (true == getUserInformation(&user))
    {
        model->create(user);
        clear();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::updateUser()
{
    User user;
    if (true == getUserInformation(&user))
    {
        model->update(user);
        clear();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::clear()
{
    ui->lineEditMatricule->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->lineEditAddresse->clear();
    ui->lineEditNTelephone->clear();
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    ui->lineEditReference->clear();
    ui->lineEditSearch->clear();

    activateCreate();
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::selectFirstRow()
{
    if (model->rowCount() > 0)
    {
        populate(0);
        activateUpdate();
    }
    else
    {
        clear();
        activateCreate();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::onPushButtonCreateClicked()
{
    if (ui->radioButtonUpdate->isChecked())
    {
        updateUser();
    }
    else
    {
        createUser();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_pushButtonDelete_clicked()
{
    QString matricule = ui->lineEditMatricule->text();
    if (matricule.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Veuillez sélectionner un utilisateur!");
    }
    else
    {
        if (QMessageBox::Yes == QMessageBox::information(this, "Confirmation", "Voulez-vous vraiment supprimer cet utilisateur ?",
                                                         QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
        {
            model->remove(matricule.toUInt());
            selectFirstRow();
        }
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_pushButtonClear_clicked()
{
    clear();
    model->clear();
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_pushButtonSearch_clicked()
{
    QString search = ui->lineEditSearch->text();
    if (search.isEmpty())
    {
        model->readAll();
        if (model->rowCount() <= 0)
        {
            QMessageBox::information(this, "Recherche", "La liste des utilisateurs est vide!");
            activateCreate();
        }
        else
        {
            populate (0);
            activateUpdate();
        }
    }
    else if (model->readBy(search) == false)
    {
        QMessageBox::information(this, "Recherche", "Aucun utilisateur avec ce login n'a été trouvé!");
        return;
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_radioButtonCreate_clicked()
{
    clear();
    activateCreate();
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_radioButtonUpdate_clicked()
{
    QString matricule = ui->lineEditMatricule->text();
    if (matricule.isEmpty())
    {
        activateCreate();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_tableViewAdmin_clicked(const QModelIndex &index)
{

    if(index.isValid() && ui->checkBoxEmploye->isDown())
    {
         activateUpdate();
         populate(index.row());
    }if(index.isValid()&&(ui->checkBoxEmploye->isChecked()))
    {
        model = new UserModel(DBAccess::getInstance());
        QSqlRecord record = model->record(index.row());
        QSqlField field = record.field(index.row());
        ui->tableView->selectRow(field.value().toUInt());

    }

}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_checkBoxEmploye_clicked()
{

    uint row = ui->tableView ->selectionModel()->currentIndex().row();
    if(ui->checkBoxEmploye->isChecked())
    {

        ui->label_9->show();
        ui->lineEditReference->show();
        ui->checkBoxAdministrateur->close();
        ui->checkBoxDRH->close();
        ui->checkBoxManager->close();
        ui->tableView ->setEnabled(model->readByManager());
        QSqlRecord record = model->record(row);
        QSqlField field = record.field(0);
        ui->lineEditReference->setText(field.value().toString());

    }else {

        setUpTableView();
        ui->checkBoxAdministrateur->show();
        ui->checkBoxDRH->show();
        ui->checkBoxManager->show();
        ui->label_9->close();
        ui->lineEditReference->close();
        populate(row);

    }
}
/*--------------------------------------------------------------------------------------------------*/
Administrateur::~Administrateur()
{
    delete ui;
    delete model;
    qDebug() << "Interface Administrateur Object has been deleted!";
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_checkBoxAdministrateur_clicked()
{
    if(ui->checkBoxAdministrateur->isChecked())
    {

        ui->checkBoxDRH->close();
        ui->checkBoxEmploye->close();
        ui->checkBoxManager->close();
        ui->label_9->close();
        ui->lineEditReference->close();
        activateCreate();

    }else{

        ui->checkBoxDRH->show();
        ui->checkBoxEmploye->show();
        ui->checkBoxManager->show();
        activateCreate();
    }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_checkBoxManager_clicked()
{
    if(ui->checkBoxManager->isChecked())
    {
        ui->checkBoxDRH->close();
        ui->checkBoxEmploye->close();
        ui->checkBoxAdministrateur->close();
        ui->label_9->close();
        ui->lineEditReference->close();
    }else{

        ui->checkBoxDRH->show();
        ui->checkBoxEmploye->show();
        ui->checkBoxAdministrateur->show();
     }
}
/*--------------------------------------------------------------------------------------------------*/
void Administrateur::on_checkBoxDRH_clicked()
{
    if(ui->checkBoxDRH->isChecked())
    {
        ui->checkBoxAdministrateur->close();
        ui->checkBoxEmploye->close();
        ui->checkBoxManager->close();
        ui->label_9->close();
        ui->lineEditReference->close();
    }else
    {
        ui->checkBoxAdministrateur->show();
        ui->checkBoxEmploye->show();
        ui->checkBoxManager->show();
    }
}

/*--------------------------------------------------------------------------------------------------*/

void Administrateur::on_tableView_clicked(const QModelIndex &index)
{
    populate(index.row());
}
