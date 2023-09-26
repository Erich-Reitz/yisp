#include <iostream>


#include <getopt.h>

#include "yisp.hpp"

int main(int argc, char *argv[]) {
  int opt;

  while((opt = getopt(argc, argv, "")) != -1) {
    switch(opt) {
    default:
      fprintf(stderr, "Usage: %s [dir...]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  std::string sourceFile;
  if (optind < argc) {
    sourceFile = argv[optind];
  }

  return yisp::runFile(sourceFile);
}
