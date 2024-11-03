#ifndef _AUXFILE_H
#define _AUXFILE_H

#include <stdio.h>

struct aux {
  char bibfile[30];
  char **entries;
};

struct aux *aux_init(char *auxfile);
void aux_clear(struct aux *self);

int aux_scan(struct aux *self, FILE *input);

#endif