#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "imageprocessing.h"
#define PATHSZ 100
typedef struct size {
    int N;
    int M;
} size;
void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}
int main() {
    int ****index = NULL;
    size *marimi = malloc(sizeof(size));
    int in = 0;
    float ***indexF = NULL;
    int inF = 0;
    int *marimiF = NULL;
    while (1) {
        char input[2];
        scanf("%s", input);
        if (strcmp(input, "e") == 0) {
            for (int ind = 0; ind < in; ++ind) {
                for (int i = 0; i < marimi[ind].N; ++i) {
                    for (int j = 0; j < marimi[ind].M; ++j) {
                        free(index[ind][i][j]);
                    }
                    free(index[ind][i]);
                }
                free(index[ind]);
            }
            free(index);
            free(marimi);
            for (int ind = 0; ind < inF; ++ind) {
                for (int i = 0; i < marimiF[ind]; ++i) {
                    free(indexF[ind][i]);
                }
                free(indexF[ind]);
            }
            free(marimiF);
            free(indexF);
            return 0;
        }
        if (strcmp(input, "l") == 0) {
            int N = 0, M = 0;
            char *path = malloc(PATHSZ * sizeof(char));
            scanf("%d%d%s", &N, &M, path);
            int ***img = calloc(N, sizeof(int **));
            for (int i = 0; i < N; ++i) {
                img[i] = calloc(M, sizeof(int *));
                for (int j = 0; j < M; ++j) {
                    img[i][j] = calloc(3, sizeof(int));
                }
            }
            read_from_bmp(img, N, M, path);
            int ****aux = realloc(index, (in + 1) * sizeof(int ***));
            size *aux2 = realloc(marimi, (in + 1) * sizeof(size));
            index = aux;
            marimi = aux2;
            index[in] = img;
            marimi[in].N = N;
            marimi[in].M = M;
            in++;
            free(path);
        }
        if (strcmp(input, "s") == 0) {
            int in_citit = 0;
            char *path = malloc(PATHSZ * sizeof(char));
            scanf("%d%s", &in_citit, path);
            write_to_bmp(index[in_citit], marimi[in_citit].N, marimi[in_citit].M, path);
            free(path);
        }
        if (strcmp(input, "ah") == 0) {
            int in_citit = 0;
            scanf("%d", &in_citit);
            int ***img = flip_horizontal(index[in_citit], marimi[in_citit].N, marimi[in_citit].M);
            index[in_citit] = img;
        }
        if (strcmp(input, "ar") == 0) {
            int in_citit = 0;
            scanf("%d", &in_citit);
            int ***img = rotate_left(index[in_citit], marimi[in_citit].N, marimi[in_citit].M);
            index[in_citit] = img;
            swap(&marimi[in_citit].N, &marimi[in_citit].M);
        }
        if (strcmp(input, "ac") == 0) {
            int in_citit = 0, x = 0, y = 0, h = 0, w = 0;
            scanf("%d%d%d%d%d", &in_citit, &x, &y, &w, &h);
            int ***img = crop(index[in_citit], marimi[in_citit].N, marimi[in_citit].M, x, y, h, w);
            index[in_citit] = img;
            marimi[in_citit].N = h;
            marimi[in_citit].M = w;
        }
        if (strcmp(input, "ae") == 0) {
            int in_citit = 0, rows = 0, cols = 0, R = 0, G = 0, B = 0;
            scanf("%d%d%d%d%d%d", &in_citit, &rows, &cols, &R, &G, &B);
            int ***img = extend(index[in_citit], marimi[in_citit].N, marimi[in_citit].M, rows, cols, R, G, B);
            index[in_citit] = img;
            marimi[in_citit].N = marimi[in_citit].N + 2 * rows;
            marimi[in_citit].M = marimi[in_citit].M + 2 * cols;
        }
        if (strcmp(input, "ap") == 0) {
            int ind_dst = 0, ind_scr = 0, x = 0, y = 0;
            scanf("%d%d%d%d", &ind_dst, &ind_scr, &x, &y);
            int ***img = paste(index[ind_dst], marimi[ind_dst].N, marimi[ind_dst].M,
                               index[ind_scr], marimi[ind_scr].N, marimi[ind_scr].M, x, y);
            index[ind_dst] = img;
        }
        if (strcmp(input, "cf") == 0) {
            int sizeF = 0;
            scanf("%d", &sizeF);
            float ***aux = realloc(indexF, (inF + 1) * sizeof(float **));
            indexF = aux;
            indexF[inF] = calloc(sizeF, sizeof(float *));
            for (int i = 0; i < sizeF; ++i) {
                indexF[inF][i] = calloc(sizeF, sizeof(float));
            }
            for (int i = 0; i < sizeF; ++i)
                for (int j = 0; j < sizeF; ++j) {
                    scanf("%f", &indexF[inF][i][j]);
                }
            int *aux2 = realloc(marimiF, (inF + 1) * sizeof(int));
            marimiF = aux2;
            marimiF[inF] = sizeF;
            inF++;
        }
        if (strcmp(input, "af") == 0) {
            int index_img = 0, index_filter = 0;
            scanf("%d%d", &index_img, &index_filter);
            int ***aux = apply_filter(index[index_img], marimi[index_img].N, marimi[index_img].M,
                                      indexF[index_filter], marimiF[index_filter]);
            index[index_img] = aux;
        }
        if (strcmp(input, "df") == 0) {
            int index_filter = 0;
            scanf("%d", &index_filter);
            for (int i = 0; i < marimiF[index_filter]; ++i) {
                free(indexF[index_filter][i]);
            }
            free(indexF[index_filter]);
            for (int i = index_filter; i < inF - 1; ++i) {
                indexF[i] = indexF[i + 1];
                marimiF[i] = marimiF[i + 1];
            }
            inF--;
        }
        if (strcmp(input, "di") == 0) {
            int index_img = 0;
            scanf("%d", &index_img);
            for (int i = 0; i < marimi[index_img].N; ++i) {
                for (int j = 0; j < marimi[index_img].M; ++j) {
                    free(index[index_img][i][j]);
                }
                free(index[index_img][i]);
            }
            free(index[index_img]);
            for (int i = index_img; i < in - 1; ++i) {
                index[i] = index[i + 1];
                marimi[i] = marimi[i + 1];
            }
            in--;
        }
    }

    return 0;
}
