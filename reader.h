#ifndef READER_H
#define READER_H


// Structure to store Tag Data
typedef struct song_info
{
    char tag[10];
    char *tag_info;
} song_info;

unsigned int swap32(unsigned int x);
int validate_file(FILE *fp);
void print_tag(song_info *ptr, int count);
int read_tag(char *file_name, song_info *s);

#endif