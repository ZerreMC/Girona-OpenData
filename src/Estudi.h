// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef ESTUDI_H
#define ESTUDI_H

#include <string>

using namespace std;

class Estudi
{
    public:
        Estudi(int id, string nom);
        int obtenirId() const;
        string obtenirNom() const;
        bool operator==(const Estudi &estudi) const;

    private:
        int _id;
        string _nom;
    
};

#endif // ESTUDI_H