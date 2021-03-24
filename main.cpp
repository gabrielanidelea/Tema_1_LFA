#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
ifstream fin("mealy.in");

int nr_noduri; //cardinalul starilor
int nr_tranzitii; //nr de tranzitii
int stare_initiala;
int f; //nr starilor finale
int* F; //adresa inceputului de vector pentru starile finale
int nr_stringuri; //nr cuvinte
int sc; //stare curenta

struct tranzitie
{
    int a; //starea de la care se porneste
    int b; //starea in care se ajunge
    char c; //cu ce simbol tranzitionam
    int d; //int-ul afisat de mealy

} G;

vector <tranzitie> tr;
vector <int> st;
vector <int> traseu;

void afis(vector<int> tras) //afisarea traseului
{
    for (int i = 0; i < tras.size(); i++)

        cout << tras[i] << " ";
    cout<<sc;
    cout << endl;


}

void afis1(vector<int> st) //afisarea output-urilor specifice Mealy
{
    for (int i = 0; i < st.size(); i++)

        cout << st[i];

    cout << endl;


}

int trecere(int curenta, char c)
{

    for (int i = 0; i < nr_tranzitii; i++)
        if ((tr[i].a == curenta) && (tr[i].c == c)) //daca avem o stare care duce cu un simbol din alfabet citit intr-o alta stare
        {
            st.push_back(tr[i].d);//, atunci salvam in vectorul st int-ul pe care dorim sa-l afisam ulterior
            traseu.push_back(curenta); // salvam in vectorul traseu starea curenta
            return tr[i].b; // returnam nodul in care am ajuns
        }

    return -1; // daca nu putem ajunge nicaieri, returnam -1
}

void citire()
{
    fin >> nr_noduri;
    fin >> nr_tranzitii;
    for (int i = 0; i < nr_tranzitii; i++)
    {
        fin >> G.a >> G.b >> G.c >> G.d;
        tr.push_back(G); // salvam in vectorul tr: starea 1, starea 2, simbolul si ce afiseaza
    }
    fin >> stare_initiala;
    fin >> f;//cardinalul starilor finale
    F = new int[f];
    for (int i = 0; i < f; i++)
        fin >> F[i]; //citire stari finale
    fin >> nr_stringuri;

}

bool verificare(string cuvant)
{
    sc = stare_initiala; // plecam cu sc din starea initiala, citita din fisier
    for (int i = 0; i < f; i++)
    {
        if (sc == F[i]) // daca sc se regaseste printe elementele vectorului de stari finale, atunci returnam 1
            return 1;
    }



    for (unsigned int i = 0; i < cuvant.length(); i++) // parcurgem literele cuvantului
    {

        sc = trecere(sc, cuvant[i]); // mutam starea in care ajungem parcurgand urmatoarea litera in variabila sc
        if (sc == -1) // daca nu ajungem nicaieri, sc va avea valoarea -1, iar functia verificare va returna 0
            return 0;
    }
    for (int i = 0; i < f; i++)// parcurgem starile finale si verificam daca sc se gaseste printre ele
        if (sc == F[i])
            return 1;// daca se gaseste, returnam 1
    return 0;// pentru orice alt caz(nefavorabil) returnam 0

}

int main()
{

    citire();
    string w;
    while (fin>>w) //citim cate un cuvant din fisier
    {
        if (verificare(w) == 1)
        {
            cout << "DA\n";
            afis1(st); //afisam output-ul specific Mealy
            cout << "Traseu:";
            afis(traseu); //afisam traseul prin care am ajuns cu succes intr-o stare finala

        }
        else
            cout << "NU\n";
        nr_stringuri--; // decrementam nr de stringuri
        st.erase(st.begin(), st.end()); // golim vectorul st pentru a putea trece la urmatorul cuvant
        traseu.erase(traseu.begin(), traseu.end()); //golim vectorul traseu pentru a putea trece la urmatorul cuvant

    }
    fin.close();
    return 0;
}
