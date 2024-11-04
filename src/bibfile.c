#include "bibfile.h"
#include "auxfile.h"
#include <stdlib.h>
#include <stdio.h>

#define BLOCK_SIZE 50

struct bib *bib_init()
{
  struct bib *self;

  self = malloc(sizeof(struct bib));

  self->n_entries = 0;
  self->entries = malloc(sizeof(struct bibentry) * BLOCK_SIZE);
  self->next = NULL;

  return self;
}

void bib_clear(struct bib *self)
{
  free(self->entries);
  free(self);
}

int bib_scan(struct bib *self, struct aux *auxdata)
{
  printf("Scanning BIB file...\n");

  return 0;
}