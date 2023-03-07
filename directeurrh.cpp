#include "directeurrh.h"
#include "ui_directeurrh.h"
#include <QDebug>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPainter>
#include <QtDebug>
#include <QVariant>
#include <QString>
#include <QSqlRecord>
#include <QSqlField>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
/*--------------------------------------------------------------------------------------------------*/
DirecteurRH::DirecteurRH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirecteurRH)
{
    ui->setupUi(this);
}
/*--------------------------------------------------------------------------------------------------*/
DirecteurRH::DirecteurRH(QObject *controller):
    ui(new Ui::DirecteurRH)
{
    ui->setupUi(this);
    this->setUpTableView();
    connect(ui->pushButtonQuit, SIGNAL(clicked()), controller, SLOT(on_pushButtonQuit_clicked()));
    connect(ui->pushButtonExcel, SIGNAL(clicked()), this, SLOT(on_pushButtonExcel_clicked()));
    connect(ui->pushButtonDashboard, SIGNAL(clicked()), this, SLOT(:on_pushButtonDashboard_clicked()));
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_tableView_clicked(const QModelIndex &index)));
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::setUpTableView()
{
    model = new CongeModel(DBAccess::getInstance());
    ui->tableView->setModel(model);
    ui->tableView->show();
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::infoDrh()
{
    QMessageBox::information(this, "ALERT" , "BIENVENUE LE DIRECTEUR NOM : " +  drhConnecte.getNom() + " "+

                             " PRENOM : " + drhConnecte.getPrenom());
}
/*--------------------------------------------------------------------------------------------------*/
bool DirecteurRH::closeConfirmation()
{
    if (QMessageBox::Yes == QMessageBox::information(this, "DIRECTION RESSOURCES HUMAINES",
                                 "Voulez-vous vraiment quitter ?", QMessageBox::Button::Yes, QMessageBox::Button::Cancel))
   {
        return true;
    }
    return false;
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::selectFirstRow()
{
    if (model->rowCount() > 0)
        {
            populate(0);
        }
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::populate(uint row)
{
    QSqlRecord record = model->record(row);
    QSqlField field = record.field(0);
}
/*--------------------------------------------------------------------------------------------------*/
DirecteurRH::~DirecteurRH()
{
    delete ui;
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::on_pushButtonDashboard_clicked()
{
//    QString matricule = ui->lineEditDashboard->text();
//          if (matricule.isEmpty())
//          {
//              model->readAll();

//          }
//          else
//          {
//            if(model->readBy(matricule.toUInt()) == true)
//            {
             model->readAll();
//              QMessageBox::information(this, "Recherche", "Aucun conge de ce  matricule n'a été trouvé!");
//              return;

        //    }
//          }
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::on_pushButtonExport_clicked()
{
    QPrinter printer;
          printer.setPrinterName("Imprimer");

           QPrintDialog dialog(&printer, this);


           if(dialog.exec() == QDialog::Rejected) return;

           ui->tableView->render(&printer);
}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::on_pushButtonExcel_clicked()
{
    auto filename = QFileDialog::getSaveFileName(this,"Save", QDir::rootPath(), "CSV File (*.csv)");

       if(filename.isEmpty())
       {
           return;
       }
       QFile file(filename);
       if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           return;
       }
       QTextStream xout(&file);
       const int rowCount =  model->rowCount();
       const int colCount =  model->columnCount();
       for(int jx =0; jx< rowCount ; ++jx)
       {
           xout << model->headerData(jx, Qt::Horizontal).toString() << ";" ;


           }
           xout<< "\n";

           for (int ix=0; ix < rowCount ; ix++)
           {
               xout << getValueAt(ix,0).toString();
               for(int jx = 1; jx < colCount ; jx++)
               {
                   xout << ";" << getValueAt(ix,jx).toString();
               }
               xout <<"\n" ;
       }
       file.flush();
       file.close();

}
/*--------------------------------------------------------------------------------------------------*/
void DirecteurRH::on_tableView_clicked(const QModelIndex &index)
{
    if((index.isValid()))
           {
                model = new CongeModel(DBAccess::getInstance());
           }else
           {
               populate(index.row());
           }
}
/*--------------------------------------------------------------------------------------------------*/
QVariant DirecteurRH::getValueAt(int ix, int jx)
{
    QSqlRecord rec = model->record(ix);
    QVariant valeur = rec.field(jx).value();
    if(valeur.isNull())
    {
        return "";
    }
    return valeur;
}
/*--------------------------------------------------------------------------------------------------*/
