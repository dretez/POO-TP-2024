#ifndef INCLUDE_HEADERS_ITEMS_H_
#define INCLUDE_HEADERS_ITEMS_H_

#include "SimComponents.h"

class ItemPandora : public Item {
  virtual void collected(User &, Caravana &);
};
class ItemTesouro : public Item {
  virtual void collected(User &, Caravana &);
};
class ItemJaula : public Item {
  virtual void collected(User &, Caravana &);
};
class ItemMina : public Item {
  virtual void collected(User &, Caravana &);
};
class ItemSurpresa : public Item {
  virtual void collected(User &, Caravana &);
};

#endif // INCLUDE_HEADERS_ITEMS_H_
