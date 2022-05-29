#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
    printf("Error, this program requires 3 arguments!\n");
    printf("%s [source file] [target file]\n", argv[0]);
    return 1;
    }

    FILE *fileSrc, *fileDst;
    size_t i, read_ret;

    fileSrc = fopen(argv[1], "r");
    if (!fileSrc){
        perror("err fileSrc");
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    fileDst = fopen(argv[2], "w");
    if (!fileDst){
        perror("err fileDst");
        puts("Cannot create temp.txt");
        fclose(fileSrc);
        return 1;
    }

    do {
        unsigned char buffer[4096];

        read_ret = fread(buffer, 1, sizeof(buffer), fileSrc);
        for (i = 0; i < read_ret; i++)
            buffer[i] += 100;

        fwrite(buffer, 1, read_ret, fileDst);
    } while (read_ret > 0);

    fclose(fileSrc);
    fclose(fileDst);
    printf("File %s is encrypted into temp.txt!\n", argv[2]);

    return 0;
}
