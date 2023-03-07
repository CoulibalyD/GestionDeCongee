#ifndef CONGEMODEL_H
#define CONGEMODEL_H
#include "conge.h"
#include "user.h"
#include "dbaccess.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QDate>
#include <QSqlTableModel>
/*--------------------------------------------------------------------------------------------------*/
class CongeModel:public QSqlQueryModel
{
private:
    DBAccess *dbAccess;
    DBAccess *singleton;
public:

    CongeModel();
    CongeModel(DBAccess *dbAccess);
    ~CongeModel();

    void clear();
    void readAll();
    QString getConnection();
    void createConge(Conge conge);
    void update(Conge conge);
    void remove(uint idConge);
    bool readBy(uint matricule);
    bool readByDemande();
    User readByMatricule(uint matricule);
    bool readBy(uint matricule ,QString type ,Conge *conge);
    void readByDemandeManager(uint reference);
    void statusConge();

};
/*--------------------------------------------------------------------------------------------------*/
#endif // CONGEMODEL_H
