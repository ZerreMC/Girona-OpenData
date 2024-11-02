// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Estudi.h"

Estudi::Estudi(int id, string nom) {
    _id = id;
    _nom = nom;
}

int Estudi::obtenirId() const {
    return _id;
}

string Estudi::obtenirNom() const {
    return _nom;
}

bool Estudi::operator==(const Estudi &estudi) const {
    return _id == estudi._id;
}

bool Estudi::operator>(const Estudi &estudi) const {
    return _id > estudi._id;
}

bool Estudi::operator<(const Estudi &estudi) const {
    return _id < estudi._id;
}
