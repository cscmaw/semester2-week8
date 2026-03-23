
/* TODO: Define a PGMImage structure that encapsulates:
   - width and height
   - max_gray value
   - 2D array of pixel values (pixels)
*/
typedef struct _pgm_image {
    int width;
    int height;
    char **pixels;
    int max_gray;
} PGMimage;


/* TODO: Update these function prototypes to use your PGMImage structure */
/* Function prototypes */
PGMimage *allocate_image_array(int height, int width);
void free_image_array(PGMimage *image);
PGMimage *read_pgm_image(const char *filename);
void print_image_info(const char *filename, PGMimage *image);
void print_image_values(PGMimage *image);
PGMimage *invert_image_colors(PGMimage *image);
PGMimage *rotate_image(PGMimage *image, int degrees);
int save_pgm_image(const char *filename, PGMimage *image);
