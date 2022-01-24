#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// ---

const int BLOCK_SIZE = 512; // block size of jpg file
 
int main(int argc, char *argv[])
{
    // ensure correct usage
    if (argc != 2) // (1st arg = executable, 2nd arg = .raw file)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1; // error exit code
    }

    // open .raw input file provided as argument to executable
    char *raw_filename = argv[1];
    FILE *raw_file = fopen(raw_filename, "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", raw_filename);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE]; // buffer to store jpg, file after file
    char jpg_filename[8]; // pointer for jpg file name with exactly 8 bytes
    int jpg_count = 0; // jpg file count
    FILE *jpg_pointer;  // pointer to write data to jpg file

    // read faw file
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // first 4 bytes of any jpg file: 0xff 0xd8 0xff 0xe[*] (-> 0xe0 - 0xef)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // printf("next jpg! count: %i\n", jpg_count);

            if (jpg_count != 0) // not first jpg file
            {
                // close previous file
                fclose(jpg_pointer);
            }

            // store new jpg_filename with next counter number
            sprintf(jpg_filename, "%03i.jpg", jpg_count);

            // open new jpg file
            jpg_pointer = fopen(jpg_filename, "w");
            if (jpg_pointer == NULL)
            {
                printf("Could not open %s.\n", jpg_filename);
                return 1;
            }

            // prepare jpg count for next iteration
            jpg_count += 1;
        }

        if (jpg_count != 0) // jpg open
        {
            // write data to file
            fwrite(buffer, BLOCK_SIZE, 1, jpg_pointer);
        }
    }

    // free(jpg_filename);
    fclose(jpg_pointer); // close previous file
    fclose(raw_file); // close raw file

    return 0;
}

/*
compile and run: clang -lcs50 ./recover.c -o recover.out && ./recover.out card.raw
delete all jpg files in folder without confirmation: rm -f *.jpg
check: check50 cs50/problems/2022/x/recover
submit: submit50 cs50/problems/2022/x/recover
*/