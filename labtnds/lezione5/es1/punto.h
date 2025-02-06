#ifndef __VETTORE__
#define __VETTORE__

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Posizione {
public:
    Posizione() : m_x(0), m_y(0), m_z(0) {}

    Posizione(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

    friend istream& operator>>(istream& is, Posizione& p) {
        string temp;
        getline(is, temp, ',');
        p.m_x = stod(temp);
        getline(is, temp, ',');
        p.m_y = stod(temp);
        getline(is, temp, '\n');
        p.m_z = stod(temp);
        return is;
    }

    // Funzioni di accesso ai dati
    double getDistance() const { return sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }

    // Coordinate cartesiane
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }

    // Distanza da un altro punto
    double getDistance(const Posizione& p) const {
        double dx = p.getX() - m_x;
        double dy = p.getY() - m_y;
        double dz = p.getZ() - m_z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Conversione angolare (corretto uso della funzione di trigonometria)
    double angoloPxy() const {
        return atan2(m_y, m_x);
    }

    double angoloPxz() const {
        return atan2(m_z, m_x);
    }

    double angoloPyz() const {
        return atan2(m_z, m_y);
    }

    // Overload dell'operatore < per ordinamento
    bool operator<(const Posizione& b) const {
        return (getDistance() < b.getDistance());
    }

    void printPositions() const {
        cout << "Posizione: x = " << m_x << ", y = " << m_y << ", z = " << m_z << endl;
    }

private:
    double m_x, m_y, m_z;
};

// Algoritmo di riordinamento di un vettore di punti
template <typename Iter>
void findBestPath(Iter start, Iter end) {
    Posizione ref(0, 0, 0);
    for (auto it = start; it != end; ++it) {
        sort(it, end, [&ref](const Posizione& i, const Posizione& j) {
            return i.getDistance(ref) < j.getDistance(ref);
        });
        ref = *it;
    }
}

#endif // __VETTORE__
