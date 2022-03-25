// Pre-defined data types
#include "datatypes.hpp"

using namespace SoftwareRenderer;

void DrawLine(Image& img, Vector2f p1, Vector2f p2, float step, Color color)
{
    float lx = p2.x - p1.x, ly = p2.y - p1.y;
    for (auto t = 0.0f; t <= 1.0f; t += step) {
        auto x = p1.x + t * lx;
        auto y = p1.y + t * ly;
        // 将屏幕坐标转换到像素空间
        img.SetColor(img.Width() * x, img.Height() * y, color);
    }
}

int main()
{
    auto img = Image(200, 200);
    DrawLine(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), 0.01f, Color::Red());
    img.SaveAsPNG("line-0.01.png");
}