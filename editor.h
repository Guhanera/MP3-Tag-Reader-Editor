#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>

void animate(char *s);
char *get_input(char *op);
int edit_tag(char *edit_op, char *new_info, char *file_name);

#endif