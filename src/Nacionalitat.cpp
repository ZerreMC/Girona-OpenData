// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Nacionalitat.h"

Nacionalitat::Nacionalitat(int id) {
    _id = id;
    _nom = "";
}

Nacionalitat::Nacionalitat(int id, string nom) {
    _id = id;
    _nom = nom;
}

int Nacionalitat::obtenirId() const {
    return _id;
}

string Nacionalitat::obtenirNom() const {
    return _nom;
}

bool Nacionalitat::operator==(const Nacionalitat &nacio) const {
    return _id == nacio._id;
}

bool Nacionalitat::operator>(const Nacionalitat &nacio) const {
    return _id > nacio._id;
}

bool Nacionalitat::operator<(const Nacionalitat &nacio) const {
    return _id < nacio._id;
}
