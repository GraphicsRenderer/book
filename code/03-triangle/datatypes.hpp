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

void DrawLine(Image& img, Vector2f p1, Vector2f p2, Color color)
{
    // 将屏幕坐标转换到像素空间
    auto p1i = Vector2i((int)(p1.x * img.Width()), (int)(p1.y * img.Height()));
    auto p2i = Vector2i((int)(p2.x * img.Width()), (int)(p2.y * img.Height()));

    // 如果斜率大于1，我们将x和y交换，从而统一为横扫描
    auto steep = false;
    if (std::abs(p1i.x - p2i.x) < std::abs(p1i.y - p2i.y)) {
        p1i = Vector2i(p1i.y, p1i.x);
        p2i = Vector2i(p2i.y, p2i.x);
        steep = true;
    }

    // 如果p1点在p2点的右侧，则交换两点，从而统一为从左到右扫描
    if (p1i.x > p2i.x) {
        std::swap(p1i, p2i);
    }

    auto dx = p2i.x - p1i.x;
    auto dy = p2i.y - p1i.y;
    auto derror = std::abs(dy / (float)dx);
    auto error = 0.0f;
    auto y = p1i.y;
    for (auto x = p1i.x; x <= p2i.x; x++) {
        if (steep) {
            img.SetColor(y, x, color);
        } else {
            img.SetColor(x, y, color);
        }
        // 当x步进一格，累积一次error，如果error超过0.5，意味着y需要步进一格
        error += derror;
        if (error > 0.5f) {
            // 如果斜率为正，则向上步进，否则向下步进
            y += p2i.y > p1i.y ? 1 : -1;
            // error-1，重置一个像素偏移，重新计算累积error
            error -= 1;
        }
    }
}
} // namespace SoftwareRenderer
