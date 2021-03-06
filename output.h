/***************************************
  $Header$

  Header file shared between generic output code and the backend
  drivers.
  ***************************************/

/* COPYRIGHT */

#ifndef OUTPUT_H
#define OUTPUT_H    /*+ To stop multiple inclusions. +*/

#include "nodes.h"

typedef struct {
  void (*initialise)(void);
  void (*prologue)(void);
  void (*epilogue)(void);
  void (*open_bracket)(BracketType type, int subscript);
  void (*close_bracket)(BracketType type, int subscript);
  void (*set_eols)(int);
  void (*lojban_text)(char *);
  void (*translation)(char *);
  void (*start_tags)(void);
  void (*end_tags)(void);
  void (*start_tag)(void);
  void (*write_tag_text)(char *, char *, char *, int);
  void (*write_partial_tag_text)(char *);

  // For XML output
  void (*lojban_word_and_translation)(char *, char *, char *);
  void (*stop_tag)(void);
  // End for XML output

} DriverVector;

// acutally idle3, .u'i
static void idle2(char * a,char * b, char *c) {
   return;
}

static void idle0() {
   return;
}

#endif /* OUTPUT_H */
