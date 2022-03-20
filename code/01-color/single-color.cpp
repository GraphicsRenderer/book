// single-color.cpp

// This line is required for stb image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>

int main() {
  int w = 200;
  int h = 200;
  int c = 3;

  char pixels[w * h * c];
  for (auto x = 0; x < w; x++)
    for (auto y = 0; y < h; y++) {
      pixels[(y * w + x) * c + 0] = (char)255;
      pixels[(y * w + x) * c + 1] = (char)0;
      pixels[(y * w + x) * c + 2] = (char)0;
    }

  stbi_write_png("single-color.png", w, h, c, pixels, w * 3);
  return 0;
}