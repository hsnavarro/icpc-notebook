#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.);

struct point{
  double x, y;
  point() : x(0.0), y(0.0) {}
  point(double x, double y) : x(x), y(y) {}
  point operator +(point b){ return point(x+b.x, y+b.y); }
  point operator -(point b){ return point(x-b.x, y-b.y); }
  point operator *(double k) { return point(x*k, y*k); }
  point operator /(double k) { return point(x/k, y/k); }
  double operator %(point b) { return x*b.y - y*b.x; }
};

double dist(point p1, point p2){ return hypot(p1.x - p2.x, p1.y - p2.y); }

point rot90cw(point p1){ return point(p1.y, -p1.x); }

struct circle{
  point c;
  double r;
  circle() { c = point(); r = 0; }
  circle(point c, double r) : c(c), r(r) {}
  bool contains(point p) { return dist(c, p) <= r + EPS; }
};

circle circumcircle(point a, point b, point c) {
	point u = rot90cw(b-a);
  point v = rot90cw(c-a);
	point n = (c-b)/2;
  point ans = ((a+c)/2) + (v*((u%n)/(v%u)));
  return circle(ans, dist(ans, a));
}

// Welzl - Minimum Enclosing Circle O(n)
circle minimumCircle(vector<point> p){
  random_shuffle(p.begin(), p.end());
  circle C = circle(p[0], 0.0);
  for(int i = 0; i < p.size(); i++){ 
    if(C.contains(p[i])) continue; 
    C = circle(p[i], 0.0);
    for(int j = 0; j < i; j++){ 
      if(C.contains(p[j])) continue; 
      C = circle((p[j] + p[i])/2, dist(p[j], p[i])/2);
      for(int k = 0; k < j; k++){ 
        if(C.contains(p[k])) continue; 
        C = circumcircle(p[j], p[i], p[k]); 
      } 
    } 
  }
  return C;
}

