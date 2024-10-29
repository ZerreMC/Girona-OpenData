// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Districte.h"

void Districte::afegir(int seccio, int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiNacionalitat,
    const string &nomNacionalitat) {

    Persona persona(codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
    _Persones.push_back(persona);

    Estudi estudi(codiNivellEstudis, nivellEstudis);
    _Estudis.insert(estudi);

    Nacionalitat nacionalitat(codiNivellEstudis, nivellEstudis);
    _Nacionalitats.insert(nacionalitat);

    _habitantsSeccio[seccio]++;
}

long Districte::obtenirNumHabitants() const {
    return _Persones.size();
}

double Districte::obtenirEdatMitjana() const {
    return obtenirNumHabitants() / _Persones.size();
}
