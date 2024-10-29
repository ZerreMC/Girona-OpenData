// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef PADRO_H
#define PADRO_H

#include <vector>
#include <map>
#include <list>
#include <string>
#include <fstream>
#include "Districte.h"
#include "Eines.h"

using namespace std;

typedef vector<int> ResumEstudis;
typedef vector<int> ResumEdats;
typedef vector<int> ResumNivellEstudis;
typedef vector<int> ResumNacionalitats;

class Padro {
public:
    /**
     * @brief Llegeix les dades del fitxer CSV de la ruta especificada i les emmagatzema.
     *
     * @param path Ruta del fitxer CSV.
     * @return retorna el nombre de files llegides
     * @pre  --
     * @post S'han llegit les files del fitxer CSV i s'han emmagatzemat els valors.
     */
    int llegirDades(const string &path);

    /**
     * @brief Comprova si existeixen dades per a l'any indicat.
     *
     * @param any Any a comprovar.
     * @return `true` si existeixen dades per a l'any, `false` en cas contrari.
     * @pre  --
     * @post Retorna un valor booleà indicant si existeixen dades per a l'any.
     */
    bool existeixAny(int any) const;

    /**
     * @brief Obté el nombre d'habitants per any.
     *
     * @return Un mapa on cada clau és un any i el valor és el nombre d'habitants.
     * @pre  --
     * @post Retorna un `map<int, long>` amb el nombre d'habitants per cada any.
     */
    map<int, long> obtenirNumHabitantsPerAny() const;

    /**
     * @brief Obté el nombre d'habitants per districte en un any específic.
     *
     * @param any Any de referència.
     * @return Un vector amb el nombre d'habitants de cada districte en l'any indicat.
     * @pre  --
     * @post Retorna un `vector<long>` amb els habitants de cada districte en l'any indicat.
     */
    vector<long> obtenirNumHabitantsPerDistricte(int any) const;

    /**
     * @brief Obté el nombre d'habitants per secció d'un any i districte específics.
     *
     * @param any Any de referència.
     * @param districte Districte de referència.
     * @return Un mapa `map<int, long>` amb els habitants de cada secció del districte en l'any indicat.
     * @pre  --
     * @post Retorna un `map<int, long>` amb el nombre d'habitants per cada secció del districte en l'any indicat.
     */
    map<int, long> obtenirNumHabitantsPerSeccio(int any, int districte) const;

    /**
     * @brief Obté un resum dels estudis realitzats per cada any.
     *
     * @return Un `ResumEstudis` que conté els diferents tipus d'estudis realitzats per cada any.
     * @pre  --
     * @post Retorna un `ResumEstudis` amb els tipus d'estudis realitzats pels habitants identificats pel nom.
     */
    ResumEstudis resumEstudis() const;

    /**
     * @brief Obté el nombre d'estudis diferents dels habitants d'un districte en cada any.
     *
     * @param districte Districte de referència.
     * @return Un mapa `map<int, int>` amb el nombre d'estudis diferents per cada any al districte indicat.
     * @pre  --
     * @post Retorna un `map<int, int>` amb el nombre d'estudis diferents dels habitants del districte indicat.
     */
    map<int, int> nombreEstudisDistricte(int districte) const;

    /**
     * @brief Obté el nivell d'estudis promig per cada any i districte.
     *
     * @return Un `ResumNivellEstudis` que conté, per cada any, el nivell d'estudis promig de cada districte.
     * @pre  --
     * @post Retorna un `ResumNivellEstudis` amb el nivell d'estudis promig de cada districte, indicant el districte més estudiós amb un `+` i el menys amb un `-`.
     */
    ResumNivellEstudis resumNivellEstudis() const;

    /**
     * @brief Obté el nombre d'habitants per nacionalitat en cada any.
     *
     * @return Un `ResumNacionalitats` que conté, per cada any, totes les nacionalitats i el nombre d'habitants de cadascuna.
     * @pre  --
     * @post Retorna un `ResumNacionalitats` amb el nombre d'habitants per nacionalitat, ordenat en ordre descendent.
     */
    ResumNacionalitats resumNacionalitats() const;

    /**
     * @brief Obté el nom del districte que concentra més habitants d'una nacionalitat en cada any.
     *
     * @param codiNacionalitat Codi de la nacionalitat.
     * @return Un mapa `map<int, string>` amb el nom del districte per cada any que concentra més habitants d'aquesta nacionalitat.
     * @pre  --
     * @post Retorna un `map<int, string>` amb el districte que concentra més habitants d'aquesta nacionalitat en cada any.
     */
    map<int, string> movimentsComunitat(int codiNacionalitat) const;

    /**
     * @brief Obté l'edat promig per cada any i districte, ordenat per edat promig.
     *
     * @return Un `ResumEdats` amb l'edat promig per cada districte i any, ordenat ascendentment.
     * @pre  --
     * @post Retorna un `ResumEdats` amb l'edat promig per cada districte i any, ordenat ascendentment.
     */
    ResumEdats resumEdat() const;

    /**
     * @brief Obté el districte més envellit per cada any.
     *
     * @return Un mapa `map<int, string>` amb el nom del districte més envellit per cada any.
     * @pre  --
     * @post Retorna un `map<int, string>` amb el districte més envellit de cada any.
     */
    map<int, string> movimentVells() const;

    /**
     * @brief Obté el districte amb l'increment més gran d'habitants joves entre dos anys.
     *
     * @param anyInicial Any inicial.
     * @param anyFinal Any final.
     * @return Un `pair<string, long>` amb el nom del districte i l'increment d'habitants joves.
     * @pre  --
     * @post Retorna un `pair<string, long>` amb el districte amb l'increment més gran d'habitants joves (20-30 anys) entre els anys indicats.
     */
    pair<string, long> mesJoves(int anyInicial, int anyFinal) const;

    /**
     * @brief Obté els estudis dels habitants d'un any, districte, edat i codi de nacionalitat indicats.
     *
     * @param any Any de referència.
     * @param districte Districte de referència.
     * @param edat Edat de referència.
     * @param codiNacionalitat Codi de la nacionalitat.
     * @return Una llista `list<string>` amb els diferents estudis dels habitants amb les característiques indicades.
     * @pre  --
     * @post Retorna una `list<string>` amb els estudis dels habitants que compleixen amb els requisits especificats.
     */
    list<string> estudisEdat(int any, int districte, int edat, int codiNacionalitat) const;

private:
    map<int, vector<Districte> > _districtes;
    ///< Map amb clau com any i un vector de districtes per emmagatzemar les dades per any.

    /**
     * @brief Converteix una cadena de text a enter.
     *
     * @param s Cadena de text a convertir.
     * @return Enter resultant de la conversió o -1 si la cadena no és vàlida.
     */
    int stringToInt(const string &s);

    const vector<string> DISTRICTES = {
        "Carme, Vila-roja", "Eixample, Montilivi", "Santa Eugenia, Mas Xirgu",
        "Casc Antic", "Montjuic, Pont major", "Sant Ponc, Domeny, Taiala"
    }; ///< Vector constant amb els noms dels districtes que no es modificaran.
    const int MIDA = 6; ///< Mida constant del vector DISTRICTES, que representa el nombre total de districtes.
};

#endif // PADRO_H