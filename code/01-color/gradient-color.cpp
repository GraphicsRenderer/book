// gradient-color.cpp

// This line is required for stb image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>

struct Color {
  char r;
  char g;
  char b;
};

Color PixelColor(float u, float v) {
  Color c;
  c.r = (char)(u * 255);
  c.g = (char)(v * 255);
  c.b = 0;
  return c;
}

int main() {
  int w = 200;
  int h = 200;
  int c = 3;

  Color pixels[w * h];
  for (auto x = 0; x < w; x++)
    for (auto y = 0; y < h; y++) {
      auto u = x / (float)w;
      auto v = y / (float)h;
      pixels[y * w + x] = PixelColor(u, v);
    }

  stbi_write_png("gradient-color.png", w, h, c, pixels, w * 3);
  return 0;
}