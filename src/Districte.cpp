// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Districte.h"

#include "Padro.h"

void Districte::afegir(int seccio, int codiNivellEstudis, const string &nivellEstudis, int anyNaixement,
                       int codiNacionalitat,
                       const string &nomNacionalitat) {
    Persona persona(codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
    _Persones.push_back(persona);

    Estudi estudi(codiNivellEstudis, nivellEstudis);
    _Estudis.insert(estudi);

    Nacionalitat nacionalitat(codiNacionalitat, nomNacionalitat);

    _habitantsPerSeccio[seccio]++;
    _habitantsPerNacio[nacionalitat]++;
}

long Districte::obtenirNumHabitants() const {
    return _Persones.size();
}

double Districte::obtenirEdatMitjana(int any) const {
    double sumEdat = 0.0;
    list<Persona>::const_iterator it = _Persones.begin();
    while (it != _Persones.end()) {
        int edat = any - it->obtenirAnyNaixement();
        sumEdat += edat;
        it++;
    }
    return _Persones.empty() ? 0.0 : sumEdat / _Persones.size();
}

set<string, greater<string>> Districte::resumEstudis() const {
    set<string, greater<string>> estudis;

    for (set<Estudi, greater<Estudi>>::const_iterator estudi = _Estudis.begin(); estudi != _Estudis.end(); estudi++) {
        estudis.insert(estudi->obtenirNom());
    }

    return estudis;
}

long Districte::comptaEdatNacionalitat(int anyNaixement, int codiNacionalitat) const {
    long total = 0;

    list<Persona>::const_iterator it_persona = _Persones.begin();
    while (it_persona != _Persones.end()) {
        if (it_persona->obtenirAnyNaixement() == anyNaixement) {
            if (codiNacionalitat == -1 or it_persona->obtenirCodiPaisNaixement() == codiNacionalitat) {
                total++;
            }
        }
        it_persona++;
    }

    return total;
}

map<int, long> Districte::obtenirHabitantsPerSeccio() const{
    return _habitantsPerSeccio;
}

int Districte::obtenirNivellEstudis() const {
    return _Estudis.size();
}

long Districte::obtenirTotalNivellEstudis() const {
    int total = 0;
    list<Persona>::const_iterator it = _Persones.begin();
    while (it != _Persones.end()) {
        total += it->obtenirCodiNivellEstudis();
        it++;
    }
    return total;
}

unordered_map<Nacionalitat, long> Districte:: obtenirHabitantsPerNacio() const{
    return _habitantsPerNacio;
}

list<Persona> Districte::obtenirPersones() const {
    return _Persones;
}
