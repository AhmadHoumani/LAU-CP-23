#include <complex>

typedef complex<double> point;

#define X real()
#define Y imag()
#define polar(r, t) (r * exp(point(0, t)))
#define length(a) hypot(a.X, a.Y)
#define angle(a) atan2(a.Y, a.X)
#define vec(a, b) (b - a)
#define dot(a, b) ((conj(a) * b).X)
#define cross(a, b) ((conj(a) * b).Y)
#define lengthsqr(a) dot(a, a)
#define vec_rot(v, t) (v * exp(point(0, t)))
#define vec_rot_around(v, t, a) (vec_rot(vec(a, v), t) + a)
#define reflect(v, m) (conj(v / m) * m)
#define normalize(v) (v / length(v))
#define ccw(a, b, c) (cross(vec(a, b), vec(a, c)) > EPS)
#define same(a, b) (lengthsqr(vec(a, b)) < EPS)

bool three_points_collinear(const point &a, const point &b, const point &c)
{
  return (a.Y - b.Y) * (a.X - c.X) == (a.Y - c.Y) * (a.X - b.X);
}

bool point_on_ray(const point &a, const point &b, const point &p)
{
  return fabs(cross(vec(a, b), vec(a, p))) < EPS && dot(vec(a, b), vec(a, p)) > -EPS;
}

bool point_on_line(const point &a, const point &b, const point &p)
{
  return fabs(cross(vec(a, b), vec(a, p))) < EPS;
}

bool point_on_segment(const point &a, const point &b, const point &p)
{
  if(lengthsqr(vec(a, b)) < EPS)
      return lengthsqr(vec(a, p)) < EPS;
  return point_on_ray(a, b, p) && point_on_ray(b, a, p);
}

point divide_line_by_ratio(const point &a, const point &b, const double &r)
{
  return a + r * (b - a);
}

double point_line_distance(const point &a, const point &b, const point &p, point &res)
{
  double temp = dot(vec(a, b), vec(a, p)) / lengthsqr(vec(a, b));
  res = divide_line_by_ratio(a, b, temp);
  return length(vec(res, p));
}

double point_segment_min_distance(const point &a, const point &b, const point &p, point &res)
{
  if(a.X == b.X && a.Y == b.Y)
  {
      res = point(a.X, a.Y);
      return length(vec(res, p));
  }
  double temp = dot(vec(a, b), vec(a, p)) / lengthsqr(vec(a, b));
  if(temp < EPS)
  {
      res = point(a.X, a.Y);
      return length(vec(res, p));
  }
  if(temp > 1)
  {
      res = point(b.X, b.Y);
      return length(vec(res, p));
  }
  return point_line_distance(a, b, p, res);
}

double triangle_area(const point &a, const point &b, const point &c)
{
  return 0.5 * fabs(cross(vec(a, b), vec(b, c)));
}

bool line_intersection(const point &a, const point &b, const point &p, const point &q, point &res)
{
  double d1 = cross(vec(a, p), vec(a, b));
  double d2 = cross(vec(a, q), vec(a, b));
  if(fabs(d1 - d2) < EPS) return false;
  res = (d1 * q - d2 * p) / (d1 - d2);
  return true;
}

bool segment_intersection(const point &a, const point &b, const point &p, const point &q, point &res)
{
  if(!line_intersection(a, b, p, q, res))
      return false;
  if(!point_on_segment(a, b, res) || !point_on_segment(p, q, res))
      return false;
  return true;
}

double angle_between_three_points(const point &a, const point &b, const point &c)
{
  double ang = dot(vec(a, b), vec(a, c));
  ang /= length(vec(a, b));
  ang /= length(vec(a, c));
  return acos(ang);
}

double angle_between_three_points2(const point &a, const point &b, const point &c)
{
  double aa=atan2(b.Y-a.Y,b.X-a.X);
  if(aa<-EPS)
    aa+=2*PI;
  double bb=atan2(c.Y-a.Y,c.X-a.X);
  if(bb<-EPS)
    bb+=2*PI;
  return aa - bb;
}

bool point_inside_rec(const point &a, const point &b, const point &p)
{
  return p.X >= a.X && p.Y <= a.Y && p.X <= b.X && p.Y >= b.Y;
}

double sign(const point &a, const point &b, const point &c)
{
  return (a.X - c.X) * (b.Y - c.Y) - (b.X - c.X) * (a.Y - c.Y);
}

bool point_inside_triangle(const point &a, const point &b, const point &c, const point &p)
{
  bool b1, b2, b3;
  b1 = sign(p, a, b) < 0.0;
  b2 = sign(p, b, c) < 0.0;
  b3 = sign(p, c, a) < 0.0;
  return ((b1 == b2) && (b2 == b3));
}

bool check_square(vector<point> &points)
{
	vector<double> y;
	for(int i=0;i<4;i++)
		for(int j=i+1;j<4;j++)
			y.push_back(lengthsqr(vec(points[i], points[j])));
	sort(y.begin(),y.end());
	if(y[0] > EPS && fabs(y[0]-y[1]) <= EPS && fabs(y[0]-y[2]) <= EPS && fabs(y[0]-y[3]) <= EPS)
		if(fabs(y[4]-y[5]) <= EPS)
			return true;
	return false;
}

int Right_or_Left(const point &a, const point &b, const point &x)
{
  double temp = (b.X - a.X) * (x.Y - a.Y) - (b.Y - a.Y) * (x.X - a.X);
  if(temp > EPS) return 1;
  if(temp < -EPS) return -1;
  return 0;
}

vector<point> circle_circle_intersection(point a, double r1, point b, double r2)
{
  vector<point> res;
  if(fabs(a.X - b.X) < EPS && fabs(a.Y - b.Y) < EPS)
  {
    if(fabs(r1 - r2) < EPS)
    {
      if(r1 < EPS && r2 < EPS)
        res.pb(a);
      else
      {
        res.pb(point(0, 0));
        res.pb(point(0, 0));
        res.pb(point(0, 0));
      }
    }
    return res;
  }
  if(r1 < r2)
  {
    swap(a, b);
    swap(r1, r2);
  }
  double d = (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
  if(r2 < EPS)
  {
    if(fabs(sqrt(d) - r1) < EPS)
      res.pb(b);
    return res;
  }
  if(fabs((r1 + r2) * (r1 + r2) - d) < EPS)
  {
    double t = r1 / (r1 + r2);
    res.pb(a + t * (b - a));
    return res;
  }
  if(fabs((r1 - r2) * (r1 - r2) - d) < EPS)
  {
    double t = r1 / (r1 - r2);
    res.pb(a + t * (b - a));
    return res;
  }
  if((r1 + r2) * (r1 + r2) < d || (r1 - r2) * (r1 - r2) > d) return res;
  point v = vec(a, b);
  v *= r1 / sqrt(d);
  double theta = acos((r1 * r1 + d - r2 * r2) / (2.0 * sqrt(d) * r1));
  res.pb(a + vec_rot(v, theta));
  res.pb(a + vec_rot(v, -theta));
  return res;
}

vector<point> line_circle_intersection(const point &x, int r, const point &a, const point &b)
{
  vector<point> res;
  double A = dot(vec(a, b), vec(a, b));
  double B = 2 * dot(vec(a, b), vec(x, a));
  double C = dot(vec(x, a), vec(x, a));
  C -= r * 1.0 * r;
  double tmp = B * B - 4 * A * C;
  if(tmp < 0)
    return res;
  if(tmp == 0)
    res.pb(a - B / (2.0 * A) * (b - a));
  else
  {
    tmp = sqrt(tmp);
    res.pb(a + (-B + tmp) / (2.0 * A) * (b - a));
    res.pb(a + (-B - tmp) / (2.0 * A) * (b - a));
  }
  return res;
}

/*
From here not tested
*/

vector<point> point_circle_tangent(const point &x, int r, const point &a)
{
  LL dist = (a.X - x.X + EPS) * 1LL * (a.X - x.X + EPS) + (a.Y - x.Y + EPS) * 1LL * (a.Y - x.Y + EPS);
  vector<point> res;
  if(dist == 0)
    res.pb(a);
  else if(dist > r * 1LL * r)
  {
    point v = vec(x, a);
    v *= r * 1.0 / sqrt(d);
    double theta = acos(sqrt(d) / r);
    res.pb(x + vec_rot(v, theta));
    res.pb(x + vec_rot(v, -theta));
  }
  return res;
}

vector<point> circle_circle_tangent(const point &a, int r1, const point &b, int r2)
{
  vector<point> res;
  if(r1 == r2)
  {
    point v = normalize(vec(a, b));
    point p1 = point(-x.Y, x.x) * r1;
    point p2 = point(x.Y, -x.x) * r1;
    res.pb(p1 + a);
    res.pb(p2 + a);
    res.pb(p1 + b);
    res.pb(p2 + b);
    return res;
  }
  if(r1 < r2)
  {
    swap(a, b);
    swap(r1, r2);
  }
  double r = r1 - r2;
  res = point_circle_tangent(a, r, b);
  point t1 = res[0], t2 = res[1];
  point p1 = normalize(vec(a, t1));
  point p2 = normalize(vec(a, t2));
  res.pb(p1 * r1 + a);
  res.pb(p2 * r1 + a);
  res.pb(p1 * r2 + b);
  res.pb(p2 * r2 + b);
  return res;
}

double polygon_area(int n)
{
  double res = 0.0;
  for(int i=0;i<n;i++)
    res += cross(arr[i], arr[(i + 1) % n]);
  return fabs(res) / 2;
}

bool isconvex(int n)
{
  bool isccw = ccw(arr[0], arr[1], arr[2]);
  for(int i=1;i<n;i++)
    if(ccw(arr[i], arr[(i + 1) % n], arr[(i + 2) % n]) != isccw)
      return false;
  return true;
}

double crosss(const point &O, const point &A, const point &B)
{
	return (A.X - O.X) * (B.Y - O.Y) - (A.Y - O.Y) * (B.X - O.X);
}

bool sorter(const point &a, const point &b)
{
  if(a.X == b.X) return a.Y < b.Y;
  return a.X < b.X;
}

vector<point> convex_hull(vector<point> &P)
{
	int n = P.size(), k = 0;
	vector<point> H(2*n);
	sort(P.begin(), P.end(), sorter);
	for(int i=0;i<n;i++)
  {
		while(k >= 2 && crosss(H[k-2], H[k-1], P[i]) <= 0)
      k--;
		H[k++] = P[i];
	}
	for(int i=n-2,t=k+1;i>=0;i--)
  {
		while(k >= t && crosss(H[k-2], H[k-1], P[i]) <= 0)
      k--;
		H[k++] = P[i];
	}
	H.resize(k);
	return H;
}

bool point_inside_polygon(const vector<point> &P, const point &pt)
{
  int n = P.size();
  double sum = 0;
  for(int i=0;i<n; i++)
  {
    if(ccw(pt, P[i], P[(i+1) % n]))
      sum+=angle_between_three_points(pt, P[i], P[(i+1) % n]);
    else sum-=angle_between_three_points(pt, P[i], P[(i+1) % n]);
  }
  return fabs(fabs(sum) - 2*PI) < EPS;
}

vector<point> polygon_cut(const vector<point> &v, const point &a, const point &b)
{
  vector<point> res;
  int n = v.size();
  for(int i=0;i<n;i++)
  {
    int j = (i + 1) % n;
    bool in1 = ccw(a, b, v[i]);
    bool in2 = ccw(a, b, v[j]);
    if(in1) res.pb(v[i]);
    if(in1 ^ in2)
    {
      point r;
      line_intersection(a, b, v[i], v[j], r);
      res.pb(r);
    }
  }
  return res;
}

vector<point> polygon_intersection(const vector<point> &p, const vector<point> &q)
{
  vector<point> res = q;
  int n = p.size();
  for(int i=0;i<n;i++)
  {
    int j = (i + 1) % n;
    res = polygon_cut(res, p[i], p[j]);
    if(!res.size())
      return res;
  }
  return res;
}

point get_centroid(int n)
{
  double area = 0.0, tmp;
  point a, b, res = point(0, 0);
  for(int i=0;i<n;i++)
  {
    a = arr[i], b = arr[(i + 1) % n];
    tmp = a.X * b.Y - b.X * a.Y;
    area += tmp;
    res.X += (a.X + b.X) * tmp;
    res.Y += (a.Y + b.Y) * tmp;
  }
  area *= 0.5;
  res.X /= (area * 6);
  res.Y /= (area * 6);
  return res;
}
