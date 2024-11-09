#ifndef _BIBENTRY_H
#define _BIBENTRY_H

struct bibentry {
  char label[80];
  int n_fields;
  char **field_labels;
  char **field_values;
  struct bibentry *next;
};

struct bibentry *bib_init();
void bibentry_clear(struct bibentry *self);

#endif