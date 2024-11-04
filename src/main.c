#include "auxfile.h"
#include "bibfile.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int c;
  char *auxfile;
  struct aux *auxdata;
  struct bib *bibdata;

  while ((c = getopt(argc, argv, "")) != -1)
  {
    switch(c)
    {
      default:
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }
  }

  if (optind < argc)
  {
    auxfile = argv[optind];
  } else {
    fprintf(stderr, "Filename required. Usage: %s filename\n", argv[0]);
    return 1;
  }

  auxdata = aux_init();
  bibdata = bib_init();

  aux_scan(auxdata, auxfile);
  bib_scan(bibdata, auxdata);

  aux_clear(auxdata);
  bib_clear(bibdata);
  
  return(0);
}