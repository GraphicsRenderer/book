#include "datatypes.hpp"

using namespace SoftwareRenderer;

void DrawTriangleFrame(Image& img, Vector2f p1, Vector2f p2, Vector2f p3, Color color)
{
    DrawLine(img, p1, p2, color);
    DrawLine(img, p2, p3, color);
    DrawLine(img, p3, p1, color);
}

int main()
{
    auto img = Image(200, 200);
    DrawTriangleFrame(img, Vector2f(0.2f, 0.2f), Vector2f(0.6f, 0.6f), Vector2f(0.3f, 0.6f), Color::Red());
    DrawTriangleFrame(img, Vector2f(0.2f, 0.5f), Vector2f(0.1f, 0.8f), Vector2f(0.2f, 0.9f), Color::Green());
    img.SaveAsPNG("triangle-frame.png");
    return 0;
}