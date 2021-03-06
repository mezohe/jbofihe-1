/***************************************
  Driver for producing XML output from the glosser.
  ***************************************/

/* COPYRIGHT danr 2014 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "output.h"

static char tag_stack[100][100];
static int  tag_head[100];
static char tag_top;
static char last_tag_top;

int ref;
int first;

static void
initialise(void)
{
  ref = 1;
  first = 0;
  tag_top = 0;
  last_tag_top = 0;
}


static void
write_prologue(void) { }

static void
write_epilog(void) { }

static void
clear_eols(void) { }

static void
set_eols(int eols) { }

static void
write_open_bracket(BracketType type, int subscript) { }

static void
write_close_bracket(BracketType type, int subscript) { }

/*++++++++++++++++++++++++++++++
  Make a string safe for setting with HTML.

  static char * escape

  char *s
  ++++++++++++++++++++++++++++++*/

char* escape(char *s)
{
  char *buf;
  buf = alloca(sizeof(char)*2048);
  char *p, *q;
  p = s;
  q = buf;
  while (*p) {
    switch (*p) {
      case '&':
        strcpy(q, "&amp;");
        q += 5;
        p++;
        break;
      case '<':
        strcpy(q, "&lt;");
        q += 4;
        p++;
        break;
      case '>':
        strcpy(q, "&gt;");
        q += 4;
        p++;
        break;
      default:
        *q++ = *p++;
        break;
    }
  }
  *q = 0;

  return buf;
}

void rm_quote (char *s) {
    char *p;
    p = s;
    while (*s) {
        if (*s != '"') {
            *p++ = *s++;
        } else {
            *p++ = '\'';
            s++;
        }
    }
    *p = '\0';
}

static void
write_lojban_text(char *text) { }

static void
write_special(char *text) {
  //printf("<special val=\"%s\"/>\n",text);
}


static void
write_translation(char *text) {
  //printf("<translation val=\"%s\"/>\n",text);
}

static void
start_tags(void)
{
}

static void
end_tags(void) { }

static void
start_tag(void) { }

static void
write_tag_text(char *brivla, char *place, char *trans, int brac)
{
  rm_quote(brivla);
  rm_quote(place);
  rm_quote(trans);
  printf("{\"type\":\"argbegin\",\"selbri\":\"%s\",\"place\":\"%s\",\"selbriplace\":\"%s\"}\n",brivla,place,trans);
}

static void
write_stop_tag() {
  printf("{\"type\":\"argend\"}\n");
}

static void write_partial_tag_text(char *t) {

  // printf("<partial_tag_text value=\"%s\"/>\n",escape(t));
}

static void write_lojban_word_and_translation(char *loj, char *eng, char *selmaho) {
  int i;
  char *p = loj;
  int info = strcmp(loj, eng);

  rm_quote(eng);
  if (info) {
    printf("{\"type\":\"info\",\"info\":\"%s\"}\n",eng);
  }

  for (p = loj; *p; ++p) {
    if (*p != '{' && *p != '[' && *p != '"') {
      putchar(*p);
    }
  }
  putchar('\n');

  // if (info) {
  //   printf("{\"type\":\"infoend\"}\n");
  // }

  /*
  rm_quote(eng);

  printf("<word ref=\"%d\" pos=\"%s\"",ref,escape(selmaho));
  printf(" trans=\"%s\"",escape(eng));

  if(first) {
    printf(" tags=\"");
    first = 0;
  } else {
    if(tag_head[last_tag_top] != 0) {
      printf(" dephead=\"%d\"",tag_head[last_tag_top]);
    }
    printf(" deprel=\"");
  }

  for (i=tag_top-1; i>=last_tag_top; i--) {
    printf("%s",escape(tag_stack[i]));
    if (i != last_tag_top) {
      printf("|");
    }
  }

  printf("\"");

  printf(">%s</word>\n",escape(loj));
  ref++;
  */
}

DriverVector xml_driver =
{
  initialise,
  write_prologue,
  write_epilog,
  write_open_bracket,
  write_close_bracket,
  set_eols,
  write_lojban_text,
  write_translation,
  start_tags,
  end_tags,
  start_tag,
  write_tag_text,
  write_partial_tag_text,
  write_lojban_word_and_translation,
  write_stop_tag,
};
