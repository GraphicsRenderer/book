#pragma once

// This line is required for stb image library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>
#include <vector>

namespace SoftwareRenderer {
struct Vector2f {
    float x;
    float y;

    explicit Vector2f()
        : Vector2f(0, 0)
    {
    }

    explicit Vector2f(float x, float y)
        : x(x)
        , y(y)
    {
    }
};

struct Vector2i {
    int x;
    int y;

    explicit Vector2i()
        : Vector2i(0, 0)
    {
    }

    explicit Vector2i(int x, int y)
        : x(x)
        , y(y)
    {
    }
};

struct Color {
    char r;
    char g;
    char b;
    char a;

    explicit Color()
        : Color((char)0, (char)0, (char)0, (char)255)
    {
    }

    explicit Color(char r, char g, char b)
        : Color(r, g, b, (char)255)
    {
    }

    explicit Color(char r, char g, char b, char a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    static inline Color White() { return Color((char)255, (char)255, (char)255); }

    static inline Color Black() { return Color((char)0, (char)0, (char)0); }

    static inline Color Red() { return Color((char)255, (char)0, (char)0); }

    static inline Color Green() { return Color((char)0, (char)255, (char)0); }

    static inline Color Blue() { return Color((char)0, (char)0, (char)255); }
};

class Image {
private:
    int _width;
    int _height;
    std::vector<Color> _pixels;

public:
    explicit Image()
        : Image(1, 1)
    {
    }

    explicit Image(int width, int height)
        : Image(width, height, Color::Black())
    {
    }

    explicit Image(int width, int height, Color color)
    {
        _width = width;
        _height = height;
        _pixels.resize(_width * _height);
        for (auto i = 0; i < _width * _height; i++)
            _pixels[i] = color;
    }

    int Width() const
    {
        return _width;
    }

    int Height() const
    {
        return _height;
    }

    Color GetColor(int x, int y) const
    {
        auto idx = y * Width() + x;
        return _pixels[idx];
    }

    void SetColor(int x, int y, Color color)
    {
        auto idx = y * Width() + x;
        _pixels[idx] = color;
    }

    void SaveAsPNG(const char* filepath)
    {
        auto pixels = std::vector<Color>();
        pixels.resize(Width() * Height());
        for (auto x = 0; x < Width(); x++)
            for (auto y = 0; y < Height(); y++) {
                auto idx = (Height() - y - 1) * Width() + x;
                if (idx < 0 || idx >= Width() * Height())
                    continue;
                pixels[idx] = GetColor(x, y);
            }
        stbi_write_png(filepath, Width(), Height(), 4, pixels.data(), Width() * 4);
    }
};
} // namespace SoftwareRenderer
