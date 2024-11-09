#include "bibentry.h"
#include <stdlib.h>

#define MAX_FIELDS 20

struct bibentry *bib_init()
{
  struct bibentry *self;

  self = malloc(sizeof(struct bibentry));

  self->n_fields = 0;
  self->field_labels = malloc(sizeof(char *) * MAX_FIELDS);
  self->field_values = malloc(sizeof(char *) * MAX_FIELDS);
  self->next = NULL;

  return self;
}

void bibentry_clear(struct bibentry *self)
{
  int i;

  for (i = 0; i < self->n_fields; i++)
  {
    free(self->field_labels[i]);
    free(self->field_values[i]);
  }

  free(self->field_labels);
  free(self->field_values);

  if (self->next)
    bibentry_clear(self->next);

  free(self);
}