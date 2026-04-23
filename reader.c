#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"

// Convert Big Endian to Little Endian
unsigned int swap32(unsigned int x)
{
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8) |
           ((x & 0x00FF0000) >> 8) |
           ((x & 0xFF000000) >> 24);
}

void print_tag(struct song_info *ptr, int count)
{
    printf("\n===============================================\n");
    printf("                 SONG DETAILS \n");
    printf("===============================================\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-3d %-9s %s\n", i + 1, ptr[i].tag, ptr[i].tag_info);
    }
    printf("===============================================\n\n");
}

int read_tag(char *file_name, song_info *s)
{

    int tag_count = 0;

    FILE *fp = fopen(file_name, "rb");

    if (!validate_file(fp))
    {
        return 0;
    }

    fseek(fp, 7, SEEK_CUR); // Skip Header and move to song info part

    while (tag_count < 6)
    {
        // Read Tag
        char tag[5];
        fread(tag, 4, 1, fp);
        tag[4] = '\0';
        //  printf("%s\t",tag);

        // Read Size
        unsigned int size;
        fread(&size, 4, 1, fp);
        size = swap32(size); // Stored as Big Endian

        fseek(fp, 2, SEEK_CUR); // Skip FLAG
        fseek(fp, 1, SEEK_CUR); // Skip NULL

        // Read Tag Info
        char info[size];
        fread(info, 1, size - 1, fp);
        info[size - 1] = '\0';
        //  printf("%s\n",info);

        char arr[6][5] = {"TIT2", "TPE1", "TALB", "TCON", "COMM", "TYER"};

        for (int i = 0; i < 6; i++)
        {
            if (strcmp(arr[i], tag) == 0)
            {
                strcpy(s[tag_count].tag, arr[i]);
                s[tag_count].tag_info = (char *)malloc(size + 1);
                strcpy(s[tag_count].tag_info, info);
                tag_count++;
            }
        }
    }

    print_tag(s, tag_count);
    fclose(fp);

    return 1;
}