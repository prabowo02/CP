double dist3d(double lat1, double lon1, double lat2, double lon2){
  double dlat = lat2 - lat1;
  double dlon = lon2 - lon1;
  double a = pow(sin(dlat/2),2) + cos(lat1) * cos(lat2)* pow(sin(dlon/2),2);
  return (R*2*atan2(sqrt(a), sqrt(1-a)));
}

int extended_euclid(int a, int b, int & x, int & y) {
  if (a == 0) { x = 0; y = 1; return b; }
  int x1, y1;
  int d = extended_euclid(b%a, a, x1, y1);
  x = y1 - (b / a) * x1; y = x1;
  return d;
}
