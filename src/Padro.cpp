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
    return _habitantsPerAny;
}

vector<long> Padro::obtenirNumHabitantsPerDistricte(int any) const {
    vector<long> habitants(MIDA);
    if(existeixAny(any)) {
        const vector<Districte>& districtes = _districtes.at(any);  // Obté el vector de districtes d'un any especific
        for (int i = 0; i < MIDA; ++i) {
            habitants[i] = districtes[i].obtenirNumHabitants();
        }
    } else cerr << "L'any no existeix a Padro" << endl;
    return habitants;
}

map<int, long> Padro::obtenirNumHabitantsPerSeccio(int any, int districte) const {
    map<int, long> habitantsPerSec;

    // Comprova si els paràmetres son correctes
    if (existeixAny(any) and districte > 0 and districte <= MIDA) {
        const vector<Districte>& districtesAny = _districtes.find(any)->second;
        if (districte - 1 < districtesAny.size()) {
            habitantsPerSec = districtesAny[districte - 1].obtenirHabitantsPerSeccio();
        } else {
            cerr << "Districte fora de rang per l'any especificat." << endl;
        }
    } else {
        cerr << "Any o districte no existent." << endl;
    }
    return habitantsPerSec;
}

ResumEstudis Padro::resumEstudis() const {

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
    // Actualiza _habitantsPerAny
    _habitantsPerAny[any]++;

    // Actualiza _estudis
    _estudis[any].insert(Estudi(codiNivellEstudis, nivellEstudis));

    // Calcula edat i actualiza _edats
    int edat = ANY_ACTUAL - anyNaixement;
    _edats[any].resize(MIDA); // Asegura que el vector té MIDA districtes
    _edats[any][districte - 1] += edat;

    // Actualiza _nivellEstudis
    _nivellEstudis[any].resize(MIDA); // Asegura que el vector té MIDA districtes
    _nivellEstudis[any][districte - 1] += codiNivellEstudis;
    _habitantsPerAny[any]++;
}
