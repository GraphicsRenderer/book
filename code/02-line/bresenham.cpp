// Pre-defined data types
#include "datatypes.hpp"

using namespace SoftwareRenderer;

void DrawLine(Image& img, Vector2f p1, Vector2f p2, Color color)
{
    // 将屏幕坐标转换到像素空间
    auto p1i = Vector2i(p1.x * img.Width(), p1.y * img.Height());
    auto p2i = Vector2i(p2.x * img.Width(), p2.y * img.Height());

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

int main()
{
    auto img = Image(200, 200);
    DrawLine(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), Color::Red());
    DrawLine(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.25f), Color::Green());
    DrawLine(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.96f), Color::Blue());
    img.SaveAsPNG("bresenham.png");
    return 0;
}