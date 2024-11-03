// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#include "Padro.h"

Padro::Padro() {
}

int Padro::llegirDades(const string &path) {
    int llegides = 0;
    ifstream f(path);
    string linia;

    if (!f.fail()) {
        getline(f, linia); // Salta la primera linia
        while (getline(f, linia)) {
            vector<string> items = tokens(linia, ',', true);

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
    if (existeixAny(any)) {
        const vector<Districte> &districtes = _districtes.at(any); // Obté el vector de districtes d'un any especific
        for (int i = 1; i < MIDA; i++) {
            habitants[i] = districtes[i].obtenirNumHabitants();
        }
    } else cerr << "L'any no existeix a Padro" << endl;
    return habitants;
}

map<int, long> Padro::obtenirNumHabitantsPerSeccio(int any, int districte) const {
    map<int, long> habitantsPerSec;

    // Comprova si els paràmetres son correctes
    if (existeixAny(any) and districte > 0 and districte <= MIDA) {
        const vector<Districte> &districtesAny = _districtes.find(any)->second;
        if (districte < districtesAny.size()) {
            habitantsPerSec = districtesAny[districte].obtenirHabitantsPerSeccio();
        } else {
            cerr << "Districte fora de rang per l'any especificat." << endl;
        }
    }

    return habitantsPerSec;
}

ResumEstudis Padro::resumEstudis() const {
    return _estudis;
}

map<int, int> Padro::nombreEstudisDistricte(int districte) const {
    map<int, int> estudisPerDist;
    map<int, vector<Districte> >::const_iterator it = _districtes.begin();

    while (it != _districtes.end()) {
        int any = it->first;
        estudisPerDist[any] = it->second[districte].obtenirNivellEstudis();
        it++;
    }
    return estudisPerDist;
}

ResumNivellEstudis Padro::resumNivellEstudis() const {
    ResumNivellEstudis resultat;

    map<int, vector<Districte> >::const_iterator it = _districtes.begin();
    while (it != _districtes.end()) {
        int any = it->first;
        vector<pair<char, double> > nivellsPromig(MIDA, make_pair(' ', 0.0));

        int indexMax = -1;
        int indexMin = -1;
        double maxPromig = 0.0;
        double minPromig = -1.0;

        // Recorre cada distrito del año actual
        for (int i = 1; i < it->second.size(); i++) {
            long numHabitants = it->second[i].obtenirNumHabitants();
            long totalNivellEstudis = it->second[i].obtenirTotalNivellEstudis();

            if (numHabitants > 0) {
                double promig = static_cast<double>(totalNivellEstudis) / numHabitants;
                nivellsPromig[i] = make_pair(' ', promig);

                if (indexMax == -1 or promig > maxPromig) {
                    maxPromig = promig;
                    indexMax = i;
                }
                if (indexMin == -1 or promig < minPromig) {
                    minPromig = promig;
                    indexMin = i;
                }
            }
        }

        // Asigna los símbolos de máximo y mínimo
        if (indexMax != -1) {
            nivellsPromig[indexMax].first = '+';
        }
        if (indexMin != -1 && indexMin != indexMax) {
            nivellsPromig[indexMin].first = '-';
        }

        resultat[any] = nivellsPromig;
        it++;
    }

    return resultat;
}

ResumNacionalitats Padro::resumNacionalitats() const {
    ResumNacionalitats resultat;

    // Itera sobre cada año en el mapa _districtes
    map<int, vector<Districte> >::const_iterator it_any = _districtes.begin();
    while (it_any != _districtes.end()) {
        int any = it_any->first;
        unordered_map<Nacionalitat, long> nacionalitatsPerAny;

        // Recorre cada districte en l'any actual
        for (int i = 1; i < it_any->second.size(); ++i) {
            const unordered_map<Nacionalitat, long> &habitantsNacio = it_any->second[i].obtenirHabitantsPerNacio();

            // Acumula la quantitat d'habitants per nacionalitat
            for (const auto &it_nacio: habitantsNacio) {
                const Nacionalitat &nacionalitat = it_nacio.first;
                long quantitat = it_nacio.second;
                nacionalitatsPerAny[nacionalitat] += quantitat;
            }
        }

        // Transfeix del unordered_map al multimap per ordenar per cantitat evitant duplicats de nacionalitats
        multimap<long, Nacionalitat, greater<long> > ordenat;
        for (const auto &it: nacionalitatsPerAny) {
            ordenat.insert({it.second, it.first});
        }

        // Afegeix el resultat ordenat al map per any
        resultat[any] = ordenat;
        it_any++;
    }

    return resultat;
}

map<int, string> Padro::movimentsComunitat(int codiNacionalitat) const {
    map<int, string> resultat;

    map<int, vector<Districte> >::const_iterator it_any = _districtes.begin();
    // Recorre cada any
    while (it_any != _districtes.end()) {
        int any = it_any->first;
        long maxHabitants = 0;
        int districteMaxIndex = 0;

        // Recorre cada districte de l'any actaul
        for (int i = 1; i < it_any->second.size(); i++) {
            const Districte &districte = it_any->second[i];

            // Verifica si el districte té habitants de la nacionalitat sol·licitada
            const unordered_map<Nacionalitat, long> habitantsNacio = districte.obtenirHabitantsPerNacio();
            const unordered_map<Nacionalitat, long>::const_iterator it_nacionalitat = habitantsNacio.find(
                codiNacionalitat);

            // Si la nacionalitat existeix en el districte, es verifica la quantitat d'habitants
            if (it_nacionalitat != habitantsNacio.end()) {
                long habitantsNacionalitat = it_nacionalitat->second;

                // Si el districte té més habitants d'aquesta nacionalitat, s'actualitza el valor del màxim
                if (habitantsNacionalitat > maxHabitants) {
                    maxHabitants = habitantsNacionalitat;
                    districteMaxIndex = i;
                }
            }
        }

        // Afegeix el districte amb més habitants de la nacionalitat per l'any actual
        if (districteMaxIndex == 0) {
            resultat[any] = "No té habitants";
        } else {
            resultat[any] = DISTRICTES[districteMaxIndex];
        }
        it_any++;
    }
    return resultat;
}

int Padro::stringToInt(const string &s) {
    if (s.length() == 0) return -1;
    for (char c: s) {
        if (c < '0' or c > '9') {
            cerr << "Error: Carácter no numeric trobat a '" << s << "'" << endl;
            return -1;
        }
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
        afegirDades(any, districte, seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat,
                    nomNacionalitat);
        return true;
    }
    return false;
}

bool Padro::dadesCorrectes(int any, int districte, int seccio, int codiNivellEstudis, int anyNaixement,
                           int codiNacionalitat) const {
    return any != -1 and seccio != -1 and districte != -1 and codiNivellEstudis != -1 and anyNaixement != -1 and
           codiNacionalitat != -1 and
           districte > 0 and districte <= MIDA;
}


void Padro::afegirDades(int any, int districte, int seccio, int codiNivellEstudis, const string &nivellEstudis,
                        int anyNaixement, int codiNacionalitat, const string &nomNacionalitat) {
    if (existeixAny(any)) {
        _districtes[any][districte].afegir(seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat,
                                           nomNacionalitat);
    } else {
        vector<Districte> nousDistrictes(MIDA);
        nousDistrictes[districte].afegir(seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat,
                                         nomNacionalitat);
        _districtes[any] = nousDistrictes;
    }
    // Actualiza _habitantsPerAny
    _habitantsPerAny[any]++;

    // Actualiza _estudis
    _estudis[any].insert(nivellEstudis);

    // Calcula edat i actualiza _edats
    int edat = ANY_ACTUAL - anyNaixement;
    _edats[any].resize(MIDA);
    _edats[any][districte] += edat;
}
