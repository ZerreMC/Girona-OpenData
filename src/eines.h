// Sebastian J. Gutierrez Llorca
// Usuari u1980984
// Sessio 2 Practica p1

#ifndef LECTURA_EINES_H
#define LECTURA_EINES_H

#include <string>
#include <vector>
using namespace std;

/**
 * @brief Obté una subcadena des d'una posició inicial fins al següent separador o final de línia.
 *
 * @param s Cadena d'entrada de la qual es vol obtenir un token.
 * @param separador Caràcter que indica el final del token.
 * @param cometes Indica si els tokens poden estar entre cometes.
 * @param primer Posició inicial des de la qual començar a buscar el token.
 * @param ultim Posició final del token trobat.
 * @return Retorna una subcadena que conté el token entre la posició inicial i el següent separador o final de línia.
 *
 * @pre  --
 * @post Si `cometes` és cert i el primer caràcter és `"`, busca la segona `"`, elimina les cometes i retorna el contingut.
 * @throws Es genera una excepció si `cometes` és cert i el token comença amb `"`, però no es troba una segona `"`.
 */
string token(const string &s, char separador, bool cometes, long &primer, long &ultim);

/**
 * @brief Divideix una cadena en diversos tokens segons un separador especificat, tractant opcionalment cometes.
 *
 * @param s Cadena d'entrada que es vol dividir en tokens.
 * @param separador Caràcter utilitzat per separar els tokens dins de la cadena.
 * @param cometes Indica si els tokens poden estar entre cometes.
 * @return Un `vector<string>` amb tots els components d'una línia CSV bàsica, separats per `separador`.
 *
 * @pre  --
 * @post Retorna un `vector<string>` amb els components d'una línia CSV. Cada component conté els caràcters entre dos separadors,
 *       excepte el primer i l'últim:
 *         - El primer component conté els caràcters abans del primer separador.
 *         - L'últim component conté els caràcters després de l'últim separador.
 */
vector<string> tokens(const string &s, char separador = ',', bool cometes = false);

#endif // LECTURA_EINES_H
