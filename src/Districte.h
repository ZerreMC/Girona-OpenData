// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef DISTRICTE_H
#define DISTRICTE_H

#include <string>
#include <list>
#include <set>
#include <iostream>
#include <map>

#include "Estudi.h"
#include "Nacionalitat.h"
#include "Persona.h"

using namespace std;

class Districte
{
public:
    Districte();
    void afegir(int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiNacionalitat, const string &nomNacionalitat);
    long obtenirNumHabitants() const;
    double obtenirEdatMitjana() const;
    list<string> resumEstudis() const;
    list<string> resumNacionalitats() const;
    long comptaEdatNacionalitat(int anyNaixement, int codiNacionalitat) const;

private:
    list<Persona> _Persones; // Llista de persones
    set<Estudi> _Estudis; // Set d'estudis
    set<Nacionalitat> _Nacionalitats; // Set de nacionalitats
    map<int, long> _habitantsSeccio; // Map amb clau com seccio i un long que representa el num. d'habitants

    static const int ANY_ACTUAL = 2024;
};

#endif // DISTRICTE_H