#ifndef DBACCESS_H
#define DBACCESS_H
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlDriver>
#include <QSqlQuery>

/*----------------------------------------------------------------------------------------------------------------*/
class DBAccess
{
private:
    static DBAccess* instance; // The single instance
    QSqlDatabase db;
public:
    DBAccess(); // private constructor
    ~DBAccess(); // private destructor

public:
    QSqlDatabase database() { return db; }

    bool open();
    void close();

    // How to get the single instance of DBAccess
    static DBAccess* getInstance();

    // How the release the single instance of DBAccess
    static void release();

};
/*----------------------------------------------------------------------------------------------------------------*/
#endif // DBACCESS_H
