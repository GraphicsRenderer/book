#pragma once

#include "datatypes.hpp"

using namespace SoftwareRenderer;

Vector2i BBoxMin(Vector2i p1, Vector2i p2, Vector2i p3)
{
    return Vector2i(0, 0);
}

Vector2i BBoxMax(Vector2i p1, Vector2i p2, Vector2i p3)
{
    return Vector2i(0, 0);
}

bool IsInsideTriangle(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p)
{
    return false;
}