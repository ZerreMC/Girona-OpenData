// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef PADRO_H
#define PADRO_H

#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include "Districte.h"
#include "eines.h"

using namespace std;

typedef map<int, set<string, greater<string>>> ResumEstudis;
typedef map<int, set<pair<double, string>>> ResumEdats;
typedef map<int, vector<pair<char, double>>> ResumNivellEstudis;
typedef map<int, multimap<long, Nacionalitat, greater<long>>> ResumNacionalitats;

const vector<string> DISTRICTES = {
    "", "Carme, Vila-roja", "Eixample, Montilivi", "Santa Eugenia, Mas Xirgu",
    "Casc Antic", "Montjuic, Pont major", "Sant Ponc, Domeny, Taiala"
}; ///< Vector constant que conté els noms dels districtes, sense possibilitat de modificació.

/**
 * @class Padro
 * @brief Classe que gestiona les dades del padró municipal de Girona, permetent la lectura i consulta d'informació
 * relacionada amb els habitants, districtes, estudis, nacionalitats, i altres aspectes demogràfics.
 */
class Padro {
public:
    /**
     * @brief Constructor per defecte que inicialitza un objecte Padro buit.
     *
     * @pre  --
     * @post Inicialitza l'objecte Padro sense dades carregades.
     */
    Padro();

    /**
     * @brief Llegeix les dades del fitxer CSV de la ruta especificada i les emmagatzema.
     *
     * @param path Ruta del fitxer CSV.
     * @return Enter que indica el nombre de files llegides correctament.
     * @pre  --
     * @post S'han llegit les files del fitxer CSV i s'han emmagatzemat els valors. Retorna el nombre de files llegides.
     */
    int llegirDades(const string &path);

    /**
     * @brief Comprova si existeixen dades per a un any específic.
     *
     * @param any Any a comprovar.
     * @return `true` si existeixen dades per a l'any indicat, `false` en cas contrari.
     * @pre  --
     * @post Retorna `true` si existeixen dades per a l'any, `false` altrament.
     */
    bool existeixAny(int any) const;

    /**
     * @brief Obté el nombre d'habitants per cada any registrat.
     *
     * @return Un mapa amb l'any com a clau i el nombre d'habitants com a valor.
     * @pre  --
     * @post Retorna un mapa amb el nombre total d'habitants per cada any registrat.
     */
    map<int, long> obtenirNumHabitantsPerAny() const;

    /**
     * @brief Obté el nombre d'habitants per districte en un any específic.
     *
     * @param any Any de referència.
     * @return Un vector amb el nombre d'habitants de cada districte per l'any indicat.
     * @pre  --
     * @post Retorna un vector amb els habitants de cada districte en l'any indicat.
     */
    vector<long> obtenirNumHabitantsPerDistricte(int any) const;

    /**
     * @brief Obté el nombre d'habitants per secció en un any i districte específics.
     *
     * @param any Any de referència.
     * @param districte Districte de referència.
     * @return Un mapa amb el número de secció com a clau i el nombre d'habitants com a valor.
     * @pre  --
     * @post Retorna un mapa amb el nombre d'habitants per cada secció en l'any i districte indicats.
     */
    map<int, long> obtenirNumHabitantsPerSeccio(int any, int districte) const;

    /**
     * @brief Obté un resum dels estudis realitzats per cada any.
     *
     * @return Un `ResumEstudis` amb els nivells d'estudis de cada any.
     * @pre  --
     * @post Retorna un `ResumEstudis` amb els estudis registrats per cada any.
     */
    ResumEstudis resumEstudis() const;

    /**
     * @brief Obté el nombre d'estudis diferents per any en un districte específic.
     *
     * @param districte Districte de referència.
     * @return Un mapa amb l'any com a clau i el nombre d'estudis diferents com a valor.
     * @pre  --
     * @post Retorna un mapa amb el nombre d'estudis per cada any en el districte especificat.
     */
    map<int, int> nombreEstudisDistricte(int districte) const;

    /**
     * @brief Obté el resum del nivell d'estudis per cada any, identificant el districte amb el nivell més alt i més baix.
     *
     * @return Un `ResumNivellEstudis` que conté el nivell d'estudis promig per cada districte i any.
     * @pre  --
     * @post Retorna un `ResumNivellEstudis` amb el districte més estudiós (+) i el menys (-) per cada any.
     */
    ResumNivellEstudis resumNivellEstudis() const;

    /**
     * @brief Obté un resum de les nacionalitats per cada any.
     *
     * @return Un `ResumNacionalitats` amb la quantitat d'habitants per cada nacionalitat, ordenat descendentment.
     * @pre  --
     * @post Retorna un `ResumNacionalitats` amb les nacionalitats i els seus habitants per cada any.
     */
    ResumNacionalitats resumNacionalitats() const;

    /**
     * @brief Obté el districte amb més habitants d'una comunitat específica per any.
     *
     * @param codiNacionalitat Codi de la nacionalitat a buscar.
     * @return Un mapa amb l'any com a clau i el nom del districte amb més habitants de la comunitat com a valor.
     * @pre  --
     * @post Retorna un mapa amb el districte amb més habitants de la nacionalitat especificada per cada any.
     */
    map<int, string> movimentsComunitat(int codiNacionalitat) const;

    /**
     * @brief Obté un resum de l'edat promig dels habitants per districte en cada any.
     *
     * @return Un `ResumEdats` amb l'edat promig per cada districte en cada any.
     * @pre  --
     * @post Retorna un `ResumEdats` ordenat per edat promig de menor a major.
     */
    ResumEdats resumEdat() const;

    /**
     * @brief Obté el districte més envellit per cada any.
     *
     * @return Un mapa amb l'any com a clau i el nom del districte més envellit com a valor.
     * @pre  --
     * @post Retorna un mapa amb el districte més envellit per cada any.
     */
    map<int, string> movimentVells() const;

    /**
     * @brief Obté el districte amb el major increment de població jove entre dos anys.
     *
     * @param anyInicial Any inicial per comparar.
     * @param anyFinal Any final per comparar.
     * @return Un `pair<string, long>` amb el nom del districte i l'increment de joves.
     * @pre  --
     * @post Retorna un `pair<string, long>` amb el districte amb el major increment de joves entre els anys indicats.
     */
    pair<string, long> mesJoves(int anyInicial, int anyFinal) const;

    /**
     * @brief Obté una llista dels estudis dels habitants d'un any, districte, edat i codi de nacionalitat específics.
     *
     * @param any Any de referència.
     * @param districte Districte de referència.
     * @param edat Edat de referència.
     * @param codiNacionalitat Codi de la nacionalitat.
     * @return Una `list<string>` amb els estudis dels habitants que compleixen les condicions especificades.
     * @pre  --
     * @post Retorna una llista amb els estudis que compleixen els criteris especificats.
     */
    list<string> estudisEdat(int any, int districte, int edat, int codiNacionalitat) const;

private:
    map<int, vector<Districte>> _districtes; ///< Map que associa cada any amb un vector de districtes.
    map<int, long> _habitantsPerAny; ///< Mapa que manté el nombre total d'habitants per cada any.

    /**
     * @brief Converteix una cadena de text a un enter si és possible.
     *
     * @param s Cadena de text a convertir.
     * @return Enter resultant de la conversió o -1 si no és vàlid.
     * @pre --
     * @post Retorna l'enter si la conversió és vàlida; en cas contrari, retorna -1.
     */
    int stringToInt(const string &s);

    /**
     * @brief Processa una línia de dades i l'emmagatzema si és vàlida.
     *
     * @param items Vector de cadenes que representa una línia de dades.
     * @return `true` si s'ha processat correctament, `false` si conté errors.
     * @pre --
     * @post La línia és processada i emmagatzemada si és correcta; retorna `false` si té errors.
     */
    bool processarLinia(vector<string> &items);

    /**
     * @brief Verifica si les dades d'una línia són correctes.
     *
     * @param any Any de les dades.
     * @param districte Districte de les dades.
     * @param seccio Secció de les dades.
     * @param codiNivellEstudis Codi del nivell d'estudis.
     * @param nivellEstudis Nom del nivell d'estudis.
     * @param anyNaixement Any de naixement.
     * @param codiNacionalitat Codi de la nacionalitat.
     * @param nomNacionalitat Nom de la nacionalitat.
     * @return `true` si totes les dades són correctes, `false` en cas contrari.
     * @pre --
     * @post Retorna `true` si les dades compleixen els criteris de validació.
     */
    bool dadesCorrectes(int any, int districte, int seccio, int codiNivellEstudis, const string &nivellEstudis,
                        int anyNaixement, int codiNacionalitat, const string &nomNacionalitat) const;

    /**
     * @brief Afegeix dades processades al mapa `_districtes`.
     *
     * @param any Any de referència.
     * @param districte Districte de referència.
     * @param seccio Secció de referència.
     * @param codiNivellEstudis Codi del nivell d'estudis.
     * @param nivellEstudis Nom del nivell d'estudis.
     * @param anyNaixement Any de naixement.
     * @param codiNacionalitat Codi de la nacionalitat.
     * @param nomNacionalitat Nom de la nacionalitat.
     * @pre Les dades han de ser vàlides.
     * @post Les dades s'afegeixen correctament al mapa `_districtes`.
     */
    void afegirDades(int any, int districte, int seccio, int codiNivellEstudis, const string &nivellEstudis,
                     int anyNaixement, int codiNacionalitat, const string &nomNacionalitat);

    const int MIDA = 7; ///< Mida que indica el nombre de districtes.
};

#endif // PADRO_H
