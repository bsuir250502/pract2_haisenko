#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_VALUES 9

const int fieldSize = NUM_OF_VALUES;
const int stringSize = 30;

typedef struct field_t {
    int cell;
    int probable[NUM_OF_VALUES];
    int probableNum;
    int isBasic;
} field_t;

field_t **importField();
void solvingSudoku(field_t **field);

int main(int argc, char *argv[])
{
    field_t **field;
    field = importField();
    solvingSudoku(field);
    return 0;
}

field_t **importField()
{
    int i, j;
    char tempChar;
    field_t **field;
    FILE *inputFile;
    field = (field_t **) calloc(fieldSize, sizeof(field_t *));
    for (i = 0; i < fieldSize; i++) {
        field[i] = (field_t *) calloc(fieldSize, sizeof(field_t));
    }
    inputFile = fopen("in.sudoku", "r");

    for (i = 0; i < fieldSize; i++) {
        for (j = 0; j < fieldSize; j++) {
            tempChar = getc(inputFile);
            field[i][j].cell = atoi(&tempChar);
            field[i][j].isBasic = 1;
            printf("%d ", field[i][j].cell);            /**/
        }
        tempChar = getc(inputFile);
        if (tempChar != '\n' && !feof(inputFile)) {
            printf("Wrong field.\n");
            exit(1);
        }
        printf("\n");                                   /**/
    }
    return field;
}

void solvingSudoku(field_t **field)
{
    while (1) {
        printf("SOLVING IN PROCESS.\n");
    }
}