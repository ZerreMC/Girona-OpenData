// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Districte.h"

void Districte::afegir(int seccio, int codiNivellEstudis, const string &nivellEstudis, int anyNaixement,
                       int codiNacionalitat,
                       const string &nomNacionalitat) {
    Persona persona(codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
    _Persones.push_back(persona);

    Estudi estudi(codiNivellEstudis, nivellEstudis);
    _Estudis.insert(estudi);

    Nacionalitat nacionalitat(codiNacionalitat, nomNacionalitat);
    _Nacionalitats.insert(nacionalitat);

    _habitantsPerSeccio[seccio]++;
    _habitantsPerNacio[nacionalitat]++;
}

long Districte::obtenirNumHabitants() const {
    return _Persones.size();
}

double Districte::obtenirEdatMitjana() const {
    double sumEdat = 0.0;
    list<Persona>::const_iterator it = _Persones.begin();
    while (it != _Persones.end()) {
        sumEdat += ANY_ACTUAL - it->obtenirAnyNaixement();
        it++;
    }
    return _Persones.empty() ? 0.0 : sumEdat / _Persones.size();
}

set<string, greater<string>> Districte::resumEstudis() const {
    set<string, greater<string>> estudis;
    set<Estudi, greater<Estudi>>::const_iterator it = _Estudis.begin();

    while (it != _Estudis.end()) {
        estudis.insert(it->obtenirNom());
        it++;
    }

    return estudis;
}

set<string, greater<string>> Districte::resumNacionalitats() const {
    set<string, greater<string>> nacionalitats;
    set<Nacionalitat, greater<Nacionalitat>>::const_iterator it = _Nacionalitats.begin();

    while (it != _Nacionalitats.end()) {
        nacionalitats.insert(it->obtenirNom());
        it++;
    }

    return nacionalitats;
}

// FALTA IMPLEMENTAR
long Districte::comptaEdatNacionalitat(int anyNaixement, int codiNacionalitat) const {
    long total = 0;

    return total;
}

map<int, long> Districte::obtenirHabitantsPerSeccio() const {
    return map<int, long>(_habitantsPerSeccio.begin(), _habitantsPerSeccio.end());
}

int Districte::obtenirNivellEstudis() const {
    return _Estudis.size();
}

long Districte::obtenirTotalNivellEstudis() const {
    int total = 0;
    set<Estudi, greater<Estudi>>::const_iterator it = _Estudis.begin();
    while (it != _Estudis.end()) {
        total += it->obtenirId();
        it++;
    }
    return total;
}

unordered_map<Nacionalitat, long> Districte:: obtenirHabitantsPerNacio() const{
    return _habitantsPerNacio;
}
