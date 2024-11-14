// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef NACIONALITAT_H
#define NACIONALITAT_H

#include <string>

using namespace std;

class Nacionalitat {
public:
    Nacionalitat() = default;

    Nacionalitat(int id);

    /**
     * @brief Constructor que inicialitza una nacionalitat amb un codi i un nom especificats.
     *
     * @param id Codi identificador de la nacionalitat.
     * @param nom Nom del país de la nacionalitat.
     * @pre  --
     * @post El codi i el nom de la nacionalitat es guarden en els atributs corresponents.
     */
    Nacionalitat(int id, string nom);

    /**
     * @brief Obté el codi identificador del país.
     *
     * @return Enter que representa el codi del país.
     * @pre  --
     * @post Retorna el codi del país.
     */
    int obtenirId() const;

    /**
     * @brief Obté el nom del país.
     *
     * @return Cadena de text que representa el nom del país.
     * @pre  --
     * @post Retorna el nom del país.
     */
    string obtenirNom() const;

    /**
     * @brief Sobrecàrrega de l'operador d'igualtat per comparar dues nacionalitats.
     *
     * @param nacio Objecte Nacionalitat amb el qual es vol comparar.
     * @return `true` si les dues nacionalitats tenen el mateix codi, `false` en cas contrari.
     * @pre  --
     * @post Retorna `true` si els codis de les nacionalitats són iguals, `false` en cas contrari.
     */
    bool operator==(const Nacionalitat &nacio) const;

    bool operator>(const Nacionalitat &nacio) const;

    bool operator<(const Nacionalitat &nacio) const;

private:
    int _id; ///< Codi identificador del país.
    string _nom; ///< Nom del país de la nacionalitat.
};

// Especialització del hash en el std per fer-ho global.
// Sino no es pot declarar un unordered_map d'una classe per default
namespace std {
    template<>
    struct hash<Nacionalitat> {
        size_t operator()(const Nacionalitat &n) const {
            return std::hash<int>()(n.obtenirId());
        }
    };
}

#endif // NACIONALITAT_H
