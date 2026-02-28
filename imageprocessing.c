#include "imageprocessing.h"
#include <stdio.h>
#include <stdlib.h>
#define maxColor 255
#define minColor 0
int ***flip_horizontal(int ***image, int N, int M) {
    int ***flip = malloc(N * sizeof(int **));
    for (int i = 0; i < N; ++i) {
        flip[i] = malloc(M * sizeof(int *));
        if (!flip[i])
            return NULL;
        for (int j = 0; j < M; ++j) {
            flip[i][j] = malloc(3 * sizeof(int));
            if (!flip[i][j])
                return NULL;
        }
    }
    if (!flip)
        return NULL;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < 3; ++k) {
                flip[i][j][k] = image[i][M - j - 1][k];
            }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            free(image[i][j]);
        free(image[i]);
    }
    free(image);
    return flip;
}

int ***rotate_left(int ***image, int N, int M) {
    int Nf = M, Mf = N;
    int ***flip = malloc(Nf * sizeof(int **));
    for (int i = 0; i < Nf; ++i) {
        flip[i] = malloc(Mf * sizeof(int *));
        if (!flip[i])
            return NULL;
        for (int j = 0; j < Mf; ++j) {
            flip[i][j] = malloc(3 * sizeof(int));
            if (!flip[i][j])
                return NULL;
        }
    }
    if (!flip)
        return NULL;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < 3; ++k) {
                flip[M - j - 1][i][k] = image[i][j][k];
            }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            free(image[i][j]);
        free(image[i]);
    }
    free(image);
    return flip;
}

int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***flip = malloc(h * sizeof(int **));
    for (int i = 0; i < h; ++i) {
        flip[i] = malloc(w * sizeof(int *));
        if (!flip[i])
            return NULL;
        for (int j = 0; j < w; ++j) {
            flip[i][j] = malloc(3 * sizeof(int));
            if (!flip[i][j])
                return NULL;
        }
    }
    if (!flip)
        return NULL;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            for (int k = 0; k < 3; ++k) {
                flip[i][j][k] = image[i + y][j + x][k];
            }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            free(image[i][j]);
        free(image[i]);
    }
    free(image);
    return flip;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int ***flip = calloc(N + 2 * rows, sizeof(int **));
    for (int i = 0; i < N + 2 * rows; ++i) {
        flip[i] = calloc(M + 2 * cols, sizeof(int *));
        if (!flip[i])
            return NULL;
        for (int j = 0; j < M + 2 * cols; ++j) {
            flip[i][j] = malloc(3 * sizeof(int));
            if (!flip[i][j])
                return NULL;
        }
    }
    for (int i = 0; i < N + 2 * rows; ++i) {
        for (int j = 0; j < M + 2 * cols; ++j) {
            if (i < rows || i >= rows + N || j < cols || j >= cols + M) {
                flip[i][j][0] = new_R;
                flip[i][j][1] = new_G;
                flip[i][j][2] = new_B;
            } else {
                for (int k = 0; k < 3; ++k) {
                    flip[i][j][k] = image[i - rows][j - cols][k];
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            free(image[i][j]);
        free(image[i]);
    }
    free(image);
    return flip;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    for (int i = 0; i < N_src && i + y < N_dst; ++i)
        for (int j = 0; j < M_src && j + x < M_dst; ++j)
            for (int k = 0; k < 3; ++k)
                image_dst[i + y][j + x][k] = image_src[i][j][k];
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int ***new_img = calloc(N, sizeof(int **));
    for (int i = 0; i < N; ++i) {
        new_img[i] = calloc(M, sizeof(int *));
        for (int j = 0; j < M; ++j) {
            new_img[i][j] = calloc(3, sizeof(int));
        }
    }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < 3; ++k)
                new_img[i][j][k] = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < 3; ++k) {
                float new_color = 0;
                for (int fi = 0; fi < filter_size; ++fi)
                    for (int fj = 0; fj < filter_size; ++fj) {
                        int x = i - filter_size / 2 + fi;
                        int y = j - filter_size / 2 + fj;
                        if (x >= 0 && x < N && y >= 0 && y < M) {
                            new_color += ((float)image[x][y][k] * filter[fi][fj]);
                        }
                    }
                if (new_color < minColor)
                    new_color = minColor;
                if (new_color > maxColor)
                    new_color = maxColor;
                new_img[i][j][k] = (int)new_color;
            }
        }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            free(image[i][j]);
        free(image[i]);
    }
    free(image);
    return new_img;
}
