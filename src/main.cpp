// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include "Padro.h"

using namespace std;

/**
 * @brief Llegeix les dades des d'un fitxer CSV i mostra el nombre de línies llegides.
 * @param padro Referència a l'objecte Padro per emmagatzemar les dades.
 * @pre El fitxer indicat per l'usuari ha de ser accessible i tenir el format correcte.
 * @post Es llegeixen les dades del fitxer i es mostren les línies llegides.
 * @return Retorna el nombre de línies llegides.
 */
int llegir_dades(Padro &padro) {
    cout << "********************" << endl;
    cout << "* 01: Llegir dades *" << endl;
    cout << "********************" << endl;

    string path;
    cin >> path;
    int numLinies = padro.llegirDades(path);
    cout << "Numero de linies: " << numLinies << endl;
    return numLinies;
}

/**
 * @brief Obté un número enter positiu de l'entrada de l'usuari.
 * @param entrada Referència a l'enter on es desarà l'input de l'usuari.
 * @post L'input introduït serà un enter positiu vàlid.
 */
void obtenirEntradaValida(int &entrada) {
    bool valida = false;
    while (!valida) {
        cin >> entrada;
        // Comprova si l'entrada és vàlida o és un número negatiu
        if (cin.fail() or entrada < 0) {
            cin.clear(); // Neteja l'estat d'error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar l'entrada incorrecta del buffer
            cout << "L'entrada no és vàlida, ha de ser un nombre enter positiu." << endl;
        } else {
            valida = true; // L'entrada és vàlida
        }
    }
}

/**
 * @brief Comprova si un any específic existeix en les dades del Padró.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha de contenir dades vàlides.
 * @post Mostra si l'any introduït existeix al Padró.
 */
void existeixAny(const Padro &padro) {
    cout << "********************" << endl;
    cout << "* 02: Existeix any *" << endl;
    cout << "********************" << endl;

    int any;
    obtenirEntradaValida(any);
    cout << "Any:" << any << endl;
    if (padro.existeixAny(any))
        cout << "Any existent" << endl;
    else
        cout << "Any inexistent" << endl;
}

/**
 * @brief Mostra el nombre total d'habitants per cada any.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha de contenir dades vàlides.
 * @post Es mostra el nombre d'habitants per any, així com el promig calculat.
 */
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
    cout << "PROMIG : " << fixed << setprecision(2) << promig / n << endl;
}

/**
 * @brief Mostra el nombre d'habitants d'un any especificat.
 * @param padro Referència constant a l'objecte Padro.
 * @pre L'any indicat ha de ser existent a les dades del \c padro.
 * @post Mostra el nombre d'habitants per districte d'un any determinat i el total.
 */
void nHabitantsUnAny(const Padro &padro) {
    cout << "*******************************************" << endl;
    cout << "* 04: Obtenir nombre d'habitants d'un any *" << endl;
    cout << "*******************************************" << endl;

    int any;
    obtenirEntradaValida(any);
    while (!padro.existeixAny(any)) {
        cout << "ERROR any " << any << " inexistent" << endl;
        obtenirEntradaValida(any);
    }

    cout << "Any:" << any << endl;
    vector<long> habitants = padro.obtenirNumHabitantsPerDistricte(any);
    int total = 0;
    for (int i = 1; i < habitants.size(); i++) {
        cout << "Districte " << i << setw(13) << "habitants:" << setw(7) << habitants[i] << endl;
        total += habitants[i];
    }
    cout << "TOTAL : " << total << endl;
}

/**
 * @brief Mostra el nombre d'habitants d'una secció específica dins un districte i any.
 * @param padro Referència constant a l'objecte Padro.
 * @pre L'any i districte han d'existir en les dades de \c padro.
 * @post Mostra el nombre d'habitants per secció, així com el total del districte.
 */
void nHabitantsUnAnyUnDistricte(const Padro &padro) {
    cout << "*******************************************************" << endl;
    cout << "* 05: Obtenir nombre d'habitants d'un any i districte *" << endl;
    cout << "*******************************************************" << endl;

    int any, districte;

    // Bucle per validar l'any
    obtenirEntradaValida(any);
    while (!padro.existeixAny(any)) {
        cout << "ERROR any " << any << " inexistent" << endl;
        obtenirEntradaValida(any);
    }

    // Bucle per validar el districte
    obtenirEntradaValida(districte);
    map<int, long> habitants;
    habitants = padro.obtenirNumHabitantsPerSeccio(any, districte);
    while (habitants.empty()) {
        cout << "ERROR districte " << districte << "inexistent" << endl;
        obtenirEntradaValida(districte);
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

/**
 * @brief Mostra un resum de les dades per nivell d'estudis.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Mostra el resum dels nivells d'estudis per any.
 */
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

/**
 * @brief Mostra el nombre d'estudis per un districte donat.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Mostra el nombre d'estudis registrats per un districte especificat.
 */
void nEstudisDistricte(const Padro &padro) {
    cout << "**************************************" << endl;
    cout << "* 07: Nombre d'estudis per districte *" << endl;
    cout << "**************************************" << endl;
    int districte;
    obtenirEntradaValida(districte);
    cout << "Districte:" << districte << endl;

    map<int, int> habitants = padro.nombreEstudisDistricte(districte);
    map<int, int>::iterator it = habitants.begin();
    while (it != habitants.end()) {
        cout << "Any " << it->first << "  Num Estudis:" << it->second << endl;
        it++;
    }
}

/**
 * @brief Mostra un resum del nivell d'estudis per districte i any.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Es mostra el nivell d'estudis promig per cada districte i any.
 */
void resumNivellEstudis(const Padro &padro) {
    cout << "******************************" << endl;
    cout << "* 08: Resum nivell d'estudis *" << endl;
    cout << "******************************" << endl;

    ResumNivellEstudis resum = padro.resumNivellEstudis();

    map<int, vector<pair<char, double> > >::const_iterator it = resum.begin();
    while (it != resum.end()) {
        int any = it->first;
        cout << any << ": " << endl;

        const vector<pair<char, double> > &districtes = it->second;
        for (int i = 1; i < districtes.size(); i++) {
            char simbol = districtes[i].first;
            double promig = districtes[i].second;

            cout << "       " << simbol << " " << left << setw(32) << DISTRICTES[i]
                    << "Promig Estudis: " << setw(10) << right << fixed << setprecision(2) << promig << endl;
        }
        it++;
    }
}

/**
 * @brief Mostra un resum de les nacionalitats dels habitants.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Es mostra un resum de nacionalitats amb el nombre d'habitants per any.
 */
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
            cout << "       " << left << setw(30) << (it_Nacio->second.obtenirNom() + " (" + to_string(
                                                          it_Nacio->second.obtenirId()) + ")");
            cout << right << ":" << setw(11) << it_Nacio->first << endl;

            it_Nacio++;
        }
        it_Any++;
    }
}

/**
 * @brief Mostra els moviments d'una comunitat específica en els districtes.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Es mostra el districte que concentra més habitants d'una comunitat per any.
 */
void movimentsUnaComunitat(const Padro &padro) {
    cout << "*********************************" << endl;
    cout << "* 10: Moviments d'una comunitat *" << endl;
    cout << "*********************************" << endl;

    int codiNacionalitat;
    obtenirEntradaValida(codiNacionalitat);
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

/**
 * @brief Mostra un resum de les edats per districte i any.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Es mostra l'edat promig per cada districte i any.
 */
void resumEdats(const Padro &padro) {
    cout << "*********************" << endl;
    cout << "* 11: Resum d'edats *" << endl;
    cout << "*********************" << endl;

    ResumEdats resum = padro.resumEdat();
    map<int, set<pair<double, string> > >::const_iterator it_any = resum.begin();

    while (it_any != resum.end()) {
        int any = it_any->first;
        cout << any << ": " << endl;

        // Recorre el set de parelles <nom del districte, edat>
        for (const auto &pair: it_any->second) {
            const string &nomDistricte = pair.second;
            double promigEdat = pair.first;

            cout << "       " << setw(32) << left << nomDistricte
                    << "Promig Edat: " << setw(10) << right << fixed << setprecision(2) << promigEdat << endl;
        }
        it_any++;
    }
}

/**
 * @brief Mostra el districte més envellit per cada any.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Es mostra el districte amb la major edat mitjana per any.
 */
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

        cout << any << "    " << districte << endl;
        it_any++;
    }
}

/**
 * @brief Mostra el districte amb el major increment de població jove.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Mostra el districte amb més increment de joves entre dos anys especificats.
 */
void mesJoves(const Padro &padro) {
    cout << "******************" << endl;
    cout << "* 13: Més joves *" << endl;
    cout << "******************" << endl;
    int anyInicial, anyFinal;
    obtenirEntradaValida(anyInicial);
    obtenirEntradaValida(anyFinal);
    cout << "Any Inicial: " << anyInicial << "  AnyFinal:" << anyFinal << endl;

    pair<string, long> mesJoves = padro.mesJoves(anyInicial, anyFinal);
    cout << left << setw(29) << mesJoves.first << right << mesJoves.second << endl;
}

/**
 * @brief Mostra els estudis de persones d'una edat, any, districte i nacionalitat específics.
 * @param padro Referència constant a l'objecte Padro.
 * @pre \c padro ha d'estar inicialitzat amb dades prèviament llegides.
 * @post Mostra la llista d'estudis per l'any, districte, edat i codi de nacionalitat proporcionats.
 */
void estudisAnyDistricteEdatNacionalitat(const Padro &padro) {
    cout << "********************************************" << endl;
    cout << "* 14: Estudis any,districte, edat i nació *" << endl;
    cout << "********************************************" << endl;

    int any, districte, edat, codiNacionalitat;
    obtenirEntradaValida(any);
    obtenirEntradaValida(districte);
    obtenirEntradaValida(edat);
    obtenirEntradaValida(codiNacionalitat);
    cout << "Any: " << any << "  Districte:" << districte << "  Edat:" << edat << "  Codi Nacionalitat:" <<
            codiNacionalitat << endl;

    list<string> estudis = padro.estudisEdat(any, districte, edat, codiNacionalitat);

    if (!estudis.empty()) {
        for (list<string>::const_iterator it = estudis.begin(); it != estudis.end(); it++) {
            cout << *it << endl;
        }
    }
}

/**
 * @brief Punt d'entrada principal del programa.
 * @return Retorna 0 quan s'executa correctament.
 * @pre No té precondicions.
 * @post Permet a l'usuari triar diverses operacions sobre l'objecte Padró si hi ha dades.
 */
int main() {
    Padro padro;

    int n = 0;
    bool dadesLlegides = false;

    do {
        cin >> n;
        if (n == 1) {
            int numLinies = llegir_dades(padro);
            dadesLlegides = (numLinies > 0);// Comprova si s'han llegit dades
        } else if (n == 0) {
            // Opció de sortida, no mostrar el missatge d'error
            break;
        } else if (dadesLlegides) {
            switch (n) {
                case 2: existeixAny(padro); break;
                case 3: obtenirNHabitants(padro); break;
                case 4: nHabitantsUnAny(padro); break;
                case 5: nHabitantsUnAnyUnDistricte(padro); break;
                case 6: mostrarResumEstudis(padro); break;
                case 7: nEstudisDistricte(padro); break;
                case 8: resumNivellEstudis(padro); break;
                case 9: resumNacionalitats(padro); break;
                case 10: movimentsUnaComunitat(padro); break;
                case 11: resumEdats(padro); break;
                case 12: movimentsVells(padro); break;
                case 13: mesJoves(padro); break;
                case 14: estudisAnyDistricteEdatNacionalitat(padro); break;
                default: break;
            }
        } else {
             cout << "Primer has de llegir dades des d'un fitxer amb l'opció 1." << endl;
        }
    } while (n != 0);

    return 0;
}
