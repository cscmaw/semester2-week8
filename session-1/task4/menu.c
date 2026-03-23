
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm_tools.h"
#include "menu.h"


int menu( PGMimage *image ) {
    int choice = -1;
    char output_filename[100];
    int rotation_degrees;
    PGMimage *processed_image = NULL;

    /* Main program loop */
    do {
        choice = -1;
        display_menu();
        while (choice < 1)
            choice = get_user_menu_choice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            print_image_values(image);
            break;
            
        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
            processed_image = invert_image_colors(image);
            
            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */
            
            if (save_pgm_image(output_filename, processed_image)) {
                printf("Inverted image saved to %s\n", output_filename);
            } else {
                printf("Failed to save inverted image\n");
            }
            
            /* Free the processed image memory */
            free_image_array(processed_image);
            break;
            
        case 3: /* Rotate image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Enter rotation in degrees (90, 180, or 270): ");
            scanf("%d", &rotation_degrees);
            getchar(); /* Consume newline */
            
            /* Validate rotation degrees */
            if (rotation_degrees != 90 && rotation_degrees != 180 && rotation_degrees != 270) {
                printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
                break;
            }
            
            printf("Rotating image by %d degrees...\n", rotation_degrees);
            processed_image = rotate_image(image, rotation_degrees);
            
            printf("Enter output filename: ");
            scanf("%99s", output_filename);
            getchar(); /* Consume newline */
            
            /* For 90 and 270 degree rotations, height and width are swapped */
            if (rotation_degrees == 90 || rotation_degrees == 270) {
                if (save_pgm_image(output_filename, processed_image)) {
                    printf("Rotated image saved to %s\n", output_filename);
                } else {
                    printf("Failed to save rotated image\n");
                }
                free_image_array(processed_image);
            } else { /* 180 degrees */
                if (save_pgm_image(output_filename, processed_image)) {
                    printf("Rotated image saved to %s\n", output_filename);
                } else {
                    printf("Failed to save rotated image\n");
                }
                free_image_array(processed_image);
            }
            break;
            
        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            free_image_array(image);
            free( image );
            return 0;
            
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}

/**
 * @brief Gets user menu choice from standard input
 * 
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int get_user_menu_choice(const char *message) {
    char buffer[100];
    int choice;
    printf("%s: ", message);
    fgets(buffer, 100, stdin);
    int check = sscanf(buffer, "%d", &choice);
    if (!check) {
        return -1;
    }
    return choice;
}

/**
 * @brief Displays the main program menu
 */
void display_menu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}
