// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef NACIONALITAT_H
#define NACIONALITAT_H

#include <string>

using namespace std;

class Nacionalitat
{
    public:
        Nacionalitat(int id, string nom);
        int obtenirId() const;
        string obtenirNom() const;
        bool operator==(const Nacionalitat &nacio) const;

    private:
        int _id;
        string _nom;
};

#endif // NACIONALITAT_H
