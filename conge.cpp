#include "conge.h"
/*----------------------------------------------------------------------------------------------------------------*/
Conge::Conge(){}
/*--------------------------------------------------------------------------------------------------*/
Conge::Conge(uint matricule,QString nom,QString prenom,QString typeConge,QDate debut,QDate fin):
 matriculeDemandeur(matricule),nomDemandeur(nom),prenomDemandeur(prenom),typeconge(typeConge),dateDebut(debut),dateFin(fin)
{}
/*--------------------------------------------------------------------------------------------------*/
Conge::Conge(uint id,uint matricule,QString nom,QString prenom,QString typeconge,QDate debut,QDate fin):
   idConge(id),matriculeDemandeur(matricule),nomDemandeur(nom),prenomDemandeur(prenom),typeconge(typeconge),dateDebut(debut),dateFin(fin)
{}
/*--------------------------------------------------------------------------------------------------*/
Conge::Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin):
   idConge(id),matriculeDemandeur(matricule),nomDemandeur(nom),prenomDemandeur(prenom),typeconge(typeConge),statusConge(status),dateDebut(debut),dateFin(fin)
{}
/*--------------------------------------------------------------------------------------------------*/
Conge::Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin,uint _reference):
   idConge(id),matriculeDemandeur(matricule),nomDemandeur(nom),prenomDemandeur(prenom),typeconge(typeConge),statusConge(status),dateDebut(debut),dateFin(fin),reference(_reference)
{}

Conge::Conge(uint id,uint matricule,QString nom,QString prenom,QString typeConge,QString status,QDate debut,QDate fin,QString _motif,uint _reference):
    idConge(id),matriculeDemandeur(matricule),nomDemandeur(nom),prenomDemandeur(prenom),typeconge(typeConge),statusConge(status),dateDebut(debut),dateFin(fin),motif(_motif),reference(_reference)
{}

/*--------------------------------------------------------------------------------------------------*/
Conge::~Conge()
{}
/*--------------------------------------------------------------------------------------------------*/
