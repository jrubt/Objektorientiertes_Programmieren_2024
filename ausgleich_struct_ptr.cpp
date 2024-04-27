#include <cassert> // fuer assert(..)-Makro
#include <cmath>
#include <cstdlib> // fuer exit(..)-Fkt.
#include <iomanip>
#include <iostream>
#include <new>

using namespace std;

// selbst definierter 2D-Vektor, da die Loesung 2 Komponenten hat
struct Vector
{
  double a{0};
  double b{0};
};

struct Ausgleichsproblem
{
  int n{0};
  string name{"default"};
  double *x{nullptr};
  double *y{nullptr};
};

void einlesen(Ausgleichsproblem &p);
double *anlegen(int n);
void ausgabe(const Ausgleichsproblem &p);
void ausgabe_gerade(const Vector &v);
Vector berechne_gerade(const Ausgleichsproblem &p);
void freigabe(Ausgleichsproblem &p);

int main(void)
{
  // initialisieren mit default-Werten
  Ausgleichsproblem p{};

  einlesen(p);
  ausgabe(p);
  
  Vector lsg{berechne_gerade(p)};
  ausgabe_gerade(lsg);

  // Freigabe
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

void einlesen(Ausgleichsproblem &p)
{
  int i = 0;
  cout << "Einlesen der Messwerte:" << endl;

  cout << "  Anzahl der Messwerte: ";
  cin >> p.n;
  cout << "  Name der Messreihe: ";
  cin >> p.name;

  p.x = anlegen(p.n);
  p.y = anlegen(p.n);
  cout << "  x-Werte eingeben: ";
  while (i < p.n && !cin.fail())
  {
    cin >> p.x[i];
    ++i;
  }
  cout << "  y-Werte eingeben: ";
  i = 0;
  while (i < p.n && !cin.fail())
  {
    cin >> p.y[i];
    ++i;
  }
  cout << endl;
}

void ausgabe(const Ausgleichsproblem &p)
{
  // nicht erlaubt:
  //   x[0] = -1;

  cout << "Ausgabe der Messwerte fuer " << p.name << " :" << endl;
  for (int i = 0; i < p.n; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << p.x[i] << ", " << p.y[i] << ")" << endl;
}

Vector berechne_gerade(const Ausgleichsproblem &p)
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
  return Vector{a, b};
}

void ausgabe_gerade(const Vector &v)
{
  cout << endl
       //      << "  Optimale Paramter (a,b) = ("
       //      << v.a << ", " << v.b << ")" << endl;
       << "  Optimale Gerade : y = " << v.a << "*x + " << v.b << '\n';
}

void freigabe(Ausgleichsproblem &p)
{
  delete[] p.x;
  p.x = nullptr;
  delete[] p.y;
  p.y = nullptr;
}
