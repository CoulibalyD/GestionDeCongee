#ifndef USERMODEL_H
#define USERMODEL_H
/*--------------------------------------------------------------------------------------------------*/
#include <QSqlQueryModel>
#include "dbaccess.h"
#include "user.h"
#include "conge.h"
#include "congemodel.h"
/*--------------------------------------------------------------------------------------------------*/
class UserModel:public QSqlQueryModel
{
private:
    DBAccess *dbAccess;
public:
    UserModel( DBAccess *dbAccess);
    ~UserModel();
    void clear();
    QString getConnection();

    //CRUD

    void create(User user);
    void update(User user);
    void remove(uint matricule);
    bool readBy(QString login);
    bool readByManager();
    bool readBy(QString login,QString password,User *user);
//    int  recupererSolde();
    void readAll();
};
/*--------------------------------------------------------------------------------------------------*/
#endif // USERMODEL_H
