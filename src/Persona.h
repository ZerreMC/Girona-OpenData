// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona {
public:
    /**
     * @brief Constructor que inicialitza una Persona amb el nivell d'estudis, any de naixement i país de naixement especificats.
     *
     * @param codiNivellEstudis Codi del nivell d'estudis de la persona.
     * @param nivellEstudis Nom del nivell d'estudis de la persona.
     * @param anyNaixement Any de naixement de la persona.
     * @param codiPaisNaixement Codi del país de naixement.
     * @param paisNaixement Nom del país de naixement.
     * @pre  --
     * @post Crea una Persona amb els atributs indicats assignats als atributs corresponents.
     */
    Persona(int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiPaisNaixement,
            const string &paisNaixement);

    /**
     * @brief Obté l'any de naixement de la persona.
     *
     * @return Enter que representa l'any de naixement.
     * @pre  --
     * @post Retorna l'any de naixement de la persona.
     */
    int obtenirAnyNaixement() const;

    /**
     * @brief Obté el nivell d'estudis de la persona.
     *
     * @return Cadena de text que representa el nivell d'estudis.
     * @pre  --
     * @post Retorna el nivell d'estudis de la persona.
     */
    string obtenirNivellEstudis() const;

    /**
     * @brief Obté el codi del país de naixement de la persona.
     *
     * @return Enter que representa el codi del país de naixement.
     * @pre  --
     * @post Retorna el codi del país de naixement de la persona.
     */
    int obtenirCodiPaisNaixement() const;

private:
    int _codiNivellEstudis; ///< Codi del nivell d'estudis de la persona.
    int _anyNaixement; ///< Any de naixement de la persona.
    int _codiPaisNaixement; ///< Codi del país de naixement de la persona.
    string _nivellEstudis; ///< Nom del nivell d'estudis de la persona.
    string _paisNaixement; ///< Nom del país de naixement de la persona.
};

#endif // PERSONA_H
