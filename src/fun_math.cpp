#include "fun_math.h"

float funLerp(float a, float b, float t) {
  return (1-t) * a + t * b;
}