#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define long long long int

using namespace std;

struct pt {
    int x, y;

    pt operator - (pt p) { return { x - p.x, y - p.y }; }

    bool operator == (pt b) { return x == b.x && y == b.y; }
    bool operator != (pt b) { return !((*this == b)); }
    bool operator < (const pt& o) const { return y < o.y || (y == o.y && x < o.x); }
};

int cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
int orient(pt a, pt b, pt c) { return cross(b - a, c - a); }// clockwise = -
double norm(pt a) { return a.x * a.x + a.y * a.y; }
double abs(pt a) { return sqrt(norm(a)); }

struct polygon {
    vector<pt > p;
    polygon(int n) : p(n) {}

    void delete_repeated() {
        vector<pt> aux;
        sort(p.begin(), p.end());

        for (pt& i : p)
            if (aux.empty() || aux.back() != i)
                aux.push_back(i);
        p.swap(aux);
    }

    int top = -1;
    int bottom = -1;
    void normalize() {
        bottom = min_element(p.begin(), p.end()) - p.begin();
        vector<pt> tmp(p.begin() + bottom, p.end());
        tmp.insert(tmp.end(), p.begin(), p.begin() + bottom);
        p.swap(tmp);
        bottom = 0;
        top = max_element(p.begin(), p.end()) - p.begin();
    }

    void convex_hull() {
        sort(p.begin(), p.end());
        vector<pt> ch;
        ch.reserve(p.size() + 1);

        for (int it = 0; it < 2; it++) {
            int start = ch.size();
            for (auto& a : p) {
                // if colineal are needed, use < instead of <=, and remove repeated points
                while (ch.size() >= start + 2 && orient(ch[ch.size() - 2], ch.back(), a) <= 0)
                    ch.pop_back();
                ch.push_back(a);
            }
            ch.pop_back();
            reverse(p.begin(), p.end());
        }

        // Remove repeated points
        delete_repeated();
        if (ch.size() == 2 && ch[0] == ch[1]) ch.pop_back();
        p.swap(ch);
    }

    double perimeter() {
        double per = 0;
        for (int i = 0, n = p.size(); i < n; i++)
            per += abs(p[i] - p[(i + 1) % n]);
        return per;
    }
};

int main() {
    vector<pt> points{
    {41, -6}, {-24, -74},
    {-51, -6}, {73, 17}, {-30, -24}
    };

    polygon poly(points.size());

    for (int i = 0; i < points.size(); i++) {
        poly.p[i] = points[i];
    }

    poly.convex_hull();

    for (pt point : poly.p) {
        cout << point.x << " " << point.y << "\n";
    }

    return 0;
}
