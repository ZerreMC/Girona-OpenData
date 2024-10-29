// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Padro.h"

int Padro::llegirDades(const string &path) {
    int llegides = 0;
    ifstream f(path);
    string linia;

    if (!f.fail()) {
        getline(f, linia); // Salta la primera linia
        while (getline(f, linia)) {
            vector<string> items = tokens(linia, ';', false);
            if (items.size() >= 13) {
                cerr << "Dades insuficients a la linea" << endl;
                continue;
            }

            if (processarLinia(items)) {

                llegides++;
            } else {
                cerr << "Dades incorrectes en la línea, no serán emmagatzemades" << endl;
            }
        }
        f.close();
    } else {
        cerr << "No s'ha pogut obrir l'arxiu (" << path << ")." << endl;
    }
    return llegides;
}

bool Padro::existeixAny(int any) const {
    return _districtes.count(any) > 0;
}

map<int, long> Padro::obtenirNumHabitantsPerAny() const {
    map<int, long> habitants;

    return habitants;
}

vector<long> Padro::obtenirNumHabitantsPerDistricte(int any) const {
    vector<long> habitants;
    if(existeixAny(any)) {
        for(int i=0; i<_districtes[any].size(); i++) {

        }
    } else cerr << "L'any no existeix a Padro" << endl;
    return habitants;
}

map<int, long> Padro::obtenirNumHabitantsPerSeccio(int any, int districte) const {

}

int Padro::stringToInt(const string &s) {
    if (s.empty()) return -1;
    for (char c: s) {
        if (c < '0' || c > '9') return -1;
    }
    return stoi(s);
}

bool Padro::processarLinia(vector<string> &items) {
    // Guardar les dades rellevants
    int any = stringToInt(items[0]); // Columna 0: any
    int districte = stringToInt(items[1]); // Columna 1: districte
    int seccio = stringToInt(items[2]); // Columna 2: seccio
    int codiNivellEstudis = stringToInt(items[4]); // Columna 4: codi_nivell_estudis
    string nivellEstudis = items[5]; // Columna 5: nivell_estudis
    int anyNaixement = stringToInt(items[6]); // Columna 6: data_naixement
    int codiNacionalitat = stringToInt(items[11]); // Columna 11: codi_nacionalitat
    string nomNacionalitat = items[12]; // Columna 12: nacionalitat

    if (dadesCorrectes(any, districte, seccio, codiNivellEstudis, anyNaixement, codiNacionalitat)) {
        afegirDades(any, districte, seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
        return true;
    }
    return false;
}

bool Padro::dadesCorrectes(int any, int districte, int seccio, int codiNivellEstudis, int anyNaixement, int codiNacionalitat) const {
    return any != -1 && seccio != -1 && districte != -1 && codiNivellEstudis != -1 && anyNaixement != -1 && codiNacionalitat != -1 &&
               districte > 0 && districte <= MIDA;
}

void Padro::afegirDades(int any, int districte, int seccio, int codiNivellEstudis, const string& nivellEstudis, int anyNaixement, int codiNacionalitat, const string& nomNacionalitat) {
    if (existeixAny(any)) {
        _districtes[any][districte - 1].afegir(seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
    } else {
        vector<Districte> nousDistrictes(MIDA);
        nousDistrictes[districte - 1].afegir(seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat, nomNacionalitat);
        _districtes[any] = nousDistrictes;
    }
}


