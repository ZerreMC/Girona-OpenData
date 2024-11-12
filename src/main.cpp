// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include <fstream>
#include <iomanip>
#include <iostream>
#include "Padro.h"

using namespace std;

void llegir_dades(Padro &padro) {
    cout << "*******************" << endl;
    cout << "* 1: Llegir dades *" << endl;
    cout << "*******************" << endl;

    string path;
    cin >> path;
    cout << "Numero de linies: " << padro.llegirDades(path) << endl;
}

void existeixAny(const Padro &padro) {
    cout << "********************" << endl;
    cout << "* 02: Existeix any *" << endl;
    cout << "********************" << endl;

    int any;
    cin >> any;
    cout << "Any:" << any << endl;
    if (padro.existeixAny(any))
        cout << "Any existent" << endl;
    else
        cout << "Any inexistent" << endl;
}

void obtenirNHabitants(const Padro &padro) {
    cout << "**********************************" << endl;
    cout << "* 03: Obtenir nombre d'habitants *" << endl;
    cout << "**********************************" << endl;

    map<int, long> habitants = padro.obtenirNumHabitantsPerAny();
    map<int, long>::iterator it = habitants.begin();

    double promig = 0;
    int n = 0;
    while (it != habitants.end()) {
        cout << it->first << setw(13) << "habitants:" << setw(7) << it->second << endl;
        promig += it->second;
        n++, it++;
    }
    cout << "PROMIG: " << fixed << setprecision(2) << promig / n << endl;
}

void nHabitantsUnAny(const Padro &padro) {
    cout << "*******************************************" << endl;
    cout << "* 04: Obtenir nombre d'habitants d'un any *" << endl;
    cout << "*******************************************" << endl;

    int any;
    cout << "Any:";
    cin >> any;

    vector<long> habitants = padro.obtenirNumHabitantsPerDistricte(any);
    int total = 0;
    for (int i = 1; i < habitants.size(); i++) {
        cout << "Districte " << i << setw(13) << "habitants:" << setw(7) << habitants[i] << endl;
        total += habitants[i];
    }
    cout << "TOTAL : " << total << endl;
}

void nHabitantsUnAnyUnDistricte(const Padro &padro) {
    cout << "*******************************************************" << endl;
    cout << "* 05: Obtenir nombre d'habitants d'un any i districte *" << endl;
    cout << "*******************************************************" << endl;

    int any, districte;
    map<int, long> habitants;

    // Bucle per validar l'any
    cin >> any;
    while (!padro.existeixAny(any)) {
        cerr << "ERROR any " << any << " inexistent" << endl;
        cin >> any;
    }

    // Bucle per validar el districte
    cin >> districte;
    habitants = padro.obtenirNumHabitantsPerSeccio(any, districte);
    while (habitants.empty()) {
        cerr << "ERROR districte " << districte << " inexistent" << endl;
        cin >> districte;
        habitants = padro.obtenirNumHabitantsPerSeccio(any, districte);
    }

    // Mostrar el nombre d'habitants per secció si any i districte són vàlids
    cout << "Any:" << any << "  Districte:" << districte << endl;
    long totalHabitants = 0;
    for (const auto &entry: habitants) {
        cout << "Seccio " << entry.first
                << setw(13) << "habitants:" << setw(7) << entry.second << endl;
        totalHabitants += entry.second;
    }

    cout << "TOTAL : " << totalHabitants << endl;
}

void mostrarResumEstudis(const Padro &padro) {
    cout << "*************************" << endl;
    cout << "* 06: Resum per estudis *" << endl;
    cout << "*************************" << endl;

    ResumEstudis resum = padro.resumEstudis();

    ResumEstudis::const_iterator anyEstudis = resum.begin();
    while (anyEstudis != resum.end()) {
        int any = anyEstudis->first;
        const set<string, greater<string> > &estudis = anyEstudis->second;

        cout << any << "  Estudis:";

        bool primer = true;
        // Itera sobre el set d'estudis
        set<string, greater<string> >::const_iterator it = estudis.begin();
        while (it != estudis.end()) {
            if (not primer) {
                cout << " -- ";
            } else {
                primer = false;
            }
            cout << *it;
            it++;
        }
        cout << endl;
        anyEstudis++;
    }
}

void nEstudisDistricte(const Padro &padro) {
    cout << "**************************************" << endl;
    cout << "* 07: Nombre d'estudis per districte *" << endl;
    cout << "**************************************" << endl;
    int districte;
    cout << "Districte:";
    cin >> districte;

    map<int, int> habitants = padro.nombreEstudisDistricte(districte);
    map<int, int>::iterator it = habitants.begin();
    while (it != habitants.end()) {
        cout << "Any " << it->first << "  Num Estudis:" << it->second << endl;
        it++;
    }
}

// TE UN ERROR DE CALCUL EN EL PROMIG
void resumNivellEstudis(const Padro &padro) {
    cout << "******************************" << endl;
    cout << "* 08: Resum nivell d'estudis *" << endl;
    cout << "******************************" << endl;

    ResumNivellEstudis resum = padro.resumNivellEstudis();

    map<int, vector<pair<char, double> > >::const_iterator it = resum.begin();
    while (it != resum.end()) {
        int any = it->first;
        cout << any << ":" << endl;

        const vector<pair<char, double> > &distritos = it->second;
        for (int i = 1; i < distritos.size(); i++) {
            char simbol = distritos[i].first;
            double promig = distritos[i].second;

            cout << "\t   " << simbol << " ";
            cout << DISTRICTES[i] << setw(32) << right << "Promig Estudis: " << setw(10) << fixed << setprecision(2) <<
                    promig << endl;
        }
        it++;
    }
}

void resumNacionalitats(const Padro &padro) {
    cout << "******************************" << endl;
    cout << "* 09: Resum de nacionalitats *" << endl;
    cout << "******************************" << endl;

    ResumNacionalitats resum = padro.resumNacionalitats();
    map<int, multimap<long, Nacionalitat, greater<long> > >::const_iterator it_Any = resum.begin();

    // Recorre cada any
    while (it_Any != resum.end()) {
        cout << it_Any->first << endl;

        multimap<long, Nacionalitat, greater<long> >::const_iterator it_Nacio = it_Any->second.begin();
        // Recorre cada nacionalitat d'un any
        while (it_Nacio != it_Any->second.end()) {
            cout << "\t   " << left << setw(30) << it_Nacio->second.obtenirNom()
                    << "(" << it_Nacio->second.obtenirId() << ") :";
            cout << right << setw(10) << it_Nacio->first << endl;
            it_Nacio++;
        }
        it_Any++;
    }
}

void movimentsUnaComunitat(const Padro &padro) {
    cout << "*********************************" << endl;
    cout << "* 10: Movimente d'una comunitat *" << endl;
    cout << "*********************************" << endl;

    int codiNacionalitat;
    cin >> codiNacionalitat;
    cout << "Codi Nacionalitat:" << codiNacionalitat << endl;

    map<int, string> resumHabitants = padro.movimentsComunitat(codiNacionalitat);
    map<int, string>::const_iterator it_Any = resumHabitants.begin();
    while (it_Any != resumHabitants.end()) {
        int any = it_Any->first;
        const string &districte = it_Any->second;
        cout << any << setw(30) << districte << endl;
        it_Any++;
    }
}

void resumEdats(const Padro &padro) {
    cout << "*********************" << endl;
    cout << "* 11: Resum d'edats *" << endl;
    cout << "*********************" << endl;

    ResumEdats resum = padro.resumEdat();
    map<int, vector<double> >::const_iterator it_any = resum.begin();

    while (it_any != resum.end()) {
        int any = it_any->first;
        cout << any << ":" << endl;

        const vector<double> &edatsPromig = it_any->second;

        for (int i = 0; i < edatsPromig.size(); ++i) {
            string nomDistricte = DISTRICTES[i + 1];
            cout << "       " << setw(30) << left << nomDistricte
                    << "Promig Edat: " << setw(10) << right << fixed << setprecision(2) << edatsPromig[i] << endl;
        }
        it_any++;
    }
}

// TE UN ERROR DE CALCUL DE VELLS
void movimentsVells(const Padro &padro) {
    cout << "****************************" << endl;
    cout << "* 12: Moviments dels vells *" << endl;
    cout << "****************************" << endl;

    // Obtenim el districte més envellit per cada any
    map<int, string> resumVells = padro.movimentVells();
    map<int, string>::const_iterator it_any = resumVells.begin();

    while (it_any != resumVells.end()) {
        int any = it_any->first;
        const string &districte = it_any->second;

        cout << any << setw(30) << districte << endl;
        it_any++;
    }
}

void mesJoves(const Padro &padro) {
    cout << "*****************" << endl;
    cout << "* 13: Més joves *" << endl;
    cout << "*****************" << endl;
    int anyInicial, anyFinal;
    cin >> anyInicial >> anyFinal;
    cout << "Any Inicial: " << anyInicial << "  Any Final: " << anyFinal << endl;

    pair<string, long> mesJoves = padro.mesJoves(anyInicial, anyFinal);
    cout << mesJoves.first << "\t " << mesJoves.second << endl;
}

// ERROR AL MOSTRAR CORRECTAMENT A LA PERSONA
void estudisAnyDistricteEdatNacionalitat(const Padro &padro) {
    cout << "********************************************" << endl;
    cout << "* 14: Estudis any, districte, edat i nació *" << endl;
    cout << "********************************************" << endl;

    int any, districte, edat, codiNacionalitat;
    cin >> any;
    cin >> districte;
    cin >> edat;
    cin >> codiNacionalitat;
    cout << "Any: " << any << "  Districte:" << districte << "  Edat:" << edat << "  Codi Nacionalitat:" <<
            codiNacionalitat << endl;

    list<string> estudis = padro.estudisEdat(any, districte, edat, codiNacionalitat);

    if (!estudis.empty()) {
        for (list<string>::const_iterator it = estudis.begin(); it != estudis.end(); it++) {
            cout << *it << endl;
        }
    }
}

int main() {
    Padro padro;

    int n = 0;
    do {
        cin >> n;
        if (n == 1) {
            llegir_dades(padro);
        } else if (n == 2) {
            existeixAny(padro);
        } else if (n == 3) {
            obtenirNHabitants(padro);
        } else if (n == 4) {
            nHabitantsUnAny(padro);
        } else if (n == 5) {
            nHabitantsUnAnyUnDistricte(padro);
        } else if (n == 6) {
            mostrarResumEstudis(padro);
        } else if (n == 7) {
            nEstudisDistricte(padro);
        } else if (n == 8) {
            resumNivellEstudis(padro);
        } else if (n == 9) {
            resumNacionalitats(padro);
        } else if (n == 10) {
            movimentsUnaComunitat(padro);
        } else if (n == 11) {
            resumEdats(padro);
        } else if (n == 12) {
            movimentsVells(padro);
        } else if (n == 13) {
            mesJoves(padro);
        } else if (n == 14) {
            estudisAnyDistricteEdatNacionalitat(padro);
        } else {
            cout << "Tria una opció válida del menú d'opcions" << endl;
        }
    } while (n != 0);

    return 0;
}
