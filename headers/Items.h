#ifndef INCLUDE_HEADERS_ITEMS_H_
#define INCLUDE_HEADERS_ITEMS_H_

#include "SimComponents.h"

#define ITEM_PANDORA 0
#define ITEM_TESOURO 1
#define ITEM_JAULA 2
#define ITEM_MINA 3
#define ITEM_SURPRESA 4

class ItemPandora : public Item {
public:
  virtual void collect(User &, vector<Caravana>::iterator &,
                       vector<Caravana> &);
};
class ItemTesouro : public Item {
public:
  virtual void collect(User &, vector<Caravana>::iterator &,
                       vector<Caravana> &);
};
class ItemJaula : public Item {
public:
  virtual void collect(User &, vector<Caravana>::iterator &,
                       vector<Caravana> &);
};
class ItemMina : public Item {
public:
  virtual void collect(User &, vector<Caravana>::iterator &,
                       vector<Caravana> &);
};
class ItemSurpresa : public Item {
public:
  virtual void collect(User &, vector<Caravana>::iterator &,
                       vector<Caravana> &);
};

#endif // INCLUDE_HEADERS_ITEMS_H_
