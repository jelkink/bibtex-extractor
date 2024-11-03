#include "auxfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

struct aux *aux_init(char *auxfile)
{
  char filename[256];
  FILE *input;
  struct aux *auxdata;

  sprintf(filename, "%s.aux", auxfile);

  auxdata = malloc(sizeof(struct aux));

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
        if (strcmp(command, "citation") == 0)
        {
          countCitations++;
        }
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
      fprintf(stderr, "Warning: Command too long, truncating.\n");
      commandLength = 0;
    }
  }

  // EOF reached
  if (commandLength > 0)
  {
    command[commandLength] = '\0';
    // process command
  }

  printf("%d citations detected to be extracted from: %s.bib.\n", countCitations, self->bibfile);

  return 0;
}
