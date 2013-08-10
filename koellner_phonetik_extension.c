#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
 
#define PHP_MY_EXTENSION_VERSION "1.0"
#define PHP_MY_EXTENSION_EXTNAME "koellner_phonetik_extension"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
 
extern zend_module_entry koellner_phonetik_extension_module_entry;
#define phpext_koellner_phonetik_extension_ptr &koellner_phonetik_extension_module_entry

ZEND_BEGIN_ARG_INFO_EX(arginfo_koellner_phonetik, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(1, raw_output)
ZEND_END_ARG_INFO()
 
// declaration of a custom koellner_phonetik()
PHP_FUNCTION(koellner_phonetik);
 
// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
static function_entry koellner_phonetiks[] = {
    PHP_FE(koellner_phonetik, arginfo_koellner_phonetik)
    {NULL, NULL, NULL}
};
 
// the following code creates an entry for the module and registers it with Zend.
zend_module_entry koellner_phonetik_extension_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MY_EXTENSION_EXTNAME,
    koellner_phonetiks,
    NULL, // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    NULL, // name of the MINFO function or NULL if not applicable
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MY_EXTENSION_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
 
ZEND_GET_MODULE(koellner_phonetik_extension)

/*
Buchstabe	Kontext	Code
A, E, I, J, O, U, Y		0
H		-
B		1
P	nicht vor H
D, T	nicht vor C, S, Z	2
F, V, W		3
P	vor H
G, K, Q		4
C	im Anlaut vor A, H, K, L, O, Q, R, U, X
vor A, H, K, O, Q, U, X außer nach S, Z
X	nicht nach C, K, Q	48
L		5
M, N		6
R		7
S, Z		8
C	nach S, Z
im Anlaut außer vor A, H, K, L, O, Q, R, U, X
nicht vor A, H, K, O, Q, U, X
D, T	vor C, S, Z
X	nach C, K, Q
*/

#define ae ( (char) 228 )
#define ue ( (char) 252 )
#define oe ( (char) 246 )
#define ss ( (char) 223 )


#define AE ( (char) 228 )
#define UE ( (char) 252 )
#define OE ( (char) 246 )

char * soundex_ger(char *s){
  // input: ISO-8859-1

  int len = strlen(s);

  #define a_lowered(c) *(p_lowered++) = (c);
  char *lowered = emalloc(len+2);
  char *p_lowered = lowered;
  char *c;

  // to lower case
  c = s;
  p_lowered = lowered;
  a_lowered('\0'); // add leading 0 so that we can go one char back
  while (*c != '\0'){
    if ((*c >= 'a' && *c <= 'z')){
      a_lowered(*c);
    } else if (*c >= 'A' && *c <= 'Z'){
      a_lowered((*c - ('A' - 'a')));
    } else if (*c == ss) {
      a_lowered('s');
    } else if (*c == ae || *c == oe || *c == ue) {
      a_lowered('a');
    } else if (*c == AE || *c == OE || *c == UE) {
      a_lowered('a');
    } else {
      a_lowered(' ');
    }
    c++;
  }
  a_lowered('\0');

  // printf("%s lowered: %s\n",s, &(lowered[1]));

  char * r = emalloc(len+2);

  #define a_out(c) if (p_out == r || *(p_out-1) != c) *(p_out++) = c;
  char * p_out = &r[0];

  char next;
  char before;

  int i;
  for (i = 1; i <= len; ++i)
  {
    switch (lowered[i]){
      case 'a':
      case 'e':
      case 'i':
      case 'j':
      case 'o':
      case 'u':
      case 'y': if (i == 1) a_out('0');
                break;

      case 'h': break;
      case 'b': a_out('1'); break;
      case 'p':
        if (lowered[i+1] == 'h') {
          a_out('3');
        } else a_out('1');
        break;

      case 'd':
      case 't':
        next = lowered[i+1];
        if (!(next == 'c' || next == 's' || next == 'z')){
          a_out('2');
          break;
        }
        if (next == 'c' || next == 's' || next == 'z'){
          a_out('8');
          break;
        }
      case 'f':
      case 'v':
      case 'w': a_out('3'); break;


      case 'g':
      case 'k':
      case 'q': a_out('4'); break;

      case 's':
      case 'z': a_out('8'); break;


      case 'c':
        next   = lowered[i+1];
        before = lowered[i-1];
        if ( (before == ' ' && (  next == 'a' || next == 'h' || next == 'k' || next == 'l' || next == 'o' || next == 'q' || next == 'r' || next == 'u' || next == 'x'))
          || (before != 's' && before != 'z' && (next == 'a' || next == 'h' || next == 'k' || next == 'o' || next == 'q' || next == 'u' || next == 'x'))
        ){
          a_out('4');
          break;
        }

        if (
            (before == 's' || before == 'z')
         || (before == ' ' && ( next != 'a' && next != 'h' && next != 'k' && next != 'l' && next != 'o' && next != 'q' && next != 'r' && next != 'r' && next != 'r' && next != 'u' && next != 'x'))
         || (next != 'a' && next != 'h' && next != 'k' && next != 'o' && next != 'q' && next != 'q' && next != 'u' && next != 'x')
         ){
          a_out('8');
          break;
        }
      case 'x':
        before = lowered[i-1];
        if (before != 'c' && before != 'k' && before != 'q'){
          a_out('4');
          a_out('8');
          break;
        }

        if (before == 'c' || before == 'k' || before == 'q'){
          a_out('8');
          break;
        }

      case 'l': a_out('5'); break;
      case 'm':
      case 'n': a_out('6'); break;
      case 'r': a_out('7'); break;
        break;
    }
  }

  efree(lowered);
  a_out('\0');
  return r;
}

// implementation of a custom koellner_phonetik()
PHP_FUNCTION(koellner_phonetik)
{
    char *arg;
    int arg_len;
    zend_bool raw_output = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &arg, &arg_len, &raw_output) == FAILURE) {
            return;
    }
    char *ret = soundex_ger(arg);
    RETVAL_STRING(ret, 0);
}
