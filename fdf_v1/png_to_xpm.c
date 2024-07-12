
// gcc -o png_to_xpm png_to_xpm.c -lpng
// ./png_to_xpm input.png output.xpm


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#define MAX_COLORS 256

typedef struct {
    unsigned char r, g, b, a;
} Color;

typedef struct {
    Color color;
    char symbol;
    int count;
} ColorEntry;

int compare_colors(const void *a, const void *b) {
    return ((ColorEntry*)b)->count - ((ColorEntry*)a)->count;
}

void png_to_xpm(const char *input_file, const char *output_file) {
    FILE *fp_in = fopen(input_file, "rb");
    if (!fp_in) {
        fprintf(stderr, "Nie można otworzyć pliku wejściowego\n");
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Błąd podczas odczytu PNG\n");
        fclose(fp_in);
        png_destroy_read_struct(&png, &info, NULL);
        return;
    }

    png_init_io(png, fp_in);
    
    // Ignoruj problematyczny profil kolorów
    png_set_option(png, PNG_SKIP_sRGB_CHECK_PROFILE, PNG_OPTION_ON);
    
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    printf("Debug: Wymiary obrazu: %d x %d\n", width, height);
    printf("Debug: Typ koloru: %d, Głębia bitowa: %d\n", color_type, bit_depth);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));

    png_read_image(png, row_pointers);

    fclose(fp_in);

    // Analiza kolorów i tworzenie palety
    ColorEntry palette[MAX_COLORS] = {0};
    int palette_size = 0;

    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            Color color = {px[0], px[1], px[2], px[3]};

            int found = 0;
            for (int i = 0; i < palette_size; i++) {
                if (memcmp(&palette[i].color, &color, sizeof(Color)) == 0) {
                    palette[i].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && palette_size < MAX_COLORS) {
                palette[palette_size].color = color;
                palette[palette_size].symbol = palette_size < 62 ? palette_size + 65 : (palette_size < 62 + 26 ? palette_size + 71 : palette_size + 19);
                palette[palette_size].count = 1;
                palette_size++;
            }
        }
    }

    printf("Debug: Liczba unikalnych kolorów: %d\n", palette_size);

    qsort(palette, palette_size, sizeof(ColorEntry), compare_colors);

    // Zapis do pliku XPM
    FILE *fp_out = fopen(output_file, "w");
    if (!fp_out) {
        fprintf(stderr, "Nie można otworzyć pliku wyjściowego\n");
        return;
    }

    fprintf(fp_out, "/* XPM */\n");
    fprintf(fp_out, "static char *image[] = {\n");
    fprintf(fp_out, "\"%d %d %d %d\",\n", width, height, palette_size, 1);

    for (int i = 0; i < palette_size; i++) {
        fprintf(fp_out, "\"%c c #%02X%02X%02X\",\n", palette[i].symbol,
                palette[i].color.r, palette[i].color.g, palette[i].color.b);
    }

    int total_pixels = 0;
    for (int y = 0; y < height; y++) {
        fprintf(fp_out, "\"");
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            Color color = {px[0], px[1], px[2], px[3]};
            int found = 0;
            for (int i = 0; i < palette_size; i++) {
                if (memcmp(&palette[i].color, &color, sizeof(Color)) == 0) {
                    fputc(palette[i].symbol, fp_out);
                    found = 1;
                    total_pixels++;
                    break;
                }
            }
            if (!found) {
                fputc(palette[0].symbol, fp_out); // Użyj pierwszego koloru jako domyślnego
                total_pixels++;
            }
        }
        fprintf(fp_out, "\"%s\n", y == height - 1 ? "" : ",");
    }

    fprintf(fp_out, "};\n");
    fclose(fp_out);

    printf("Debug: Liczba zapisanych pikseli: %d (powinno być %d)\n", total_pixels, width * height);

    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Użycie: %s <plik_wejściowy.png> <plik_wyjściowy.xpm>\n", argv[0]);
        return 1;
    }

    png_to_xpm(argv[1], argv[2]);
    return 0;
}
