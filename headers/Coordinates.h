#ifndef INCLUDE_HEADERS_COORDINATES_H_
#define INCLUDE_HEADERS_COORDINATES_H_

#include <cmath>

class Coords {
public:
  Coords(int xx, int yy, bool inbounds = true);

  int getx() const;
  void setx(int xx);
  int gety() const;
  void sety(int yy);
  int distance(Coords) const;
  Coords normalize() const;
  Coords abs() const;
  bool isAdjacent(Coords) const;
  Coords inbounds() const;

  Coords operator+(Coords) const;
  Coords operator-(Coords) const;
  Coords operator*(int) const;
  Coords operator=(Coords);
  Coords operator+=(Coords);
  bool operator==(Coords) const;

protected:
  void setWorldDimensions(int w, int h);
  int vecLen() const;
  static int width, height;

private:
  int x, y;
};

#endif // INCLUDE_HEADERS_COORDINATES_H_
