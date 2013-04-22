#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_VALUES 9

const int fieldSize = NUM_OF_VALUES;
const int stringSize = 30;

typedef struct field_t {
    int cell;
    int isBasic;
} field_t;

field_t **importField();
void solvingSudoku(field_t **field);
int settingValue(field_t **field, int x, int y);
int checkCellSquare(field_t **field, int x, int y, int number);
int checkCellX(field_t **field, int x, int y, int number);
int checkCellY(field_t **field, int x, int y, int number);
void outputField(field_t **field);

int main(int argc, char *argv[])
{
    field_t **field;
    field = importField();
    outputField(field);
    solvingSudoku(field);
    outputField(field);
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
            if (field[i][j].cell) {
                field[i][j].isBasic = 1;
            }
        }
        tempChar = getc(inputFile);
        if (tempChar != '\n' && !feof(inputFile)) {
            printf("Wrong field.\n");
            exit(1);
        }
    }
    return field;
}

void solvingSudoku(field_t **field)
{
    if (settingValue(field, 0, 0)) {
        printf("No solution\n");
    }
}

int settingValue(field_t **field, int x, int y)
{
    int number, nextX, nextY, isLastCell;
    ((x + 1) == NUM_OF_VALUES) ? (nextX = 0, nextY = y + 1) : (nextX = x + 1, nextY = y);
    (nextY == NUM_OF_VALUES) ? (isLastCell = 1) : (isLastCell = 0);

    if (field[y][x].isBasic) {
        if (isLastCell) {
            return 0;
        } else {
            if (settingValue(field, nextX , nextY)) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    
    for (number = 1; number < (NUM_OF_VALUES + 1); number++) {
        if (checkCellSquare(field, x, y, number)) {
            continue;
        }
        if (checkCellX(field, x, y, number)) {
            continue;
        }
        if (checkCellY(field, x, y, number)) {
            continue;
        }
        field[y][x].cell = number;
        if (isLastCell) {
            return 0;
        } else {
            if (settingValue(field, nextX , nextY)) {
                field[y][x].cell = 0;
                continue;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

int checkCellSquare(field_t **field, int x, int y, int number)
{
    int i, j, endJ, endI;
    endJ = x - (x % 3) + 3;
    endI = y - (y % 3) + 3;

    for (i = endI - 3; i < endI; i++) {
        for (j = endJ - 3; j < endJ; j++) {
            if (number == field[i][j].cell) {
                return 1;
            }
        }
    }
    return 0;
}

int checkCellX(field_t **field, int x, int y, int number)
{
    int i;
    for (i = 0; i < NUM_OF_VALUES; i++) {
        if (i == x) {
            continue;
        }
        if (number == field[y][i].cell) {
            return 1;
        }
    }
    return 0;
}

int checkCellY(field_t **field, int x, int y, int number)
{
    int j;
    for (j = 0; j < NUM_OF_VALUES; j++) {
        if (j == y) {
            continue;
        }
        if (number == field[j][x].cell) {
            return 1;
        }
    }
    return 0;
} 

void outputField(field_t **field)
{
    int i, j;
    printf("\n");
    for (i = 0; i < NUM_OF_VALUES; i++) {
        for (j = 0; j < NUM_OF_VALUES; j++) {
            printf("%d ", field[i][j].cell);
        }
        printf("\n");
    }
}