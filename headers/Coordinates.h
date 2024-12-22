#ifndef INCLUDE_HEADERS_COORDINATES_H_
#define INCLUDE_HEADERS_COORDINATES_H_

#include <cmath>

class Coords {
public:
  Coords(int xx, int yy);

  int getx() const;
  void setx(int xx);
  int gety() const;
  void sety(int yy);
  int distance(Coords) const;
  Coords normalize() const;

  Coords operator+(Coords) const;
  Coords operator-(Coords) const;
  Coords operator=(Coords);
  bool operator==(Coords) const;

private:
  int x, y;
};

#endif // INCLUDE_HEADERS_COORDINATES_H_
