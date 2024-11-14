// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1
#include "Persona.h"

Persona::Persona(int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiPaisNaixement,
                 const string &paisNaixement) {
    _codiNivellEstudis = codiNivellEstudis;
    _nivellEstudis = nivellEstudis;
    _anyNaixement = anyNaixement;
    _codiPaisNaixement = codiPaisNaixement;
    _paisNaixement = paisNaixement;
}

int Persona::obtenirAnyNaixement() const {
    return _anyNaixement;
}

int Persona::obtenirCodiNivellEstudis() const {
    return _codiNivellEstudis;
}

string Persona::obtenirNivellEstudis() const {
    return _nivellEstudis;
}

int Persona::obtenirCodiPaisNaixement() const {
    return _codiPaisNaixement;
}
