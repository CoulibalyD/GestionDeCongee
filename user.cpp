#include "user.h"
/*--------------------------------------------------------------------------------------------------*/
User::User()
{}
/*--------------------------------------------------------------------------------------------------*/
User::User(uint _numeroMatricule,QString _nom,QString _prenom,QString _address,QString _login,QString _password):
    numeroMatricule(_numeroMatricule),nom(_nom),prenom(_prenom),addresse(_address),login(_login),password(_password){}
User::User(QString _nom,QString _prenom,QString _address,QString _numeroTel,QString _login,QString _password):
    nom(_nom),prenom(_prenom),addresse(_address),numeroTel(_numeroTel),login(_login),password(_password){}
/*--------------------------------------------------------------------------------------------------*/
User::User(QString _nom, QString _prenom, QString _address, QString _numero, QString _login, QString _password, uint _reference):
User(_nom,_prenom,_address,_numero,_login,_password)
{
    reference = _reference;
}
/*--------------------------------------------------------------------------------------------------*/
User::User(uint _numeroM,QString _nom, QString _prenom, QString _address, QString _numero, QString _login, QString _password, uint _reference, uint _solde):
 numeroMatricule(_numeroM), nom(_nom),prenom(_prenom),addresse(_address),numeroTel(_numero),login(_login),password(_password),reference(_reference),solde(_solde)
{}
/*--------------------------------------------------------------------------------------------------*/
User::User(uint _numeroM,QString _nom, QString _prenom, QString _address, QString _numero, QString _login, QString _password, uint _reference, uint _solde, QDate _date):
 numeroMatricule(_numeroM), nom(_nom),prenom(_prenom),addresse(_address),numeroTel(_numero),login(_login),password(_password),reference(_reference),solde(_solde)
{
    job = _date;
}
/*--------------------------------------------------------------------------------------------------*/
