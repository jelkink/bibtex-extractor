#include "bibfile.h"
#include "auxfile.h"
#include <stdlib.h>
#include <stdio.h>

struct bib *bib_init()
{
  struct bib *self;

  self = malloc(sizeof(struct bib));

  self->root = NULL;

  return self;
}

void bib_clear(struct bib *self)
{
  free(self);
}

int bib_scan(struct bib *self, struct aux *auxdata)
{
  printf("Scanning BIB file...\n");

  return 0;
}