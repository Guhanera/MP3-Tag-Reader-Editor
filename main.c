// MP3 file follows Big endianess

/*
    Title : MP3 Tag reader cum editor
    Name : Guhan Era
    Roll.no : 25036_36
    Start date : 04.01.2026
    End date : 13.01.2026
    Description:
        *   MP3 Tag Reader & Editor is a command-line application written in C that allows users
            to view and modify metadata stored in MP3 files.
        *   It reads ID3 tags from the binary structure of an MP3 file and displays details
            such as title, artist, album, year, genre, and comments.
        *   The program also enables editing specific tag fields without altering the audio data.
        *   This project demonstrates file handling, binary data processing, structures, and command-line
            argument parsing in C.

*/

#include <stdio.h>
#include <string.h>
#include "reader.h"
#include "editor.h"
#include "validation.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("\033[1;31mError: Invalid arguments\033[0m\n");
        printf("\nFor Help Enter: \"./a.out -h\"\n");
        return 0;
    }

    printf("\n═══════════════════════════════════════════\n");
    printf("   🎵  MP3 TAG READER  &  TAG EDITOR  🎵\n");
    printf("═══════════════════════════════════════════\n\n");

    char operation = check_op(argv[1]);

    char *file_name = argv[argc - 1]; // The last element is file_name

    song_info s[6]; // Declare an array of Tags

    switch (operation)
    {
    case 'e':
        if (argc != 5)
        {
            printf("\033[1;31mError: Invalid arguments\033[0m\n");
            printf("\nFor Help Enter: \"./a.out -h\"\n");
            return 0;
        }

        // argv[2] = edit op;
        // argv[3] = new_data;
        // argv[4] = file_name;

        char *edit_op = argv[2];

        char *info = argv[3];

        // Edit operation --> edit_tag(edit_op, info, file_name)
        if (!edit_tag(edit_op, info, file_name))
        {
            return 0;
        }
        remove(file_name);             // Deleted the user provided file
        rename("temp.mp3", file_name); // Rename temp file as user provided file

        break;

    case 'v':
        // Read operation
        if (argc != 3)
        {
            printf("\033[1;31mError: Invalid arguments\033[0m\n");
            printf("\nFor Help Enter: \"./a.out -h\"\n");
            return 0;
        }

        // argv[2] = file_name
        if (!read_tag(file_name, s))
        {
            return 0;
        }

        break;

    case 'h':
        print_help();

        break;

    default:
        printf("\033[1;31mError: Invalid arguments\033[0m\n");
        printf("\nFor Help Enter: \"./a.out -h\"\n");
    }

    return 0;
}