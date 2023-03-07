#ifndef EMPLOYEMODEL_H
#define EMPLOYEMODEL_H
#include "conge.h"
#include "dbaccess.h"
/*--------------------------------------------------------------------------------------------------*/
class EmployeModel
{
private:
     DBAccess *dbAccess;
public:
    EmployeModel();
    QString getConnection();
    void createConge(Conge conge);
    ~EmployeModel();
};

/*--------------------------------------------------------------------------------------------------*/
#endif // EMPLOYEMODEL_H
