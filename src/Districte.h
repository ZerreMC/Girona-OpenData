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
#include <unordered_map>

#include "Estudi.h"
#include "Nacionalitat.h"
#include "Persona.h"

using namespace std;
///< Constant que representa l'any actual per a càlculs relacionats amb l'edat dels habitants.

class Districte {
public:
    /**
     * @brief Constructor per defecte que inicialitza un objecte Districte sense informació.
     *
     * @pre  --
     * @post Inicialitza el Districte amb les estructures de dades buides.
     */
    Districte() = default; ///< serveix per ressoldre l'error de "undefined reference"

    /**
     * @brief Afegeix un habitant a les estructures de dades del Districte.
     *
     * @param seccio Secció del districte on resideix l'habitant.
     * @param codiNivellEstudis Codi del nivell d'estudis de l'habitant.
     * @param nivellEstudis Nom del nivell d'estudis de l'habitant.
     * @param anyNaixement Any de naixement de l'habitant.
     * @param codiNacionalitat Codi de la nacionalitat de l'habitant.
     * @param nomNacionalitat Nom de la nacionalitat de l'habitant.
     * @pre  --
     * @post Afegeix l'habitant amb les característiques indicades als conjunts de dades del Districte.
     */
    void afegir(int seccio, int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiNacionalitat,
                const string &nomNacionalitat);

    /**
     * @brief Obté el nombre d'habitants del Districte.
     *
     * @return Nombre total d'habitants al Districte.
     * @pre  --
     * @post Retorna el nombre d'habitants registrats al Districte.
     */
    long obtenirNumHabitants() const;

    /**
     * @brief Calcula l'edat mitjana dels habitants del Districte.
     *
     * @return Edat mitjana dels habitants del Districte.
     * @pre  --
     * @post Retorna l'edat mitjana calculada dels habitants del Districte.
     */
    double obtenirEdatMitjana(int any) const;

    /**
     * @brief Obté un conjunt amb els diferents tipus d'estudis dels habitants del Districte.
     *
     * @return Un conjunt amb els noms dels estudis únics.
     * @pre  --
     * @post Retorna un conjunt amb els noms dels tipus d'estudis presents al Districte.
     */
    set<string, greater<string> > resumEstudis() const;

    /**
     * @brief Compta el nombre d'habitants nascuts en un any específic i amb una nacionalitat determinada.
     *
     * @param anyNaixement Any de naixement a comptabilitzar.
     * @param codiNacionalitat Codi de la nacionalitat a comptabilitzar.
     * @return Nombre d'habitants que compleixen amb els criteris indicats.
     * @pre  --
     * @post Retorna el nombre d'habitants que han nascut l'any especificat i tenen la nacionalitat indicada.
     */
    long comptaEdatNacionalitat(int anyNaixement, int codiNacionalitat) const;

    map<int, long> obtenirHabitantsPerSeccio() const;

    int obtenirNivellEstudis() const;

    long obtenirTotalNivellEstudis() const;

    unordered_map<Nacionalitat, long> obtenirHabitantsPerNacio() const;

    list<Persona> obtenirPersones() const;

private:
    list<Persona> _Persones; ///< Conjunt de persones que resideixen al districte.
    set<Estudi, greater<Estudi>> _Estudis; ///< Conjunt d'estudis dels habitants del districte per evitar duplicats.

    map<int, long> _habitantsPerSeccio;
    unordered_map<Nacionalitat, long> _habitantsPerNacio; ///< Estructura de dades que conta les persones que
};

#endif // DISTRICTE_H
