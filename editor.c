#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "reader.h"

void animate(char *s)
{
    int ash = 0;
    int space = 10;
    int num = 0;

    while (ash <= 10)
    {
        printf("\r\t%s [", s);
        for (int i = 0; i < ash; i++)
        {
            printf("#");
        }
        for (int i = 0; i < space; i++)
        {
            printf("-");
        }
        printf("]\t%d %%", num);

        num += 10;
        fflush(stdout);
        ash++;
        space--;
        if (num <= 70)
        {
            usleep(50 * 1000);
        }
        else
        {
            usleep(800 * 1000);
        }
    }
}

// Check for edit operation type and return TAG need to be edited
char *get_input(char *op)
{
    static char option[5];
    if (strcmp(op, "-t") == 0)
    {
        strcpy(option, "TIT2");
    }
    else if (strcmp(op, "-a") == 0)
    {
        strcpy(option, "TPE1");
    }
    else if (strcmp(op, "-A") == 0)
    {
        strcpy(option, "TALB");
    }
    else if (strcmp(op, "-y") == 0)
    {
        strcpy(option, "TYER");
    }
    else if (strcmp(op, "-g") == 0)
    {
        strcpy(option, "TCON");
    }
    else if (strcmp(op, "-c") == 0)
    {
        strcpy(option, "COMM");
    }
    else
    {
        return NULL;
    }

    option[4] = '\0';
    return option;
}

int edit_tag(char *edit_op, char *new_info, char *file_name)
{
    // Validate the file
    FILE *fp = fopen(file_name, "rb");
    if (!validate_file(fp))
    {
        return 0;
    }
    fseek(fp, 0, SEEK_SET);

    // Get the TAG to be edited
    char *target_tag = get_input(edit_op);
    if (target_tag == NULL)
    {
        printf("\033[1;31mError: Invalid arguments\033[0m\n");
        printf("\nFor Help Enter: \"./a.out -h\"\n");
        return 0;
    }

    FILE *temp = fopen("temp.mp3", "wb"); // Create a temp file to copy

    // Copy the header
    char header[10];
    fread(header, 10, 1, fp);
    fwrite(header, 10, 1, temp);

    while (1)
    {
        // Read Tag
        char tag[5];
        fread(tag, 4, 1, fp);
        tag[4] = '\0';
        // printf("%s",tag);

        // Read Size
        unsigned int size;
        fread(&size, 4, 1, fp);
        size = swap32(size); // Stored as Big Endian

        // Read Flag
        char flag[3];
        fread(flag, 3, 1, fp);

        // Read Tag Info
        char info[size];
        fread(info, 1, size - 1, fp);
        info[size - 1] = '\0';
        //  printf("%s\n",info);

        // If TAG matches modify the tag, else copy the data
        if (strcmp(tag, target_tag) == 0)
        {
            fwrite(target_tag, 4, 1, temp);
            unsigned int len = strlen(new_info);
            unsigned int size = swap32(len + 1);
            fwrite(&size, 4, 1, temp);
            fwrite(flag, 3, 1, temp);
            fwrite(new_info, len, 1, temp);
            break;
        }
        else
        {
            fwrite(tag, 4, 1, temp); // Write tag to temp file
            unsigned int temp_size = swap32(size);
            fwrite(&temp_size, 4, 1, temp);
            fwrite(flag, 3, 1, temp);
            fwrite(info, size - 1, 1, temp);
        }
    }

    // Copy remaining data
    char buf[100000];
    int size;
    while ((size = fread(buf, 1, 100000, fp)) != 0)
    {
        fwrite(buf, 1, size, temp);
    }

    fclose(fp);
    fclose(temp);

    animate("Editing");
    printf("\r------------------------------------------------------\n");
    printf("            EDITED SUCCESSFULLY\n");
    printf("------------------------------------------------------\n");

    return 1;
}