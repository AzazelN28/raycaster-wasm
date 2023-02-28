#pragma once

#define ABS(x) x < 0 ? -x : x
#define CLAMP(x, min, max) x < min ? min : (x > max ? max : x)
