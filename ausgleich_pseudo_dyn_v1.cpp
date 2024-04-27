/*
   tatsaechlich verwendete Arraylaenge "n" wird eingelesen
   pseudodynamische Arrays: Array mit NMAX Elementen angelegt,
   tatsaechliche Nutzung von n Elementen (n <= NMAX)
*/

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

/* maximale Vektorgroesse */
const int NMAX = 100;

struct Ausgleichsproblem
{
  int n{0};
  double x[NMAX];
  double y[NMAX];
};

int main(void)
{
  int i;
  double sx, sy, sxy, sx2, a, b;
  Ausgleichsproblem p{};
  do
  {
    cout << "Anzahl der Messwerte: ";
    cin >> p.n;
    if (p.n > NMAX || p.n < 0)
      cout << "Fehler! Anzahl n = " << p.n << " nicht moeglich!"
           << endl;
  } while (p.n > NMAX || p.n < 0);

  cout << "Einlesen der " << p.n << " Messwerte:" << endl;
  for (int i = 0; i < p.n; ++i)
  {
    cout << i + 1 << ". Messwert mit x- und y-Wert: ";
    cin >> p.x[i] >> p.y[i];
  }

  cout << endl;

  for (i = 0; i < p.n; i++)
    cout << "(x[" << setw(2) << i << "], y[" << setw(2) << i
         << "]) = (" << p.x[i] << ", " << p.y[i] << ")" << endl;

  sx = sy = sxy = sx2 = 0.0;
  for (i = 0; i < p.n; i++)
  {
    sx += p.x[i];
    sy += p.y[i];
    sxy += p.x[i] * p.y[i];
    sx2 += pow(p.x[i], 2);
  }

  a = (sxy - sx * sy / p.n) / (sx2 - pow(sx, 2) / p.n);
  b = (sy - a * sx) / p.n;
  cout << endl
       << "  Optimale Paramter (a,b) = ("
       << a << ", " << b << ")" << endl;

  return 0;
}
