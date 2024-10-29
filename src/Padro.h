// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef PADRO_H
#define PADRO_H

#include <vector>
#include <map>
#include <vector>
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
    Padro();
    int llegirDades(const string &path);
    bool existeixAny(int any) const;
    map<int, long> obtenirNumHabitantsPerAny() const;
    vector<long> obtenirNumHabitantsPerDistricte(int any) const;
    map<int, long> obtenirNumHabitantsPerSeccio(int any, int districte) const;
    ResumEstudis resumEstudis() const;
    map<int,int> nombreEstudisDistricte(int districte) const;
    ResumNivellEstudis resumNivellEstudis() const;
    ResumNacionalitats resumNacionalitats() const;
    map<int,string> movimentsComunitat(int codiNacionalitat) const;
    ResumEdats resumEdat() const;
    map<int, string> movimentVells() const;
    pair<string,long> mesJoves(int anyInicial, int anyFinal) const;
    list<string> estudisEdat(int any, int districte, int edat, int codiNacionalitat) const;

private:
    map<int, vector<Districte>> _districtes; // map amb clau com any i un vector de districtes

    int stringToInt(const string &s);

    const vector<string> DISTRICTES = {"Carme, Vila-roja", "Eixample, Montilivi", "Santa Eugenia, Mas Xirgu",
                                       "Casc Antic", "Montjuic, Pont major", "Sant Ponc, Domeny, Taiala"};
    const int MIDA = 6;
};

#endif //PADRO_H