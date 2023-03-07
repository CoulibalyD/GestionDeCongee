#ifndef UI_EMPLOYE_H
#define UI_EMPLOYE_H
#include "conge.h"
#include <QMainWindow>
#include "dbaccess.h"
namespace Ui {
class Ui_Employe;
}

class Ui_Employe : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ui_Employe(QWidget *parent = nullptr);
    Ui_Employe(DBAccess *dbAccess);
    ~Ui_Employe();
    void clear();
    void readAll();
    QString getConnection();
    void createConge(Conge conge);
    void update(Conge conge);
    bool readBy(QString type);
    bool readByDemande();
    bool readBy(uint matricule ,QString type ,Conge *conge);
private:
   DBAccess *dbAccess;
private slots:
    void on_pushButton_5_clicked();

private:
    Ui::Ui_Employe *ui;

   // DBAccess *dbAccess;
//    void closeChamp();
    bool getCongeInformation(Conge *conge);
};

#endif // UI_EMPLOYE_H
