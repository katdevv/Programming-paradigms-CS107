
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// num defines an enumeration — a custom data type that
// consists of a set of named integer constants.

typedef enum
{
  Integer,
  String,
  List,
  Nil
} nodeType;

/*
By default, these correspond to integer values:

Integer = 0
String  = 1
List    = 2
Nil     = 3
*/

/**
recursively concats all string nodeTypes
*/
char *ConcatAll(nodeType *list);
