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
int checkingPossibleCells(field_t **field);
void checkCellSquare(field_t **field, int x, int y, int *probableNum);
void checkCellX(field_t **field, int x, int y, int *probableNum);
void checkCellY(field_t **field, int x, int y, int *probableNum);
void settingCells(field_t **field);
void showField(field_t **field);

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
            if (field[i][j].cell) {
                field[i][j].isBasic = 1;
            }
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
    while (checkingPossibleCells(field)) {
        settingCells(field);
    }
    settingCells(field);
    showField(field);
}

int checkingPossibleCells(field_t **field)
{
    int i, j, k, probableNum[NUM_OF_VALUES], returnNumber = 0;
    printf("\n");
    for (i = 0; i < NUM_OF_VALUES; i++) {
        for (j = 0; j < NUM_OF_VALUES; j++) {
            if (!field[i][j].isBasic) {
                field[i][j].probableNum = 0;
                checkCellSquare(field, i, j, probableNum);
                checkCellX(field, i, j, probableNum);
                checkCellY(field, i, j, probableNum);
                for (k = 0; k < NUM_OF_VALUES; k++) {
                    if (probableNum[k]) {
                        field[i][j].probable[field[i][j].probableNum] = k + 1;
                        field[i][j].probableNum++;
                    }
                }
                if (field[i][j].probableNum > 1) {
                    returnNumber = 1;
                }
            }
            printf("%d ", field[i][j].probableNum);
        }
        printf("\n");
    }
    return returnNumber;
}

void checkCellSquare(field_t **field, int x, int y, int *probableNum)
{
    int i, j, startX, startY, number;
    startX = x - (x % 3);
    startY = y - (y % 3);
    for (number = 1; number <= NUM_OF_VALUES; number++) {
        for (i = startX; i < (startX + 3); i++) {
            for (j = startY; j < (startY + 3); j++) {
                if (number == field[i][j].cell) {
                    i = startX + 3;
                    break;
                }
            }
        }

        if (j == (startY + 3) && i == (startX + 3)) {
            probableNum[number - 1] = 1;
        } else {
            probableNum[number - 1] = 0;
        }
    }
}

void checkCellX(field_t **field, int x, int y, int *probableNum)
{
    int i, number;
    for (number = 1; number <= NUM_OF_VALUES; number++) {
        for (i = 0; i < NUM_OF_VALUES; i++) {
            if (i == x) {
                continue;
            }
            if (number == field[i][y].cell) {
                break;
            }
        }

        if (i == NUM_OF_VALUES && probableNum[number - 1]) {
            probableNum[number - 1] = 1;
        } else {
            probableNum[number - 1] = 0;
        }
    }
}

void checkCellY(field_t **field, int x, int y, int *probableNum)
{
    int j, number;
    for (number = 1; number <= NUM_OF_VALUES; number++) {
        if (!probableNum[number - 1]) {
            continue;
        }
        for (j = 0; j < NUM_OF_VALUES; j++) {
            if (j == y) {
                continue;
            }
            if (number == field[x][j].cell) {
                break;
            }
        }

        if (j == NUM_OF_VALUES && probableNum[number - 1]) {
            probableNum[number - 1] = 1;
        } else {
            probableNum[number - 1] = 0;
        }
    }
} 

void settingCells(field_t **field)
{
    int i, j;
    for (i = 0; i < NUM_OF_VALUES; i++) {
        for (j = 0; j < NUM_OF_VALUES; j++) {
            if (field[i][j].probableNum == 1) {
                field[i][j].cell = field[i][j].probable[0];
                field[i][j].probableNum--;
            }
        }
    }
}

void showField(field_t **field)
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