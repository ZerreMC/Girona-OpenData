// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona
{
    public:
    // CONSTRUCTOR
        Persona(int codiNivellEstudis, const string &nivellEstudis, int anyNaixement, int codiPaisNaixement, const string &paisNaixement);
    // CONSULTORS
        int obtenirAnyNaixement() const;
        string obtenirNivellEstudis() const;
        int obtenirCodiPaisNaixement() const;

    private:
        int _codiNivellEstudis, _anyNaixement, _codiPaisNaixement;
        string _nivellEstudis, _paisNaixement;
};

#endif // PERSONA_H
