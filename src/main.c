#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int c;
  char *auxfile;

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
  
  return(0);
}