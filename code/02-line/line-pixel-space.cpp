// Pre-defined data types
#include "datatypes.hpp"

using namespace SoftwareRenderer;

void DrawLine(Image& img, Vector2f p1, Vector2f p2, Color color)
{
    int px1 = p1.x * img.Width(), px2 = p2.x * img.Width();
    int py1 = p1.y * img.Height(), py2 = p2.y * img.Height();
    for (auto x = px1; x <= px2; x++) {
        auto t = (x - px1) / (float)(px2 - px1);
        auto y = (int)(t * (py2 - py1) + py1);
        img.SetColor(x, y, color);
    }
}

int main()
{
    auto img = Image(200, 200);
    DrawLine(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), Color::Red());
    img.SaveAsPNG("line-pixel-space.png");
}
