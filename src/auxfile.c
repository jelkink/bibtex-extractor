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
  char command[MAX_COMMAND_LENGTH];
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
        // process command
        commandLength = 0;
      }
    }
    else if (commandLength < MAX_COMMAND_LENGTH - 1)
    {
      command[commandLength++] = c;
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

  printf("%d citations detected.\n", countCitations);

  return 0;
}
