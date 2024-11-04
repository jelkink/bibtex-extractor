#ifndef _BIBFILE_H
#define _BIBFILE_H

#include "auxfile.h"


struct bibentry {
  char label[80];
  int n_items;
  char **item_labels;
  char **item_values;
};

struct bib {
  int n_entries;
  struct bibentry *entries;
  struct bib *next;
};

struct bib *bib_init();
void bib_clear(struct bib *self);

int bib_scan(struct bib *self, struct aux *auxdata);

#endif