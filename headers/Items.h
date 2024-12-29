#ifndef INCLUDE_HEADERS_ITEMS_H_
#define INCLUDE_HEADERS_ITEMS_H_

#include <memory>
#include <vector>

#include "Coordinates.h"

class User;
class Caravana;

#define ITEM_COUNT 5

class Item {
public:
  Item(Coords xy, int tv = 20);

  Coords getPos();
  void decrTempoVida();
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);

private:
  int tempovida;
  Coords pos;
};

class RandItemGenerator {
public:
  static void gen(vector<shared_ptr<Item>> &, Coords xy, int tv);
};

class ItemPandora : public Item {
public:
  ItemPandora(Coords xy, int tv);
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);
};
class ItemTesouro : public Item {
public:
  ItemTesouro(Coords xy, int tv);
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);
};
class ItemJaula : public Item {
public:
  ItemJaula(Coords xy, int tv);
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);
};
class ItemMina : public Item {
public:
  ItemMina(Coords xy, int tv);
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);
};
class ItemSurpresa : public Item {
public:
  ItemSurpresa(Coords xy, int tv);
  virtual void collect(User &, vector<shared_ptr<Caravana>>::iterator &,
                       vector<shared_ptr<Caravana>> &);
};

#endif // INCLUDE_HEADERS_ITEMS_H_
