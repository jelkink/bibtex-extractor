#include "auxfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ENTRIES 1024

struct aux *aux_init(char *auxfile)
{
  char filename[256];
  FILE *input;
  struct aux *auxdata;

  sprintf(filename, "%s.aux", auxfile);

  auxdata = malloc(sizeof(struct aux));
  auxdata->entries = malloc(sizeof(char *) * MAX_ENTRIES);

  input = fopen(filename, "r");

  if (input == NULL)
  {
    fprintf(stderr, "Error opening file %s!", filename);
  }
  else
  {
    aux_scan(auxdata, input);
    fclose(input);
  }

  return auxdata;
}

void aux_clear(struct aux *self)
{
  free(self->entries);
  free(self);
}

int aux_scan(struct aux *self, FILE *input)
{
  int countCitations = 0;
  int commandLength = 0;
  int incommand = 0;
  char command[MAX_COMMAND_LENGTH];
  char parameter[MAX_COMMAND_LENGTH];
  char c;

  while ((c = fgetc(input)) != EOF) {
    if (c == '\\' || c == '{')
    {
      if (commandLength > 0)
      {
        command[commandLength] = '\0';
        printf("Command detected: %s\n", command);
      }

      commandLength = 0;
      incommand = c == '\\';
    }
    else if (c == '}')
    {
      parameter[commandLength] = '\0';
      printf("Parameter detected: %s\n", parameter);

      if (strcmp(command, "bibdata") == 0)
      {
        strcpy(self->bibfile, parameter);
      }

      if (strcmp(command, "citation") == 0)
      {
        if (countCitations < MAX_ENTRIES)
        {
          self->entries[countCitations] = malloc(sizeof(char) * strlen(parameter));
          strcpy(self->entries[countCitations], parameter);
        }

        countCitations++;
      }

      commandLength = 0;
    }
    else if (commandLength < MAX_COMMAND_LENGTH - 1)
    {
      if (incommand)
        command[commandLength++] = c;
      else
        parameter[commandLength++] = c;
    }
    else
    {
      fprintf(stderr, "Warning: Command or parameter too long, truncating.\n");
      commandLength = 0;
    }
  }

  if (countCitations > MAX_ENTRIES)
    fprintf(stderr, "Warning: found more citations than can be managed. Recorded only the first %d.\n", MAX_ENTRIES);

  // We do not worry about a command that ends at the end of the
  // file, because if it was a bibliography entry, we would have
  // reached a closing curly bracket first.

  printf("%d citations detected to be extracted from: %s.bib.\n", countCitations, self->bibfile);

  for (int i = 0; i < countCitations; i++) 
    printf("Found: %s\n", self->entries[i]);

  return 0;
}
