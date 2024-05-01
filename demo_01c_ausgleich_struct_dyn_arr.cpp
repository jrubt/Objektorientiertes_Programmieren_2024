/*
   Vorlage "vorlage_01c_dyn_arr.cpp" umgeschrieben auf Struktur(en)
*/

#include <cassert> // fuer assert(..)-Makro
#include <cmath>
#include <cstdlib> // fuer exit(..)-Fkt.
#include <iomanip>
#include <iostream>
#include <new>

using namespace std;

// selbst definierter 2D-Vektor, da die Loesung 2 Komponenten hat
struct Gerade
{
  // Initialisierungswerte 0 fuer die beiden Strukturkomponenten durch "{0}",
  //   wenn beim Anlegen der zugeh. Strukturvariable keine Initialisierung vorgenommen wird
  double a{0};
  double b{0};
};

struct Messreihe_Dyn
{
  int n{0};
  string name{"Messreihe"}; // optional
  double *x{nullptr};
  double *y{nullptr};
};

void einlesen(Messreihe_Dyn &p);
double *anlegen(int n);
void ausgabe(const Messreihe_Dyn &p);
void ausgabe_gerade(const Gerade &v);
Gerade berechne_gerade(const Messreihe_Dyn &p);
void freigabe(Messreihe_Dyn &p);

int main(void)
{
  // Ueberschreiben der Initialisierungswerte in der Struktur
  Messreihe_Dyn p_bsp{
      // "designated initialization" (C++20)
      // (unvollstaendige Wertzuweisung moeglich, Reihenfolge der Komponenten darf aber nicht geaendert werden)
      .n = 3,
      //"nur angelegte Messreihe mit 3 Werten",
      .x = new double[3]{1.0, 2.0, 3.0},
      .y = new double[3]{2.5, 3.5, 4.5}};
  p_bsp.name = "nur angelegte Messreihe mit 3 Werten";

  cout << "Beispieldatensatz:" << '\n';
  ausgabe(p_bsp);

  // Initialisieren mit default-Werten, die in Strukturdefinition mit "{..}" gesetzt wurden
  Messreihe_Dyn p;
  einlesen(p);
  ausgabe(p);

  Gerade lsg;
  lsg = berechne_gerade(p);
  ausgabe_gerade(lsg);

  // Freigabe der dynam. Arrays noetig
  freigabe(p);

  return 0;
}

double *anlegen(int n)
{
  double *v;

  // Anlegen des Speichers
  v = new (nothrow) double[n];

  // if (v == nullptr)
  // {
  //   cerr << "Fehler beim Anlegen vom Vektor v mit " << n < " double-Elementen!" << endl;
  //   exit(1);
  // }
  assert(v != nullptr); // falls Bedingung NICHT zutrifft, wird Programm beendet
                        //   mit Hinweis auf diese Sourcecodezeile
  return v;
}

void einlesen(Messreihe_Dyn &p)
{

  int i = 0;

  cout << "Name der Messreihe:" << endl;
  cout << "  ";
  getline(cin, p.name);

  cout << "Einlesen der Messreihe:" << endl;
  cout << "  Anzahl der Messwerte: ";
  cin >> p.n;
  cout << endl;

  p.x = anlegen(p.n);
  p.y = anlegen(p.n);

  cout << "  x-Werte eingeben:" << endl;
  while (i < p.n && !cin.fail())
  {
    cout << "    ";
    cin >> p.x[i];
    ++i;
  }
  cout << endl;

  cout << "  y-Werte eingeben:" << endl;
  i = 0;
  while (i < p.n && !cin.fail())
  {
    cout << "    ";
    cin >> p.y[i];
    ++i;
  }
  cout << endl;
}

void ausgabe(const Messreihe_Dyn &p)
{
  // nicht erlaubt:
  //   x[0] = -1;

  cout << "Ausgabe der Messwerte fuer " << p.name << ":" << endl;
  for (int i = 0; i < p.n; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << p.x[i] << ", " << p.y[i] << ")" << endl;
}

Gerade berechne_gerade(const Messreihe_Dyn &p)
{
  double sx, sy, sxy, sx2;

  sx = sy = sxy = sx2 = 0.0;
  for (int i = 0; i < p.n; i++)
  {
    sx += p.x[i];
    sy += p.y[i];
    sxy += p.x[i] * p.y[i];
    sx2 += pow(p.x[i], 2);
  }

  double a = (sxy - sx * sy / p.n) / (sx2 - pow(sx, 2) / p.n);
  double b = (sy - a * sx) / p.n;

  /*
    Gerade g = { a, b };  // Strukturvariable mit Variablennamen)
    return g;
  */

  return {a, b}; // "anonyme" Strukturvariable (ohne Variablennamen)
                 //   mit den Werten a, b zurueckgeben
                 //  es geht sogar ohne Typangabe;
}

void ausgabe_gerade(const Gerade &v)
{
  cout << endl
       //      << "  Optimale Paramter (a,b) = ("
       //      << v.a << ", " << v.b << ")" << endl;
       << "  Optimale Gerade : y = " << v.a << "*x + " << v.b << '\n';
}

void freigabe(Messreihe_Dyn &p)
{
  delete[] p.x;
  p.x = nullptr;
  delete[] p.y;
  p.y = nullptr;
}
