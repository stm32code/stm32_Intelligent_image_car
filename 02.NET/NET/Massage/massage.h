#ifndef _MASSAGE__H_
#define _MASSAGE__H_

#include "stm32f10x_it.h"
#include "string.h"
#include <stdio.h>
#include "git.h"
#define chack_time 6
// ����json����
mySta massage_parse_json(char *message);

#endif
