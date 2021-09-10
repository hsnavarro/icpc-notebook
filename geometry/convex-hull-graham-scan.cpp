// Convex Hull Graham's Scan Algorithm O(nlogn)

struct Point{
    int x, y;
    Point(int x = 0, int y = 0):x(x), y(y) {}
    Point operator-(Point p){ return Point(x - p.x, y - p.y); }
    Point operator+(Point p){ return Point(x + p.x, y + p.y); }
    int operator%(Point p){ return x*p.y - y*p.x; }
    int operator*(Point p){ return x*p.x + y*p.y; }
};

vector<Point> pts, hull;
Point ori;
//ori -> the highest leftmost point

bool cmp(Point a, Point b){
    if((b - ori) % (a - ori) > 0) return false;
    if((b - ori) % (a - ori) == 0 and (b - ori)*(b - ori) < (a - ori)*(a - ori)) return false;
    return true;
}

void convex_hull (vector<Point>& pts){
    sort(pts.begin() + 1, pts.end(), cmp);
    hull.pb(pts[0]);
    hull.pb(pts[1]);
    for(int i = 2; i < pts.size(); i++){
        while((hull[hull.size()-1] - hull[hull.size()-2]) % (pts[i] - hull[hull.size()-1]) <= 0) hull.pop_back();
        hull.pb(pts[i]);
    }
}
