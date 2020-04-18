#pragma once

using Seconds = float;
using Millis = unsigned int;
using Radians = float;
using Degrees = float;
using Meters = float;

namespace lazye
{
    constexpr float PI = 3.14159265358979323846f;

    constexpr Degrees RadToDeg(Radians rad) { return rad / PI * 180.f; }
    constexpr Radians DegToRad(Degrees deg) { return deg / 180.f * PI; }
}