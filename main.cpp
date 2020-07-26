#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <cassert>
using namespace std;
string lgg = "en";
string oldStart = "OldStart.txt";
string oldContinue = "OldContinue.txt";

bool errBadVAlue(string texteBadValue, auto min, auto max) {
    cerr << "Min = "  << min << endl;
    cerr << "Max = "  << max << endl;
    cerr << texteBadValue << endl;
    return false;
    }

auto inputNb(auto max = 42, auto min = 0, string texteDemande = "How many?", string texteBadValue = "A good number!") {
    if(max < min) {  // En général, on donne le minimum avant le maximum, et parfois pas la valeur par défaut.
        auto temp = max;
        max = min;
        min = temp;
        }
// Textes par défaut par fichier lgg ?
    auto a = max; // Valeur valide.
    string tentativeString = "";
    bool inputOk  = true;
    do {
        cout << texteDemande << endl;
        inputOk = true; // Pour autre demande éventuelle.
        try {
            getline(cin, tentativeString);    // Pour éviter des bugs de non nombre.
            }
        catch(const std::invalid_argument& e) {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue(texteBadValue, min, max);
            }
        try {
            a = stoi(tentativeString);    // cin.;
            }
        catch(exception& e) {  // Nombre dépassant la limite : 99999999999999999999999999999999 par exemple.
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue(texteBadValue, min, max);
            }
        if((a < min) || (a > max)) {
            a = max; // Valeur valide.
            inputOk = errBadVAlue(texteBadValue, min, max);
            }
        }
    while(inputOk == false);
    return a;
    }

int replaceFileString(string file, string data = "") { // And create new file if does not exist.
    ofstream outfile(file.c_str());
    if(!outfile) {
        cerr << "Error: Impossible to write in the file " << file << "!" << endl;
        return -1;
        }
    else {
        outfile << data;
        outfile.close();
        }
    return 0; // Ok.
    }

string read1DataFile(string file = "test.txt") {
    ifstream myfile(file.c_str());
    if(myfile.is_open()) {
        string line = "";
        getline(myfile, line);
        myfile.close();
        return line;
        }
    else {
        cerr << "Unable to read file: " << file << endl;
        }
    }

void config() {
    lgg = read1DataFile("lgg.txt");
    }

void coutFile(string file = "cout.txt") {
    ifstream fichier(file.c_str(), ios::in);
    if(!fichier) {
        cerr << "Impossible to read the file: " << file << "!" << endl;
        }
    else {
        string ligne;
        while(getline(fichier, ligne)) {
            cout << ligne << endl;
            }
        fichier.close();
        }
    }

void intro(string lgg = "fr") {
// fr:
    cout << "                -= OrdiCube =-" << endl;
    cout << "Vous devez obtenir 123456789 en permutant le premier chiffre avec le chiffre de votre choix." << endl;
    cout << "Effet secondaire : inversion autour du chiffre choisi ! ( En plus, c\'est de la topologie en tore !)" << endl;
    cout << "Avec 451236789, jouer 6 donnera donc 651274389." << endl << endl;
    cout << "Source d\'origine (mais avec quelques changements) : " << endl;
    cout << "\"Ti-81 le top des jeux\", Vincent Bastid et Emmanuel Neuville, DunodTech, page 131 jusque 138." << endl << endl; // Intraduisible.
    cout << "     -2 : Entrer combinaison manuellement." << endl;
    cout << "     -1 : Combinaison d\'avant, mais au commencement." << endl;
    cout << "      0 : Suite de la partie d\'avant." << endl;
    cout << "1... 20 : Tirage au pseudo-hasard de niveau 1 (facile) jusque 20 (difficile). TODO" << endl;
    }


// cout << interchange("abcdefgh", 0, 7) << endl; // Ok.
string interchange(string startString = "abcdefgh", int a = 0, int b = 3) { // Ok.
    clog << "a: " << a << endl;
    clog << "b: " << b << endl;
    clog << "startstring: " << startString << endl;
    assert((a >= 0) && "Erreur de codage : a < 0 !");
    assert((b >= 0) && "Erreur de codage : b < 0 !");
    assert((a < startString.size()) && "Erreur de codage : a > start !");
    assert((b < startString.size()) && "Erreur de codage : b > start !");
    char x = startString[a];
    startString[a] = startString[b];
    startString[b] = x;
    return startString;
    }

int findPosIntString(int N = 0, string udt = "123456789") {
    int a = 0;
    while((udt[a] - '0') != N){  // Char to int // http://www.cplusplus.com/forum/beginner/68260/
        a++;
        if(a > udt.size()) {
            cerr << "Not in string!" << endl;
            return -1;
            }
        }
    return a;
    }



string joue(string partie, int N) { // ??
    N = findPosIntString(N, partie); // ??
    partie = interchange(partie, 1, N);
//   partie = interchange(partie, (N - 1) % partie.size(), (N + 1) % partie.size());
    return partie;
    }

string initMix(int choixMenu = 2) { // Todo.
    switch(choixMenu) {
        case -2: { // Entrer combinaison manuellement.
            return to_string(inputNb(987654321, 123456789));
            }
        break;
        case -1: { // Combinaison d'avant, mais au commencement.
            return read1DataFile(oldStart);
            }
        break;
        case 0: { // Suite de la partie d'avant.
            return read1DataFile(oldContinue);
            }
        break;
        default: {
            int N = abs(choixMenu); // In order to be more compatible.
            string workString = "123456789";
            for(int a = 0; a < N; a++) {
                workString = joue(workString, rand() % 9 + 1);
                /*
                  if ( maxData < minData ) { // Usually, the minimum is before the maximum, and sometimes it is not the default value.
                        auto temp = maxData;
                        maxData = minData;
                        minData = temp;
                    }
                    int number = rand() % (maxData - minData + 1) + minData;
                */
                //rand() % amplData + minData; // ints tous inclus.
                }
            return workString;
            }
        break;
        }
    }

bool testCombinaison(string manuelSuspect = "123456789") {
    if(manuelSuspect.size() != 9) { // Optimisation facile !
        return false;
        }
    bool un = false;
    bool deux = false;
    bool trois = false;
    bool quatre = false;
    bool cinq = false;
    bool six = false;
    bool sept = false;
    bool huit = false;
    bool neuf = false;
    for(int a = 0; a < manuelSuspect.size(); a++) {
        // Optimisation mauvaise, mais cela fonctionne !
        if(manuelSuspect[a] == '1') {
            un = true;
            }
        if(manuelSuspect[a] == '2') {
            deux = true;
            }
        if(manuelSuspect[a] == '3') {
            trois = true;
            }
        if(manuelSuspect[a] == '4') {
            quatre = true;
            }
        if(manuelSuspect[a] == '5') {
            cinq = true;
            }
        if(manuelSuspect[a] == '6') {
            six = true;
            }
        if(manuelSuspect[a] == '7') {
            sept = true;
            }
        if(manuelSuspect[a] == '8') {
            huit = true;
            }
        if(manuelSuspect[a] == '9') {
            neuf = true;
            }
        } // endfor.
    if(un && deux && trois && quatre && cinq && six && sept && huit && neuf) {
        return true;
        }
    // else all:
    return false;
    }

int input() { // Todo.
    int X = inputNb(1, 9);
    if(true) { // Envie d'ajouter un futur test.
        return X;
        }
    else {
        cerr << "Bad choice!" << endl;
        }
    }


int main() {
    srand(time(NULL));       // No need for better init.
    config();
    intro(lgg);
    int choixMenu = 0;
    string partie = "";
    while(!testCombinaison(partie)) {
        choixMenu = inputNb(-2, 20);
        partie = initMix(choixMenu);
        }
    replaceFileString(oldStart, partie);
    int coups = 0;
    int N = 0;
    while(partie != "123456789") {
        cout << partie << endl;
        N = input();
        coups++;
        partie = joue(partie, N);
        replaceFileString(oldContinue, partie);
        }
    cout << "Bravo ! Vous gagnez en " << coups << " coup";
    if(coups >= 2) // Le pluriel commence à 2 en français.
        { cout << "s";}
    cout << " !" << endl;
    cout << "Ok!" << endl;
    return 0;
    }
