#include<bits/stdc++.h>

#define EPS 1e-9
#define PI acos(-1.0)
using namespace std;

struct point{
    double x, y; // T should be preferably double
    point(){
        x = y = 0;
    }
    point(double _x, double _y) : x(_x), y(_y){}

    bool operator< (point other) const{
        if(fabs(x - other.x)>EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator== (point other){
        return (fabs(x - other.x)<EPS && (fabs(y - other.y)<EPS));
    }

    double hypot(double dx, double dy){
        return (double)sqrt(dx*dx + dy*dy);
    }
    double dist(point p1, point p2){
        return hypot(p1.x-p2.x, p1.y-p2.y);
    }

    double DEG_to_RAD(double theta){
        double rad = theta * PI; rad /= (double)(360.0);
        return rad;
    }

    point rotateCCW(point p, double theta){  //rotating counter-clockwise by angle 0;
        double rad = DEG_to_RAD(theta);
        return point(p.x * cos(rad) - p.y * sin(rad),
                     p.x * sin(rad) + p.y * cos(rad));
    }
};


struct line : point {
    /* representing a line ax + by + c = 0;
     assumption: b=1 for non vertical line,
     and b=0 for vertical line.*/
    double a, b, c;

    /* computing line from 2 points */
    void pointToLine(point p1, point p2, line &l){
        if(fabs(p1.x-p2.x) < EPS){
            l.a = 1.0; l.b = 0.0; l.c = -p1.x;
        }
        else {
            l.a = -(double)(p1.y - p2.y)/(p1.x - p2.x);
            l.b = 1.0;
            l.c = -(double)(l.a * p1.x) - p1.y;
        }
    }

    bool areParellel(line l1, line l2){
        return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
    }

    bool areSame(line l1, line l2){
        return areParellel(l1,l2) && (fabs(l1.c-l2.c)<EPS);
    }

    bool areIntersect(line l1, line l2, point &p){
        if(areParellel(l1, l2))
            return false;
        p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
        if(fabs(l1.b)>EPS)
            p.y = -(l1.a * p.x + l1.c);
        else
            p.y = -(l2.a * p.x + l2.c);
        return true;
    }
};

struct vec : line {
    double x, y;

    vec() { }
    vec(double _x, double _y): x(_x), y(_y) {}
    vec toVec(point a, point b){
        return vec(b.x - a.x, b.y - a.y);
    }
    vec scale(vec v, double s){
        return vec(v.x * s, v.y * s);
    }

    point translate(point p, vec v){
        return point(p.x + v.x, p.y + v.y);
    }

    double dot(vec a, vec b){
        return (a.x*b.x + a.y*b.y);
    }

    double norm_sq(vec v){
        return v.x * v.x + v.y * v.y;
    }

     /* return the distance from p to the line
        defined by two points a and b (a & b
        must be different) the closest point is
        stored in the 4th parameter */
    double distToLine(point p, point a, point b, point &c){
        // formula c = a + u * ab;
        vec ap = toVec(a, p), ab = toVec(a, b);
        double u = dot(ap, ab) / norm_sq(ab);
        c = translate(a, scale(ab, u));
        return dist(p, c);
    }

    double distToLineSegment(point p, point a, point b, point &c){
        vec ap = toVec(a, p), ab = toVec(a, b);
        double u = dot(ap, ab) / norm_sq(ab);
        if(u<0.0){
            c = point(a.x, a.y);
            return dist(p, a);
        }
        if(u>1.0){
            c = point(b.x, b.y);
            return dist(p, b);
        }
        return distToLine(p, a, b, c);
    }

    // to compute angle aob in rad
    double angle(point a, point o, point b){
        vec oa = toVec(o, a), ob = toVec(o, b);
        return acos(dot(oa, ob)/ sqrt(norm_sq(oa) * norm_sq(ob)));
    }

    double cross(vec a, vec b){
        return a.x*b.y - a.y*b.x;
    }

    // returns one if r is in left of the
    // line segment pr(p->r).
    bool ccw(point p, point q, point r){
        return cross(toVec(p,q), toVec(p,r)) >= 0;
    }

    bool collinear(point p, point q, point r){
        return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
    }
};

struct Polygon : vec {
    vector<point> P;

    Polygon(){
        P.resize(0);
    }

    bool isConvex(const vector<point> &P){
        int sz = (int)P.size();
        if(sz <= 3)
            return false;
        bool isLeft = ccw(P[0], P[1], P[2]);
        for(int i=1; i<sz-1; i++){
            if(ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft){
                return false;
            }
        }
        return true;
    }

    bool inPolygon(point pt, const vector<point> &P){
        if((int)P.size() == 0)
            return false;
        for(int i=0;i<P.size();i++){
            if(pt == P[i])
                return true;
        }
        double sum = 0;
        for(int i=0; i<(int)P.size()-1; i++){
            if(ccw(pt, P[i], P[i+1]))
                sum += angle(P[i], pt, P[i+1]);
            else
                sum -= angle(P[i], pt, P[i+1]);
        }
        return fabs(fabs(sum) - 2*PI) < EPS;
    }

    point lineIntersectSeg(point p, point q, point A, point B){
        double a = B.y - A.y;
        double b = A.x - B.x;
        double c = B.x * A.y - A.x * B.y;
        double u = fabs(a * p.x + b * p.y + c);
        double v = fabs(a * q.x + b * q.y + c);
        return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
    }

    // cuts polygon Q along the line formed by point a -> point b
    // This only gives the left side of the polygon
    // change ineuality sign in two if-statements for right side
    vector<point> cutPolygon(point a, point b, const vector<point> &Q){
        vector<point> P;
        for(int i=0; i<(int)Q.size(); i++){
            double left1 = cross(toVec(a,b), toVec(a, Q[i])), left2 = 0;
            if(i != (int)Q.size()-1)
                left2 = cross(toVec(a,b), toVec(a, Q[i+1]));
                if(left1 > -EPS) // Q is on the left side of ab
                    P.push_back(Q[i]);
                if(left1 * left2 < -EPS)
                    P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
        }
        if(!P.empty() && !(P.back() == P.front()))
            P.push_back(P.front());
        return P;
    }

    /* Convex Hull - Graham's Scan */
    point pivot = point(0,0);
    bool angleCmp(const point &a,const point &b){
        if(collinear(pivot, a, b))
            return dist(pivot, a) < dist(pivot, b);
        double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
        double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
        return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
    }

    vector<point> CHGraham(vector<point> P){
        int i, j, N = (int)P.size();
        if(N <= 3){
            if(!(P[0]==P[N-1]))
                P.push_back(P[0]);
            return P;
        }
        int P0 = 0;
        for(i=1;i<N;i++){
            if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
                P0 = i;
        }
        // Swap
        point temp = P[0]; P[0] = P[P0]; P[P0] = temp;

        pivot = P[0];
        sort(++P.begin(), P.end(),
            [&](point &a,point &b){ if(collinear(pivot, a, b))
                                        return dist(pivot, a) < dist(pivot, b);
                                    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
                                    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
                                        return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
                                });

        vector<point> S;
        S.push_back(P[N-1]); S.push_back(P[0]); S.push_back(P[1]);
        i = 2;
        while(i<N){
            j = (int)S.size()-1;
            if(ccw(S[j-1],S[j],P[i]))
                S.push_back(P[i++]);
            else
                S.pop_back();
        }
        return S;
    }

    vector<point> CHMonotone(vector<point> P){
        int N = P.size(), k = 0;
        if(N == 1)
            return P;
        vector<point> H(2*N);
        sort(P.begin(), P.end());

        // = 0 in cross()<=0 return value leads to elimination of inbetween collinear pts.
        // for example, if 1,2,3,4 pts all on same line then 2,3 will be removed
        for(int i=0; i<N; ++i){
            while(k >= 2 && cross(toVec(H[k-2], H[k-1]), toVec(H[k-1],P[i]))<=0)
                k--;
            H[k++] = P[i];
        }

        for(int i = N-2, t = k+1; i>=0; i--){
            while(k>=t && cross(toVec(H[k-2], H[k-1]), toVec(H[k-1], P[i]))<= 0)
                k--;
            H[k++] = P[i];
        }

        H.resize(k-1);
        H.push_back(H[0]);
        return H;
    }

};


int main(){

    Polygon A;
    A.P.push_back(point(0,0));
    A.P.push_back(point(1,0));
    A.P.push_back(point(2,0));
    A.P.push_back(point(2,2));
    A.P.push_back(point(0,2));

    /*if(A.isConvex(A.P)){
        cout << "Convex hai bhai \n";
    }
    else{
        cout << "nahi hai convex :|\n";
    }*/

    /*if(A.inPolygon(point(0,0),A.P)){
        cout << "inside\n";
    }
    else{
        cout << "outside\n";
    }*/

    vector<point> H = A.CHGraham(A.P);
    for(int i=0;i<H.size();i++){
        cout << "(" << H[i].x << "," << H[i].y << ")\t";
    }
    cout << "\n";
    H = A.CHMonotone(A.P);
    for(int i=0;i<H.size();i++){
        cout << "(" << H[i].x << "," << H[i].y << ")\t";
    }
    cout << "\n";

    return 0;
}
