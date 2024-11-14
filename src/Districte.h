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

/**
 * @class Districte
 * @brief Representa un districte que conté informació sobre els habitants, estudis, seccions i nacionalitats.
 */
class Districte {
public:
    /**
     * @brief Constructor per defecte que inicialitza un objecte Districte sense informació.
     *
     * @pre  --
     * @post Inicialitza el Districte amb les estructures de dades buides.
     */
    Districte() = default; ///< Serveix per resoldre l'error de "undefined reference".

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
     * @param any Any de referència per al càlcul de l'edat.
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

    /**
     * @brief Obté un mapa amb el nombre d'habitants per secció al Districte.
     *
     * @return Mapa amb la clau com el número de secció i el valor com el nombre d'habitants.
     * @pre  --
     * @post Retorna el mapa amb el nombre d'habitants per cada secció.
     */
    map<int, long> obtenirHabitantsPerSeccio() const;

    /**
     * @brief Obté el nombre de nivells d'estudis diferents al Districte.
     *
     * @return Nombre de nivells d'estudis diferents.
     * @pre  --
     * @post Retorna el nombre de nivells d'estudis registrats al Districte.
     */
    int obtenirNivellEstudis() const;

    /**
     * @brief Obté la suma total dels codis de nivells d'estudis dels habitants del Districte.
     *
     * @return Suma total dels codis dels nivells d'estudis.
     * @pre  --
     * @post Retorna la suma total dels codis dels nivells d'estudis.
     */
    long obtenirTotalNivellEstudis() const;

    /**
     * @brief Obté una taula amb el nombre d'habitants per nacionalitat.
     *
     * @return Un mapa no ordenat amb els objectes Nacionalitat com a clau i el nombre d'habitants com a valor.
     * @pre  --
     * @post Retorna la taula d'habitants per nacionalitat.
     */
    unordered_map<Nacionalitat, long> obtenirHabitantsPerNacio() const;

    /**
     * @brief Obté la llista de persones registrades al Districte.
     *
     * @return Llista d'objectes Persona.
     * @pre  --
     * @post Retorna la llista de persones registrades al Districte.
     */
    list<Persona> obtenirPersones() const;

private:
    list<Persona> _Persones; ///< Conjunt de persones que resideixen al districte.
    set<Estudi, greater<Estudi> > _Estudis; ///< Conjunt d'estudis dels habitants del districte per evitar duplicats.
    map<int, long> _habitantsPerSeccio; ///< Mapa amb el nombre d'habitants per secció.
    unordered_map<Nacionalitat, long> _habitantsPerNacio; ///< Mapa amb el nombre d'habitants per nacionalitat.
};

#endif // DISTRICTE_H
