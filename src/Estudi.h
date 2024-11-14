// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef ESTUDI_H
#define ESTUDI_H

#include <string>

using namespace std;

/**
 * @class Estudi
 * @brief Representa un estudi amb un codi identificador i un nom.
 */
class Estudi {
public:
    Estudi() = default;

    /**
     * @brief Constructor que inicialitza un objecte Estudi amb el codi i nom especificats.
     *
     * @param id Codi identificador de l'estudi.
     * @param nom Nom de l'estudi.
     * @pre  --
     * @post El codi i el nom de l'estudi es guarden als atributs corresponents.
     */
    Estudi(int id, string nom);

    /**
     * @brief Obté el codi identificador de l'estudi.
     *
     * @return Enter que representa el codi de l'estudi.
     * @pre  --
     * @post Retorna el codi de l'estudi.
     */
    int obtenirId() const;

    /**
     * @brief Obté el nom de l'estudi.
     *
     * @return Cadena de text que representa el nom de l'estudi.
     * @pre  --
     * @post Retorna el nom de l'estudi.
     */
    string obtenirNom() const;

    /**
     * @brief Sobrecàrrega de l'operador d'igualtat per comparar dos objectes Estudi.
     *
     * @param estudi Objecte Estudi amb el qual es vol comparar.
     * @return `true` si els dos objectes Estudi tenen el mateix codi, `false` en cas contrari.
     * @pre  --
     * @post Retorna `true` si els codis dels estudis són iguals, `false` en cas contrari.
     */
    bool operator==(const Estudi &estudi) const;

    /**
     * @brief Sobrecàrrega de l'operador major que per comparar dos objectes Estudi.
     *
     * @param estudi Objecte Estudi amb el qual es vol comparar.
     * @return `true` si el codi de l'objecte actual és més gran que el de \p estudi, `false` en cas contrari.
     * @pre  --
     * @post Retorna `true` si el codi de l'objecte actual és major, `false` en cas contrari.
     */
    bool operator>(const Estudi &estudi) const;

    /**
     * @brief Sobrecàrrega de l'operador menor que per comparar dos objectes Estudi.
     *
     * @param estudi Objecte Estudi amb el qual es vol comparar.
     * @return `true` si el codi de l'objecte actual és més petit que el de \p estudi, `false` en cas contrari.
     * @pre  --
     * @post Retorna `true` si el codi de l'objecte actual és menor, `false` en cas contrari.
     */
    bool operator<(const Estudi &estudi) const;

private:
    int _id; ///< Codi identificador de l'estudi.
    string _nom; ///< Nom de l'estudi.
};

#endif // ESTUDI_H
