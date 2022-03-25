#include "bounding-box.hpp"
#include "datatypes.hpp"

using namespace SoftwareRenderer;

void DrawTriangle(Image& img, Vector2f p1, Vector2f p2, Vector2f p3, Color color)
{
    // 将屏幕坐标转换到像素空间
    auto p1i = Vector2i(p1.x * img.Width(), p1.y * img.Height());
    auto p2i = Vector2i(p2.x * img.Width(), p2.y * img.Height());
    auto p3i = Vector2i(p3.x * img.Width(), p3.y * img.Height());

    // 找到包围盒左下和右上两个端点
    auto min = BBoxMin(p1i, p2i, p3i);
    auto max = BBoxMax(p1i, p2i, p3i);

    // 循环包围盒内所有像素，并测试是否在三角形内
    for (auto x = min.x; x <= max.x; x++)
        for (auto y = min.y; y <= max.y; y++) {
            if (!IsInsideTriangle(p1i, p2i, p3i, Vector2i(x, y)))
                continue;
            img.SetColor(x, y, color);
        }
}

int main()
{
    auto img = Image(200, 200);
    DrawTriangle(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), Vector2f(0.3f, 0.6f), Color::Red());
    DrawTriangle(img, Vector2f(0.2f, 0.5f), Vector2f(0.1f, 0.8f), Vector2f(0.2f, 0.9f), Color::Green());
    img.SaveAsPNG("bbox.png");
    return 0;
}