#include <stdio.h>
#include <string.h>
#include "validation.h"

int validate_file(FILE *fp)
{
    if (fp == NULL)
    {
        fprintf(stderr, "Error: File not found\n");
        return 0;
    }

    char signature[4];
    fread(signature, 3, 1, fp);

    // Check the signature of file matches with ID3. For MP3 files -> Signature is ID3
    if (strcmp(signature, "ID3") != 0)
    {
        printf("Error: Invalid format\n");
        return 0;
    }
    return 1;
}

char check_op(char *op)
{
    if (strcmp(op, "-e") == 0)
    {
        return 'e'; // Editing
    }
    else if (strcmp(op, "-v") == 0)
    {
        return 'v'; // Viewing
    }
    else if (strcmp(op, "-h") == 0)
    {
        return 'h';
    }
    else
    {
        return 'u'; // Unsupprted
    }
}

void print_help()
{
    FILE *fp = fopen("help.txt", "r");
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        fputc(ch, stdout);
    }
    fclose(fp);
}