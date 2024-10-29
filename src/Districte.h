// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef DISTRICTE_H
#define DISTRICTE_H

#include <string>
#include <list>
#include <set>
#include <map>
#include <iostream>

#include "Estudi.h"
#include "Nacionalitat.h"
#include "Persona.h"

using namespace std;

class Districte
{
public:
    // @Pre: --
    // @Post: Constructor per defecte que inicialitza tot sense cap informació extra
    Districte();
    // @Pre: --
    // @Post: Afegeix un habitant a les estructures de dades amb les característiques indicades pels paràmetres
    void afegir(int seccio, int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiNacionalitat, const string &nomNacionalitat);
    // @Pre: --
    // @Post: Retorna el nombre d’habitants del Districte
    long obtenirNumHabitants() const;
    // @Pre: --
    // @Post: Retorna l’edat mitjana dels habitants del Districte
    double obtenirEdatMitjana() const;
    // @Pre: --
    // @Post: Retorna el nom dels tipus d’Estudi que tenen els habitants del Districte
    set<string> resumEstudis() const;
    // @Pre: --
    // @Post: Retorna el nom dels països d’origen dels habitants del Districte
    set<string> resumNacionalitats() const;
    // @Pre: --
    // @Post: Retorna el nombre d’habitants del Districte nascuts l’any anyNaixement al país amb codi codiNacionalitat
    long comptaEdatNacionalitat(int anyNaixement, int codiNacionalitat) const;
    // @Pre: --
    // @Post: Retorna el nombre d'habitants per Seccio
    map<int, long> obtenirHabitantsPerSeccio() const;

private:
    list<Persona> _Persones; // Llista de persones
    set<Estudi> _Estudis; // Set d'estudis
    set<Nacionalitat> _Nacionalitats; // Set de nacionalitats
    map<int, long> _habitantsSeccio; // Map amb clau com seccio i un long que representa el num. d'habitants

    static const int ANY_ACTUAL = 2024; // Es guarda en una constant l'any actual
};

#endif // DISTRICTE_H