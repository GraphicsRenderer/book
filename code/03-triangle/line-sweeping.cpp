#include "datatypes.hpp"

using namespace SoftwareRenderer;

// 已知线段的两个端点，当一个点在线段上，并已知其y值，求x值
int SolveLineX(Vector2i p1, Vector2i p2, int y)
{
    // p1.y和p2.y应不相等，我们在扫描线循环中，规避了相等情况
    assert(p1.y != p2.y);

    auto t = (y - p1.y) / (float)(p2.y - p1.y);
    return t * (p2.x - p1.x) + p1.x;
}

void DrawTriangle(Image& img, Vector2f p1, Vector2f p2, Vector2f p3, Color color)
{
    // 将屏幕坐标转换到像素空间
    auto p1i = Vector2i(p1.x * img.Width(), p1.y * img.Height());
    auto p2i = Vector2i(p2.x * img.Width(), p2.y * img.Height());
    auto p3i = Vector2i(p3.x * img.Width(), p3.y * img.Height());

    // 将三角形三个坐标按y轴从低到高排序
    if (p1i.y > p2i.y)
        std::swap(p1i, p2i);
    if (p1i.y > p3i.y)
        std::swap(p1i, p3i);
    if (p2i.y > p3i.y)
        std::swap(p2i, p3i);

    // 扫描下半部分三角形，如果三角形水平，p1i.y == p2i.y
    // 则该循环被跳过
    for (auto y = p1i.y; y < p2i.y; y++) {
        auto xMin = SolveLineX(p1i, p3i, y);
        auto xMax = SolveLineX(p1i, p2i, y);
        DrawLine(img, Vector2i(xMin, y), Vector2i(xMax, y), color);
    }

    // 扫描上半部分三角形，如果三角形水平，p2i.y == p3i.y
    // 则该循环被跳过
    for (auto y = p2i.y; y < p3i.y; y++) {
        auto xMin = SolveLineX(p1i, p3i, y);
        auto xMax = SolveLineX(p2i, p3i, y);
        DrawLine(img, Vector2i(xMin, y), Vector2i(xMax, y), color);
    }
}

int main()
{
    auto img = Image(200, 200);
    DrawTriangle(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), Vector2f(0.3f, 0.6f), Color::Red());
    DrawTriangle(img, Vector2f(0.2f, 0.5f), Vector2f(0.1f, 0.8f), Vector2f(0.2f, 0.9f), Color::Green());
    img.SaveAsPNG("line-sweeping.png");
    return 0;
}