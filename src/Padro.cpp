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
            if (items.size() < 18) {
                // El nombre de paràmetres de la linia han de ser 18
                cerr << "Falten dades en la linia" << endl;
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

        // Assigna els símbols del màxim i mínim
        if (indexMax != -1) {
            nivellsPromig[indexMax].first = '+';
        }
        if (indexMin != -1 and indexMin != indexMax) {
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

        // Recorre cada districte de l'any actual
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

ResumEdats Padro::resumEdat() const {
    ResumEdats resultat;

    map<int, vector<Districte> >::const_iterator it_any = _districtes.begin();
    while (it_any != _districtes.end()) {
        int any = it_any->first;
        vector<pair<double, int> > edatsPromig;

        // Recorre cada districte en l'any actual
        for (int i = 1; i < it_any->second.size(); i++) {
            double promigEdat = it_any->second[i].obtenirEdatMitjana(it_any->first);
            edatsPromig.push_back(make_pair(promigEdat, i));
        }

        // Ordena les mitjanes d'edat en ordre ascendent
        sort(edatsPromig.begin(), edatsPromig.end());

        // Crea un vector de mitjanes d'edat ordenades per a l'any
        vector<double> edatsOrdenades;

        vector<pair<double, int> >::const_iterator it = edatsPromig.begin();
        while (it != edatsPromig.end()) {
            edatsOrdenades.push_back(it->first);
            it++;
        }

        // Emmagatzema el vector d'edats ordenades al mapa de resultats
        resultat[any] = edatsOrdenades;

        it_any++;
    }
    return resultat;
}

map<int, string> Padro::movimentVells() const {
    map<int, string> resultat;

    ResumEdats resum = resumEdat();
    map<int, vector<double> >::const_iterator it_any = resum.begin();
    while (it_any != resum.end()) {
        int any = it_any->first;
        // L'índex del districte més envellit és l'últim en el vector ordenat
        int districteIndex = it_any->second.size() - 1;

        resultat[any] = DISTRICTES[districteIndex + 1];

        it_any++;
    }
    return resultat;
}

pair<string, long> Padro::mesJoves(int anyInicial, int anyFinal) const {
    string districteMAX;
    long maxIncrement = 0;

    if (existeixAny(anyInicial) && existeixAny(anyFinal)) {
        // Per cada districte
        for (int i = 1; i < DISTRICTES.size(); i++) {
            long jovesInicial = 0;
            long jovesFinal = 0;

            const vector<Districte> &districtesInicial = _districtes.find(anyInicial)->second;
            const vector<Districte> &districtesFinal = _districtes.find(anyFinal)->second;

            // Comptem els habitants joves en el anyInicial per al districte actual
            for (int anyNaixement = anyInicial - 30; anyNaixement <= anyInicial - 20; ++anyNaixement) {
                jovesInicial += districtesInicial[i].comptaEdatNacionalitat(anyNaixement, -1);
                // -1 per a qualsevol nacionalitat
            }

            // Comptem els habitants joves en el anyFinal per al districte actual
            for (int anyNaixement = anyFinal - 30; anyNaixement <= anyFinal - 20; ++anyNaixement) {
                jovesFinal += districtesFinal[i].comptaEdatNacionalitat(anyNaixement, -1);
                // -1 per a qualsevol nacionalitat
            }

            // Calculem l'increment
            long increment = jovesFinal - jovesInicial;

            // Actualitzem si és el major increment trobat fins ara
            if (increment > maxIncrement) {
                maxIncrement = increment;
                districteMAX = DISTRICTES[i];
            }
        }
    }
    return make_pair(districteMAX, maxIncrement);
}

list<string> Padro::estudisEdat(int any, int districte, int edat, int codiNacionalitat) const {
    list<string> resultat;
    if(edat > 0 and codiNacionalitat > 0) {
        set<string> estudisUnics;  // Utilitzem un set per ordenar i eliminar duplicats durant la cerca

        map<int, vector<Districte>>::const_iterator it_any = _districtes.find(any);
        // Verifica que l'any i districte existeixen en les dades
        if (it_any != _districtes.end() and districte > 0 and districte < it_any->second.size()) {
            const Districte &districteObj = it_any->second[districte];

            for (const Persona &persona : districteObj.obtenirPersones()) {
                int edatPersona = it_any->first - persona.obtenirAnyNaixement();
                if (edatPersona == edat and persona.obtenirCodiPaisNaixement() == codiNacionalitat) {
                    estudisUnics.insert(persona.obtenirNivellEstudis());
                }
            }
        }

        // Passem el set a la llista a retornar
        resultat = list<string>(estudisUnics.begin(), estudisUnics.end());
    }

    return resultat;
}

int Padro::stringToInt(const string &s) {
    //Pre:--
    //Post:retorna el valor de s(string) en integer
    if (s.length() == 0) return -1;
    if (s.find("<20") != string::npos) {
        cerr << "Advertència: Caràcter especial '<20' detectat, ometent conversió" << endl;
        return -1;
    }
    for (char c: s) {
        if (c < '0' || c > '9') {
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

    if (dadesCorrectes(any, districte, seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat,
                       nomNacionalitat)) {
        afegirDades(any, districte, seccio, codiNivellEstudis, nivellEstudis, anyNaixement, codiNacionalitat,
                    nomNacionalitat);
        return true;
    }
    return false;
}

bool Padro::dadesCorrectes(int any, int districte, int seccio, int codiNivellEstudis, const string &nivellEstudis,
                           int anyNaixement,
                           int codiNacionalitat, const string &nomNacionalitat) const {
    // Verificacions de conversio de dades
    if (any == -1 or seccio == -1 or districte == -1 or codiNivellEstudis == -1 or anyNaixement == -1 or
        codiNacionalitat == -1) {
        return false;
    }

    // Comprovació del rang de Districtes
    if (districte < 1 || districte > MIDA) {
        return false;
    }

    // Verificació que l'any de naixement sigui acceptable
    if (anyNaixement > any or anyNaixement < 1900) {
        return false;
    }

    // Verificació de valors negatius en camps rellevants
    if (codiNivellEstudis < 0 || codiNacionalitat < 0) {
        return false;
    }

    if (nivellEstudis.empty() or nomNacionalitat.empty()) {
        cerr << "Error: Hi ha camps de text buits" << endl;
        return false;
    }
    if (nivellEstudis == "<20") {
        cerr << "Error: El nivell d'estudis conté el patró no vàlid '<20': '" << nivellEstudis << "'" << endl;
        return false;
    }

    if (nomNacionalitat == "<20") {
        cerr << "Error: El nom de la nacionalitat conté el patró no vàlid '<20': '" << nomNacionalitat << "'" << endl;
        return false;
    }

    return true;
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
    int edat = any - anyNaixement;

    if (_edats.find(any) == _edats.end()) {
        _edats[any].resize(MIDA);
    }
    _edats[any][districte] += edat;
}
