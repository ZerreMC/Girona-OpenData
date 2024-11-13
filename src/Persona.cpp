// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1
#include "Persona.h"

Persona::Persona(Estudi estudi, int anyNaixement, Nacionalitat nacionalitat) {
    _estudi = estudi;
    _anyNaixement = anyNaixement;
    _nacionalitat = nacionalitat;
}


int Persona::obtenirAnyNaixement() const {
    return _anyNaixement;
}

string Persona::obtenirNivellEstudis() const {
    return _estudi.obtenirNom();
}

int Persona::obtenirCodiEstudi() const {
        return _estudi.obtenirId();
}

int Persona::obtenirCodiPaisNaixement() const {
    return _nacionalitat.obtenirId();
}
