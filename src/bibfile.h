#ifndef _BIBFILE_H
#define _BIBFILE_H

#include "auxfile.h"
#include "bibentry.h"

struct bib {
  struct bibentry *root;
};

struct bib *bib_init();
void bib_clear(struct bib *self);

int bib_scan(struct bib *self, struct aux *auxdata);

#endif