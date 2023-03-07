#ifndef CONGE_H
#define CONGE_H
/*--------------------------------------------------------------------------------------------------*/
#include <QString>
#include <QDate>
#include <QDebug>

/*--------------------------------------------------------------------------------------------------*/
class Conge
{
 private:
    uint idConge;
    uint matriculeDemandeur;
    QString nomDemandeur;
    QString prenomDemandeur;
    QString typeconge;
    QString statusConge;
    QDate dateDebut;
    QDate dateFin;
    QString motif;
    uint reference;

public:

    Conge();
    Conge(uint matricule,QString nom,QString prenom,QString typeConge,QDate debut,QDate fin);
    Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QDate debut,QDate fin);
    Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin);
    Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin,uint );
    Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin,QString _motif,uint _reference );


    uint getIdConge(){return idConge;}
    uint getReference(){return reference;}
    uint getMatriculedemandeur(){ return matriculeDemandeur;}
    QString getNomDemandeur(){return nomDemandeur;}
    QString getPrenomDemandeur(){return prenomDemandeur;}
    QString getTypeConge(){return typeconge;}
    QString getStatus(){return statusConge;}
    QDate getDateDebut(){return dateDebut;}
    QDate getDateFin(){return dateFin;}
    QString getMotif(){return motif;}
    void setIdconge(uint idconges){idConge = idconges;}
    void setIddemandeur(uint iddemande){matriculeDemandeur = iddemande;}
    void setNom(QString nom){nomDemandeur = nom;}
    void setPrenom(QString prenom){prenomDemandeur = prenom;}
    void setTypeConge(QString type){typeconge = type;}
    void setDateDebut(QDate dateD){dateDebut = dateD;}
    void setDateFin(QDate dateF){dateFin = dateF;}
    void setStatus(QString stat){ statusConge = stat;}
    void setMotif(QString _motif){motif = _motif;}
    void setRefence(uint _reference){reference = _reference;}
     ~Conge();

};
/*--------------------------------------------------------------------------------------------------*/
#endif // CONGE_H
