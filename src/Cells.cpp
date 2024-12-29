#include "../headers/MapCells.h"
#include <memory>

/************************************ CELL ************************************/

Cell::Cell(Coords p) : pos(p) {}

bool Cell::isValid() const { return !hasCaravana(); }

bool Cell::hasCaravana() const { return !!car.lock(); }
void Cell::setCaravana(shared_ptr<Caravana> &c) { car = c; }
void Cell::unsetCaravana() { car.reset(); }
shared_ptr<Caravana> Cell::getCaravana() const { return car.lock(); }

bool Cell::hasItem() const { return !!item.lock(); }
void Cell::setItem(shared_ptr<Item> &i) { item = i; }
void Cell::unsetItem() { item.reset(); }
shared_ptr<Item> Cell::getItem() const { return item.lock(); }

bool Cell::getStorm() const { return storm; }

/******************************* DERIVED CELLS *******************************/

DesertCell::DesertCell(Coords p) : Cell(p) {}
CityCell::CityCell(Coords p) : Cell(p) {}
MountainCell::MountainCell(Coords p) : Cell(p) {}

bool DesertCell::isValid() const { return !hasCaravana(); }
bool CityCell::isValid() const { return true; }
bool MountainCell::isValid() const { return false; }
