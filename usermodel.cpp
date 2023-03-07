#include "usermodel.h"
/*----------------------------------------------------------------------------------------------------------------*/
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlResult>
/*----------------------------------------------------------------------------------------------------------------*/
UserModel::UserModel(DBAccess *dbAccess)
{
    this ->dbAccess = dbAccess;
    clear();
}
/*----------------------------------------------------------------------------------------------------------------*/
void UserModel::create(User user)
{

    dbAccess ->open();
    QSqlQuery query (dbAccess ->database());
    query.prepare("INSERT INTO t_users (nom, prenom,addresse,numeroTelephone,type,login,password,reference,solde,dateJob) VALUES (:nom ,:prenom ,:addresse ,:numeroTelephone ,:type ,:login ,:password ,:reference ,:solde ,:dateJob)");
    query.bindValue(":nom", user.getNom());
    query.bindValue(":prenom", user.getPrenom());
    query.bindValue(":addresse", user.getAddresse());
    query.bindValue(":numeroTelephone", user.getNumeroTelephone());
    query.bindValue(":type", user.getType());
    query.bindValue(":login", user.getLogin());
    query.bindValue(":password", user.getPassword());
    query.bindValue(":reference", user.getReference());
    query.bindValue(":solde", user.getSolde());
    query.bindValue(":dateJob", user.getJob());

    query.exec();

    readAll();
    qDebug () << "User" << user.getNom() << "created successfully!";
    dbAccess  ->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
void UserModel::readAll()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT matricule ,nom ,prenom ,addresse ,numeroTelephone ,login ,type FROM t_users", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(2, Qt::Horizontal, tr("Prénom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Addresse"));
    this->setHeaderData(4, Qt::Horizontal, tr("Telephone N°"));
    this->setHeaderData(5, Qt::Horizontal, tr("Login"));
    this->setHeaderData(6, Qt::Horizontal, tr("Type"));

    qDebug () << "Users displayed successfully!";
    dbAccess->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
void UserModel::update(User user)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("UPDATE t_users SET nom=:nom ,prenom=:prenom ,addresse=:addresse ,numeroTelephone=:numeroTelephone ,login=:login ,password=:password ,reference=:reference ,solde=:solde ,dateJob=:dateJob WHERE  matricule=:matricule");
    query.bindValue(":nom",user.getNom());
    query.bindValue(":prenom",user.getPrenom());
    query.bindValue(":addresse",user.getAddresse());
    query.bindValue(":numeroTelephone",user.getNumeroTelephone());
    query.bindValue(":login",user.getLogin());
    query.bindValue(":password",user.getPassword());
    query.bindValue(":reference",user.getReference());
    query.bindValue(":solde",user.getSolde());
    query.bindValue(":datJob",user.getJob());
    query.bindValue(":matricule",user.getNumeroMatricule());
    query.exec();

    readAll();

    qDebug () << "User" << user.getNom() << " updated successfully!" ;
    dbAccess->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
void UserModel::remove(uint  matricule)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("DELETE FROM t_users WHERE  matricule=:matricule");
    query.bindValue(":matricule",matricule);
    query.exec();

    readAll();

    qDebug () << "User with matricule :" <<  matricule << " has been deleted successfully!" ;
    dbAccess->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
bool UserModel::readBy(QString login)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT  matricule AS Matricule , nom AS Nom, prenom AS Prénom,addresse AS Addresse,numeroTelephone AS Telephone,login AS Login,type AS Type FROM t_users WHERE login=:login");
    query.bindValue(":login", login);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    this->setQuery(query);

    qDebug() << "User with login" << login << "found.";
    dbAccess->close();

    return true;
}
/*----------------------------------------------------------------------------------------------------------------*/
bool UserModel::readByManager()
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT  matricule AS Matricule , nom AS Nom, prenom AS Prénom,addresse AS Addresse,numeroTelephone AS Telephone,login AS Login,type AS Type FROM t_users WHERE type=:manager");
    query.bindValue(":manager", "manager");
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    this->setQuery(query);

    dbAccess->close();

    return true;
}
/*----------------------------------------------------------------------------------------------------------------*/
bool UserModel::readBy(QString login, QString password, User *user)
{
    dbAccess->open();

    QSqlQuery query(dbAccess->database());
    query.prepare("SELECT matricule ,nom ,prenom ,addresse ,numeroTelephone ,type ,login ,reference ,solde ,dateJob FROM t_users WHERE login=:login AND password=:password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    if (false == query.next()) // Aucun enregistrement trouvé
    {
        return false;
    }

    QSqlRecord record = query.record();
    user->setLogin(login);
    user->setPassword(password);
    user->setNumeroMatricule(query.value(record.indexOf("matricule")).toUInt());
    user->setNom(query.value(record.indexOf("nom")).toString());
    user->setPrenom(query.value(record.indexOf("prenom")).toString());
    user->setAddresse(query.value(record.indexOf("addresse")).toString());
    user->setNumeroTel(query.value(record.indexOf("numeroTel")).toString());
    user->setType(query.value(record.indexOf("type")).toString());
    user->setReference(query.value(record.indexOf("reference")).toUInt());
    user->setSolde(query.value(record.indexOf("solde")).toUInt());
    user->setJob(query.value(record.indexOf("dateJob")).toDate());

    qDebug() << "User with name" << user->getNom() << user->getPrenom() << "found.";
    dbAccess->close();

    return true;
}
/*----------------------------------------------------------------------------------------------------------------*/
void UserModel::clear()
{
    dbAccess->open();

    QSqlDatabase database = dbAccess->database();
    this->setQuery("SELECT matricule, nom, prenom,addresse,numeroTelephone, login,type FROM t_users WHERE matricule=-1", database);

    this->setHeaderData(0, Qt::Horizontal, tr("Matricule"));
    this->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    this->setHeaderData(2, Qt::Horizontal, tr("Prénom"));
    this->setHeaderData(3, Qt::Horizontal, tr("Addresse"));
    this->setHeaderData(4, Qt::Horizontal, tr("Telephone N°"));
    this->setHeaderData(5, Qt::Horizontal, tr("Login"));
    this->setHeaderData(6, Qt::Horizontal, tr("Type"));
    dbAccess->close();
}
/*----------------------------------------------------------------------------------------------------------------*/
QString UserModel::getConnection()
{
    return dbAccess->database().connectionName();
}
/*----------------------------------------------------------------------------------------------------------------*/
UserModel::~UserModel()
{
    qDebug() << "UserModel Object has been deleted!";
}
/*----------------------------------------------------------------------------------------------------------------*/
