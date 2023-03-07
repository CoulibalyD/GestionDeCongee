#ifndef USER_H
#define USER_H
#include <QDate>
/*--------------------------------------------------------------------------------------------------*/
#include "QString"
/*--------------------------------------------------------------------------------------------------*/
class User
{
protected:
    uint numeroMatricule;
    QString nom;
    QString prenom;
    QString addresse;
    QString numeroTel;
    QString type;
    QString login;
    QString password;
    uint reference;
    uint solde;
    QDate job;
public:
    //Les differentes constructeurs
    User();
    User(uint ,QString ,QString ,QString ,QString ,QString );
    User(QString ,QString ,QString ,QString ,QString ,QString );
    User(QString ,QString ,QString ,QString ,QString ,QString ,uint );
    User(uint ,QString , QString , QString , QString , QString , QString , uint, uint );
    User(uint ,QString , QString , QString , QString , QString , QString , uint, uint, QDate );

    //Les Getter
    uint getNumeroMatricule (){ return  numeroMatricule;}
    QString getNom(){return nom;}
    QString getPrenom (){ return prenom;}
    QString getAddresse (){return addresse;}
    QString getNumeroTelephone(){return numeroTel;}
    QString getType(){return type;}
    QString getLogin(){return login;}
    QString getPassword(){return password;}
    uint getReference(){return reference;}
    uint getSolde(){return solde;}
    QDate getJob(){ return job ;}
    void setJob(QDate jobs){ job = jobs ;}

    //Les Setters

    void setNumeroMatricule(uint nMatricule){numeroMatricule = nMatricule;}
    void setNom(QString firstname){nom = firstname;}
    void setPrenom(QString lastname){prenom = lastname;}
    void setAddresse(QString address){addresse = address;}
    void setNumeroTel(QString nTel){numeroTel = nTel;}
    void setType(QString type){this->type = type;}
    void setLogin(QString login){this->login = login;}
    void setPassword(QString password){this->password = password;}
    void setReference(uint _reference){this->reference = _reference;}
    void setSolde(uint _solde){this->solde = _solde;}
};
/*--------------------------------------------------------------------------------------------------*/
#endif // USER_H
