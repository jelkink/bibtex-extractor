# Introduction

*bibextractor* is a utility, written in C, to use the AUX file produced when compiling a Latex document to extract only those references from the bibliography file that are actually used, and save them to a separate bibtex file. This is useful when submitting the bibtex file to a publisher, so that not all entries need to be submitted, only those used.

# Usage

bibextractor filename

Note that the filename should not include the .aux extension. The AUX file itself will contain the reference to the bibliography file.