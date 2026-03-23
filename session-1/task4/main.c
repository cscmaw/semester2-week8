
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm_tools.h"
#include "menu.h"



int main(int argc, char **argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    PGMimage *image;
    
    /* Read the image */
    image = read_pgm_image(argv[1]);
    
    /* Check if image reading was successful */
    if (image == NULL) {
        return 1;
    }
    
    /* Display image information */
    print_image_info(argv[1], image);

    int k = menu( image );

    return 0;
}

