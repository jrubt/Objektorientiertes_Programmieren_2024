/*
   Vorlage "vorlage_01a_stat_arr.cpp" umgeschrieben auf Struktur(en)

   wie "ausgleich.cpp", nur die statische Arrays an Funktionen uebergeben

   Im Unterschied zu "ausgleich_funktionen_v1.cpp" wurden die Funktionen so geschrieben,
   dass Arraylaenge und flexibel lange statische Arrays an Funktionen uebergeben werden koennen.

   Als Beispiel werden die Messpunkte verdoppelt und die Ausgleichsgerade fuer die
   verdoppelte Anzahl ebenfalls berechnet.
*/

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

/* tatsaechlich verwendete Vektorgroesse */
const int NMAX = 3, NMAX_DOPPELT = 2 * NMAX;

struct Gerade
{
  double a, b;
};

struct Koordinaten_Stat
{
  double koord[NMAX];
};

struct Koordinaten_Doppelt_Stat
{
  double koord[NMAX_DOPPELT];
};

void einlesen(Koordinaten_Stat &x, Koordinaten_Stat &y);
void einlesen_doppelt(Koordinaten_Doppelt_Stat &x, Koordinaten_Doppelt_Stat &y);
void verdoppeln(const Koordinaten_Stat &x_quelle, const Koordinaten_Stat &y_quelle, Koordinaten_Doppelt_Stat &x_doppelt, Koordinaten_Doppelt_Stat &y_doppelt);
void ausgabe(const Koordinaten_Stat &x, const Koordinaten_Stat &y);
void ausgabe_doppelt(const Koordinaten_Doppelt_Stat &x, const Koordinaten_Doppelt_Stat &y);
void ausgabe_gerade(const Gerade &g);
Gerade berechne_gerade(const Koordinaten_Stat &x, const Koordinaten_Stat &y);
Gerade berechne_gerade_doppelt(const Koordinaten_Doppelt_Stat &x, const Koordinaten_Doppelt_Stat &y);
Koordinaten_Stat bsp_satz_x_koord();
Koordinaten_Stat bsp_satz_y_koord();

int main(void)
{
  Gerade g1, g2;
  Koordinaten_Stat x1 = {bsp_satz_x_koord()}; // "copy-list-initialization"
  Koordinaten_Stat y1{bsp_satz_y_koord()};    // "direct-list-initialization" (C++11)
  // Koordinaten_Stat y1=(bsp_satz_y_koord());
  // Koordinaten_Stat y1(bsp_satz_y_koord());
  Koordinaten_Doppelt_Stat x2, y2;
  cout << "Beispieldatensatz:" << '\n';
  ausgabe(x1, y1);
  ausgabe_gerade(berechne_gerade(x1, y1));
  // Aufrufe als Kommentar beim Umschreiben belassen
  cout << "### einzelne Messpunkte ###" << endl;
  /*
  einlesen(NMAX, x1.koord, y1.koord);
  ausgabe(NMAX, x1.koord, y1.koord);
  berechne_gerade(NMAX, x1.koord, y1.koord, g1.a, g1.b);
  ausgabe_gerade(g1.a, g1.b);
  */
  einlesen(x1, y1);
  ausgabe(x1, y1);
  g1 = berechne_gerade(x1, y1);
  ausgabe_gerade(g1);
  cout << endl;

  cout << "### verdoppelte Messpunkte ###" << endl;
  verdoppeln(x1, y1, x2, y2);

  ausgabe_doppelt(x2, y2);
  g2 = berechne_gerade_doppelt(x2, y2);
  ausgabe_gerade(g2);

  return 0;
}

void einlesen(Koordinaten_Stat &x, Koordinaten_Stat &y)
{
  cout << "Einlesen der " << NMAX << " Messwerte:" << endl;
  cout << "  x-Werte eingeben:" << endl;
  int i{0};
  while (i < NMAX && !cin.fail())
  {
    cout << "    ";
    cin >> x.koord[i];
    ++i;
  }
  cout << endl;

  cout << "  y-Werte eingeben:" << endl;
  i = 0;
  while (i < NMAX && !cin.fail())
  {
    cout << "    ";
    cin >> y.koord[i];
    ++i;
  }
  cout << endl;
}

void einlesen_doppelt(Koordinaten_Doppelt_Stat &x, Koordinaten_Doppelt_Stat &y)
{
  cout << "Einlesen der " << NMAX_DOPPELT << " Messwerte:" << endl;
  cout << "  x-Werte eingeben:" << endl;
  int i{0};
  while (i < NMAX_DOPPELT && !cin.fail())
  {
    cout << "    ";
    cin >> x.koord[i];
    ++i;
  }
  cout << endl;

  cout << "  y-Werte eingeben:" << endl;
  i = 0;
  while (i < NMAX_DOPPELT && !cin.fail())
  {
    cout << "    ";
    cin >> y.koord[i];
    ++i;
  }
  cout << endl;
}

Koordinaten_Stat bsp_satz_x_koord()
{
  return Koordinaten_Stat({1.0, 2.0, 3.0});
}
Koordinaten_Stat bsp_satz_y_koord()
{
  return Koordinaten_Stat({2.5, 3.5, 4.5});
}
// jeder Messpunkt wird verdoppelt
void verdoppeln(const Koordinaten_Stat &x_quelle, const Koordinaten_Stat &y_quelle, Koordinaten_Doppelt_Stat &x_doppelt, Koordinaten_Doppelt_Stat &y_doppelt)
{
  for (int i = 0; i < NMAX; ++i)
  {
    x_doppelt.koord[2 * i] = x_doppelt.koord[2 * i + 1] = x_quelle.koord[i];
    y_doppelt.koord[2 * i] = y_doppelt.koord[2 * i + 1] = y_quelle.koord[i];
  }
  return;
}

void ausgabe(const Koordinaten_Stat &x, const Koordinaten_Stat &y)
{
  cout << "Ausgabe der Messwerte:" << endl;
  for (int i = 0; i < NMAX; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << x.koord[i] << ", " << y.koord[i] << ")" << endl;
}

void ausgabe_doppelt(const Koordinaten_Doppelt_Stat &x, const Koordinaten_Doppelt_Stat &y)
{
  cout << "Ausgabe der Messwerte:" << endl;
  for (int i = 0; i < NMAX_DOPPELT; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << x.koord[i] << ", " << y.koord[i] << ")" << endl;
}

Gerade berechne_gerade(const Koordinaten_Stat &x, const Koordinaten_Stat &y)
{
  double sx, sy, sxy, sx2;

  sx = sy = sxy = sx2 = 0.0;
  for (int i = 0; i < NMAX; i++)
  {
    sx += x.koord[i];
    sy += y.koord[i];
    sxy += x.koord[i] * y.koord[i];
    sx2 += pow(x.koord[i], 2.0);
  }

  double a = (sxy - sx * sy / NMAX) / (sx2 - pow(sx, 2.0) / NMAX);
  double b = (sy - a * sx) / NMAX;
  Gerade g{a, b};
  return g;
}

Gerade berechne_gerade_doppelt(const Koordinaten_Doppelt_Stat &x, const Koordinaten_Doppelt_Stat &y)
{
  double sx, sy, sxy, sx2;

  sx = sy = sxy = sx2 = 0.0;
  for (int i = 0; i < NMAX_DOPPELT; i++)
  {
    sx += x.koord[i];
    sy += y.koord[i];
    sxy += x.koord[i] * y.koord[i];
    sx2 += pow(x.koord[i], 2.0);
  }

  double a = (sxy - sx * sy / NMAX_DOPPELT) / (sx2 - pow(sx, 2.0) / NMAX_DOPPELT);
  double b = (sy - a * sx) / NMAX_DOPPELT;
  Gerade g{a, b};
  return g;
}

void ausgabe_gerade(const Gerade &g)
{
  cout << endl
       << "  Optimale Gerade : y = " << g.a << "*x + " << g.b << '\n';
}
