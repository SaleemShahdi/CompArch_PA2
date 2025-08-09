#include <stdio.h>
#include <stdlib.h>

void multiply(double ** matrix1, double ** matrix2, double ** result, double rows, 
              double columns, double columnelements) {
    for (int i = 0; i <= rows - 1; i++){
        for (int j = 0; j <= columns - 1; j++){
            double sum = 0.0;
            for (int c = 0; c <= columnelements - 1; c++) {
                sum = sum + (matrix1[i][c] * matrix2[c][j]);
            }
            result[i][j] = sum;
        }
    }
    return;
}

void transpose(double ** matrix, double ** transposed, double rows, double columns) {
    for (int i = 0; i <= rows -1; i++) {
        for (int j = 0; j <= columns - 1; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return;

}

void invert(double ** matrix, double ** identity, double rows) {
    for (int p = 0; p <= rows - 1; p++) {
        double f = matrix[p][p];
        for (int x = 0; x <= rows - 1; x++) {
            matrix[p][x] = matrix[p][x] / f;
            identity[p][x] = identity[p][x] / f;
        }
        for (int i = p + 1; i <= rows - 1; i++) {
            f = matrix[i][p];
            for (int x = 0; x <= rows - 1; x++) {
                matrix[i][x] = matrix[i][x] - (matrix[p][x] * f);
                identity[i][x] = identity[i][x] - (identity[p][x] * f);
            }
        }
    }
    for (int p = rows - 1; p >= 0; p--) {
        for (int i = p - 1; i >= 0; i--) {
            double f = matrix[i][p];
            for (int x = 0; x <= rows - 1; x++) {
                matrix[i][x] = matrix[i][x] - (matrix[p][x] * f);
                identity[i][x] = identity[i][x] - (identity[p][x] * f);
            }
        }
    }
    return;
}

int main(int argc, char ** argv) {
    FILE * stream = fopen(argv[1], "r");
    double attributes;
    double rows;
    char irrelevant [6];
    fscanf(stream, "%s", irrelevant); // ask, would this need to be saved in pointer to char *, not just char *?
    fscanf(stream, "%lf", &attributes);
    fscanf(stream, "%lf", &rows);
    double ** X = malloc((rows) * sizeof(double *));
    for (int i = 0; i <= rows - 1; i ++) {
        X[i] = malloc((attributes+1) * sizeof(double));
    }
    double ** Y = malloc(rows * sizeof(double *));
    for (int i = 0; i <= rows - 1; i++) {
        Y[i] = malloc(1 * sizeof(double));
    }
    for (int i = 0; i <= rows - 1; i++) {
        X[i][0] = 1;
    }
    for (int i = 0; i <= rows - 1; i++) {
        for (int j = 1; j <= attributes+1; j++) {
            if (j == attributes+1) {
                fscanf(stream, "%lf", &(Y[i][0]));
            } else {
                fscanf(stream, "%lf", &(X[i][j]));
            }
        }
    }
    fclose(stream);
    /*
    for (int i = 0; i <= rows - 1; i ++) {
        for (int j = 0; j <= attributes; j++) {
            if (j == attributes) {
                printf("%lf\n", X[i][j]);
            } else {
                printf("%lf ", X[i][j]);
            }
        }
    }
    printf("\n");
    */
    /*
    for (int i = 0; i <= rows - 1; i++) {
        printf("%lf\n", Y[i][0]);
    }
    printf("\n");
    */
    double transposerows = attributes + 1;
    double transposecolumns = rows;
    double ** transposex = malloc(transposerows * sizeof(double *));
    for (int i = 0; i <= transposerows - 1; i++) {
        transposex[i] = malloc(transposecolumns * sizeof(double));
    }
    transpose(X, transposex, rows, attributes + 1);
    /*
    for (int i = 0; i <= transposerows - 1; i++) {
        for (int j = 0; j <= transposecolumns - 1; j++) {
            if (j == transposecolumns - 1) {
                printf("%lf\n", transposex[i][j]);
            } else {
                printf("%lf ", transposex[i][j]);
            }
        }
    }
    printf("\n");
    */
    double productrows = transposerows;
    double productcolumns = attributes+1;
    double productelements = transposecolumns;
    double ** product = malloc(productrows * sizeof(double *));
    for (int i = 0; i <= productrows - 1; i++) {
        product[i] = malloc(productcolumns * sizeof(double));
    }
    multiply(transposex, X, product, productrows, productcolumns, productelements);
    /*
    for (int i = 0; i <= productrows - 1; i++) {
        for (int j = 0; j <= productcolumns - 1; j++) {
            if (j == productcolumns-1) {
                printf("%lf\n", product[i][j]);
            } else {
                printf("%lf ", product[i][j]);
            }
        }
    }
    printf("\n");
    */
    double ** inverse = malloc(productrows * sizeof(double*));
    for (int i = 0; i <= productrows - 1; i++) {
        inverse[i] = malloc(productrows * sizeof(double));
    }
    for (int i = 0; i <= productrows - 1; i++) {
        for (int j = 0; j <= productrows - 1; j++) {
            if (i == j) {
                inverse[i][j] = 1;
            } else {
                inverse[i][j] = 0;
            }
        }
    }
    invert(product, inverse, productrows);
    /*
    for (int i = 0; i <= productrows - 1; i++) {
        for (int j = 0; j <= productcolumns - 1; j++) {
            if (j == productcolumns-1) {
                printf("%lf\n", inverse[i][j]);
            } else {
                printf("%lf ", inverse[i][j]);
            }

        }
    }
    printf("\n");
    */
    double product2rows = productrows;
    double product2columns = transposecolumns;
    double product2elements = productcolumns;
    double ** product2 = malloc(product2rows * sizeof(double *));
    for (int i = 0; i <= product2rows - 1; i++) {
        product2[i] = malloc(product2columns * sizeof(double));
    }
    multiply(inverse, transposex, product2, product2rows, product2columns, product2elements);
    /*
    for (int i = 0; i <= product2rows - 1; i++) {
        for (int j = 0; j <= product2columns - 1; j++) {
            if (j == product2columns - 1) {
                printf("%lf\n", product2[i][j]);
            } else {
                printf("%lf ", product2[i][j]);
            }
        }
    }
    printf("\n");
    */
    double product3rows = product2rows;
    double product3columns = 1;
    double product3elements = product2columns;
    double ** product3 = malloc(product3rows * sizeof(double *));
    for (int i = 0; i <= product3rows - 1; i++) {
        product3[i] = malloc(product3columns * sizeof(double));
    }
    multiply(product2, Y, product3, product3rows, product3columns, product3elements);
    /*
    for (int i = 0; i <= product3rows - 1; i++) {
        for (int j = 0; j <= product3columns - 1; j++) {
            printf("%lf\n", product3[i][j]);
        }
    }
    printf("\n");
    */

    stream = NULL;
    double datarows;
    double dataattributes;
    stream = fopen(argv[2], "r");
    char irrelevant2 [5];
    fscanf(stream, "%s", irrelevant2);
    fscanf(stream, "%lf", &dataattributes);
    fscanf(stream, "%lf", &datarows);
    /*printf("%lf\n", attributes);
    printf("%lf\n", rows);*/

    double ** data = malloc(datarows * sizeof(double *));
    for (int i = 0; i <= datarows - 1; i++) {
        data[i] = malloc((dataattributes+1) * sizeof(double));
    }
    for (int i = 0; i <= datarows - 1; i++) {
        for (int j = 0; j <= dataattributes - 1; j++) {
            fscanf(stream, "%lf", &(data[i][j+1]));
        }
    }
    fclose(stream);
    for (int i = 0; i <= datarows - 1; i++) {
        data[i][0] = 1;
    }
    /*
    for (int i = 0; i <= datarows - 1; i++) {
        for (int j = 0; j <= dataattributes; j++) {
            if (j == attributes) {
                printf("%lf\n", data[i][j]);
            } else {
                printf("%lf ", data[i][j]);
            }
        }
    }
    printf("\n");
    */
    double resultrows = datarows;
    double resultcolumns = product3columns;
    double resultelements = dataattributes+1;
    /*printf("result rows: %lf\n", resultrows);
    printf("result columns: %lf\n", resultcolumns);
    printf("data rows: %lf\n", datarows);
    printf("data columns: %lf\n", dataattributes+1);
    printf("product3 rows: %lf\n", product3rows);
    printf("product3 columns: %lf\n", product3columns);*/
    
    double ** result = malloc(resultrows * sizeof(double *));
    for (int i = 0; i <= resultrows - 1; i++) {
        result[i] = malloc(resultcolumns * sizeof(double));
    }
    multiply(data, product3, result, resultrows, resultcolumns, resultelements);
    for (int i = 0; i <= resultrows - 1; i++) {
        for (int j = 0; j <= resultcolumns - 1; j++) {
            printf("%.0lf\n", result[i][j]);
        }
    }
    for (int i = 0; i <= rows - 1; i++) {
        free(X[i]);
        free(Y[i]);
    }
    free(X);
    free(Y);
    for (int i = 0; i <= transposerows - 1; i++) {
        free(transposex[i]);
    }
    free(transposex);
    for (int i = 0; i <= productrows - 1; i++) {
        free(product[i]);
        free(inverse[i]);
    }
    free(product);
    free(inverse);
    for (int i = 0; i <= product2rows - 1; i++) {
        free(product2[i]);
    }
    free(product2);
    for (int i = 0; i <= product3rows - 1; i++) {
        free(product3[i]);
    }
    free(product3);
    for (int i = 0; i <= datarows - 1; i++) {
        free(data[i]);
    }
    free(data);
    for (int i = 0; i <= resultrows - 1; i++) {
        free(result[i]);
    }
    free(result);



    return 0;
    

}