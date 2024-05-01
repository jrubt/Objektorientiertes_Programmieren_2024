#include <cassert> // fuer assert(..)-Makro
#include <cmath>
#include <cstdlib> // fuer exit(..)-Fkt.
#include <iomanip>
#include <iostream>
#include <new>

using namespace std;

double *anlegen(int n);

// selbst definierter 2D-Vektor, da die Loesung 2 Komponenten hat
struct Gerade
{
  double a{0};
  double b{0};
};

struct Messreihe
{
  int n;
  string name;
  double *x;
  double *y;
  Messreihe(int ){
  };
  Messreihe()
  {
    int i = 0;
    cout << "Einlesen der Messwerte:" << endl;

    cout << "  Anzahl der Messwerte: ";
    cin >> n;
    cout << "  Name der Messreihe: ";
    cin >> name;

    x = anlegen(n);
    y = anlegen(n);
    cout << "  x-Werte eingeben: ";
    while (i < n && !cin.fail())
    {
      cin >> x[i];
      ++i;
    }
    cout << "  y-Werte eingeben: ";
    i = 0;
    while (i < n && !cin.fail())
    {
      cin >> y[i];
      ++i;
    }
    cout << endl;
  };
};

void ausgabe(const Messreihe &p);
void ausgabe_gerade(const Gerade &v);
Gerade berechne_gerade(const Messreihe &p);
void freigabe(Messreihe &p);

int main(void)
{
  // initialisieren mit default-Werten
  //Messreihe p = Messreihe();
Messreihe p{
    //
      3,
      "nur angelegte Messreihe mit 3 Werten",
      new double[3]{1.0, 2.0, 3.0},
      new double[3]{2.5, 3.5, 4.5}
  };
  ausgabe(p);

  Gerade lsg{berechne_gerade(p)};
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

  assert(v != nullptr); // falls Bedingung NICHT zutrifft, wird Programm beendet
                        //   mit Hinweis auf diese Sourcecodezeile
  return v;
}

void ausgabe(const Messreihe &p)
{
  cout << "Ausgabe der Messwerte fuer " << p.name << " :" << endl;
  for (int i = 0; i < p.n; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << p.x[i] << ", " << p.y[i] << ")" << endl;
}

Gerade berechne_gerade(const Messreihe &p)
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
  return Gerade{a, b};
}

void ausgabe_gerade(const Gerade &v)
{
  cout << endl
       //      << "  Optimale Paramter (a,b) = ("
       //      << v.a << ", " << v.b << ")" << endl;
       << "  Optimale Gerade : y = " << v.a << "*x + " << v.b << '\n';
}

void freigabe(Messreihe &p)
{
  delete[] p.x;
  p.x = nullptr;
  delete[] p.y;
  p.y = nullptr;
}
