/*
   Vorlage "vorlage_01b_pseudo_dyn_arr.cpp" umgeschrieben auf Struktur(en)

   tatsaechlich verwendete Arraylaenge "n" wird eingelesen
   pseudodynamische Arrays: Array mit NMAX Elementen angelegt,
     tatsaechliche Nutzung von n Elementen (n <= NMAX)
*/

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

/* maxgitimale Vektorgroesse */
const int NMAX = 100;
const int NMAX_DOPPELT{2 * NMAX};

struct Gerade
{
  double a, b;
};

struct Messreihe_PseudoDyn
{
  int n;
  double x[NMAX_DOPPELT];
  double y[NMAX_DOPPELT];
};

void einlesen(Messreihe_PseudoDyn &m);
void verdoppeln(const Messreihe_PseudoDyn &m_quelle, Messreihe_PseudoDyn &m_doppelt);
void ausgabe(const Messreihe_PseudoDyn &m);
void ausgabe_gerade(const Gerade &g);
Gerade berechne_gerade(const Messreihe_PseudoDyn &m);
Messreihe_PseudoDyn bsp_satz();

int main(void)
{
  Gerade g1, g2;
  Messreihe_PseudoDyn m1{bsp_satz()};
  Messreihe_PseudoDyn m2;
  cout << "Beispieldatensatz:" << '\n';
  ausgabe(m1);
  ausgabe_gerade(berechne_gerade(m1));
  // Aufrufe als Kommentar beim Umschreiben belassen
  cout << "### einzelne Messpunkte ###" << endl;
  /*
  einlesen(NMAX, m1.x, y1.x);
  ausgabe(NMAX, m1.x, y1.x);
  berechne_gerade(NMAX, m1.x, y1.x, g1.a, g1.b);
  ausgabe_gerade(g1.a, g1.b);
  */
  einlesen(m1);
  ausgabe(m1);
  g1 = berechne_gerade(m1);
  ausgabe_gerade(g1);
  cout << endl;

  cout << "### verdoppelte Messpunkte ###" << endl;
  verdoppeln(m1, m2);

  ausgabe(m2);
  g2 = berechne_gerade(m2);
  ausgabe_gerade(g2);

  return 0;
}

void einlesen(Messreihe_PseudoDyn &m)
{
  cout << "Einlesen der Messreihe:" << endl;
  int l;
  do
  {
    cout << "Anzahl der Messwerte: ";
    cin >> l;
    if (l > NMAX || l < 0)
      cout << "Fehler! Anzahl n = " << l << " nicht moeglich!"
           << endl;
  } while (l > NMAX || l < 0);
  m.n = l;
  cout << "Einlesen der " << m.n << " Messwerte:" << endl;
  cout << "  x-Werte eingeben:" << endl;
  int i{0};
  while (i < m.n && !cin.fail())
  {
    cout << "    ";
    cin >> m.x[i];
    ++i;
  }
  cout << endl;

  cout << "  y-Werte eingeben:" << endl;
  i = 0;
  while (i < m.n && !cin.fail())
  {
    cout << "    ";
    cin >> m.y[i];
    ++i;
  }
  cout << endl;
}

Messreihe_PseudoDyn bsp_satz()
{
  return Messreihe_PseudoDyn{3, {1.0, 2.0, 3.0}, {2.5, 3.5, 4.5}};
}

// jeder Messpunkt wird verdoppelt
void verdoppeln(const Messreihe_PseudoDyn &m_quelle, Messreihe_PseudoDyn &m_doppelt)
{
  m_doppelt.n = 2 * m_quelle.n;
  for (int i = 0; i < m_quelle.n; ++i)
  {
    m_doppelt.x[2 * i] = m_doppelt.x[2 * i + 1] = m_quelle.x[i];
    m_doppelt.y[2 * i] = m_doppelt.y[2 * i + 1] = m_quelle.y[i];
  }
  return;
}

void ausgabe(const Messreihe_PseudoDyn &m)
{
  cout << "Ausgabe der Messwerte:" << endl;
  for (int i = 0; i < m.n; i++)
  {
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << m.x[i] << ", " << m.y[i] << ")" << endl;
  }
}

Gerade berechne_gerade(const Messreihe_PseudoDyn &m)
{
  double sm, sy, smy, sm2;

  sm = sy = smy = sm2 = 0.0;
  for (int i = 0; i < m.n; i++)
  {
    sm += m.x[i];
    sy += m.y[i];
    smy += m.x[i] * m.y[i];
    sm2 += pow(m.x[i], 2.0);
  }

  double a = (smy - sm * sy / m.n) / (sm2 - pow(sm, 2.0) / m.n);
  double b = (sy - a * sm) / m.n;
  Gerade g{a, b};
  return g;
}

void ausgabe_gerade(const Gerade &g)
{
  cout << endl
       << "  Optimale Gerade : y = " << g.a << "*x + " << g.b << '\n';
}