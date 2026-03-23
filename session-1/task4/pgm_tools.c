/**
 * @file activity3-pgm_tools_refactored.c
 * @brief Tools for manipulating PGM (Portable Gray Map) image files
 * 
 * COMP1850 Structures Activity 3
 * 
 * Your task is to refactor this file to use a PGMImage structure.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm_tools.h"

/**
 * @brief Allocates a 2D array for storing the image pixels
 * 
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @return unsigned char** 2D array of image pixels, or NULL if allocation fails
 */
 PGMimage *allocate_image_array(int height, int width) {
    /* TODO: Refactor this to use your PGMImage structure */
    PGMimage *new = malloc(sizeof(PGMimage));
    new->height = height;
    new->width = width;
    new->pixels = calloc(height, sizeof(unsigned char *));
    if (new->pixels == NULL) {
        printf("Error: Memory allocation failed for image array\n");
        return NULL;
    }
    
    for (int i = 0; i < height; i++) {
        new->pixels[i] = calloc(width, sizeof(unsigned char));
        if (new->pixels[i] == NULL) {
            /* Free previously allocated memory if this allocation fails */
            for (int j = 0; j < i; j++) {
                free(new->pixels[j]);
            }
            free(new->pixels);
            printf("Error: Memory allocation failed for image row %d\n", i);
            return NULL;
        }
    }
    return new;
}

/**
 * @brief Frees memory allocated for a 2D image array
 * 
 * @param image The 2D image array to free
 * @param height Number of rows in the image
 */
void free_image_array(PGMimage *image) {
    /* TODO: Refactor this to use your PGMImage structure */
    if (image == NULL) return;
    
    for (int i = 0; i < image->height; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
}

/**
 * @brief Reads a PGM image from a file
 * 
 * @param filename Path to the PGM file
 * @param height Pointer to store the image height
 * @param width Pointer to store the image width
 * @param max_gray Pointer to store the max gray value
 * @return unsigned char** 2D array of image pixels, or NULL if reading fails
 */
PGMimage *read_pgm_image(const char *filename) {
    /* TODO: Refactor this to use your PGMImage structure */

    PGMimage *new;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    
    /* Read PGM header */
    char magic_number[3];
    if (fscanf(file, "%2s", magic_number) != 1) {
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }
    
    if (strcmp(magic_number, "P2") != 0) {
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }
    
    int height, width;
    if (fscanf(file, "%d %d", &(width), &(height)) != 2) {
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }
    
    int max_gray;
    if (fscanf(file, "%d", &(max_gray)) != 1) {
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }
    
    /* Allocate memory for the pixel array */
    new = allocate_image_array(height, width);
    if (new->pixels == NULL) {
        fclose(file);
        return NULL;
    }
    new->max_gray = max_gray;

    /* Read pixel values */
    int pixel_value;
    for (int i = 0; i < new->height; i++) {
        for (int j = 0; j < new->width; j++) {
            if (fscanf(file, "%d", &pixel_value) != 1) {
                printf("Error: Could not read pixel value at position (%d,%d)\n", j, i);
                free_image_array(new);
                fclose(file);
                return NULL;
            }
            new->pixels[i][j] = (unsigned char)pixel_value;
        }
    }
    
    fclose(file);
    return new;
}

/**
 * @brief Prints information about the PGM image
 * 
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void print_image_info(const char *filename, PGMimage *image) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", image->width, image->height);
    printf("Max Gray Value: %d\n", image->max_gray);
}

/**
 * @brief Prints the pixel values of the image
 * 
 * @param pixels The 2D array of image pixels
 * @param height Image height
 * @param width Image width
 */
void print_image_values(PGMimage *image) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("\nImage Pixel Values (%dx%d):\n", image->width, image->height);
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%3d ", image->pixels[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Inverts the colours of the image (255-value)
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return unsigned char** New image with inverted colours
 */
PGMimage *invert_image_colors(PGMimage *original_image) {
    /* TODO: Refactor this to use your PGMImage structure */
    /* Allocate memory for the inverted image */
    PGMimage *inverted_image = allocate_image_array(original_image->height, original_image->width);
    if (inverted_image == NULL) {
        return NULL;
    }
    inverted_image->max_gray = original_image->max_gray;
    
    /* Invert each pixel (max_gray - value) */
    for (int i = 0; i < original_image->height; i++) {
        for (int j = 0; j < original_image->width; j++) {
            inverted_image->pixels[i][j] = original_image->max_gray - original_image->pixels[i][j];
        }
    }
    
    return inverted_image;
}

/**
 * @brief Rotates the image by the specified angle
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param degrees Rotation angle (90, 180, or 270 degrees)
 * @return unsigned char** New rotated image
 */
PGMimage *rotate_image(PGMimage *original_image, int degrees) {
    /* TODO: Refactor this to use your PGMImage structure */
    PGMimage *rotated_image;
    
    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            rotated_image = allocate_image_array(original_image->width, original_image->height);
            if (rotated_image->pixels == NULL) {
                return NULL;
            }
            
            /* 90 degree rotation algorithm */
            for (int i = 0; i < original_image->height; i++) {
                for (int j = 0; j < original_image->width; j++) {
                    rotated_image->pixels[j][original_image->height-1-i] = original_image->pixels[i][j];
                }
            }
            break;
            
        case 180:
            rotated_image = allocate_image_array(original_image->height, original_image->width);
            if (rotated_image == NULL) {
                return NULL;
            }
            
            /* 180 degree rotation algorithm */
            for (int i = 0; i < original_image->height; i++) {
                for (int j = 0; j < original_image->width; j++) {
                    rotated_image->pixels[original_image->height-1-i][original_image->width-1-j] = original_image->pixels[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            rotated_image = allocate_image_array(original_image->width, original_image->height);
            if (rotated_image->pixels == NULL) {
                return NULL;
            }
            
            /* 270 degree rotation algorithm */
            for (int i = 0; i < original_image->height; i++) {
                for (int j = 0; j < original_image->width; j++) {
                    rotated_image->pixels[original_image->width-1-j][i] = original_image->pixels[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }
    
    return rotated_image;
}

/**
 * @brief Saves a PGM image to a file
 * 
 * @param filename Output filename
 * @param pixels Image pixel array
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return int 1 if successful, 0 if failedPGMimag
 */
int save_pgm_image(const char *filename, PGMimage *image) {
    /* TODO: Refactor this to use your PGMImage structure */
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", filename);
        return 0;
    }
    
    /* Write PGM header */
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_gray);
    
    /* Write pixel values */
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(file, "%d ", image->pixels[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    return 1;
}
