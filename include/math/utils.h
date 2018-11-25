#pragma once
#include "math/vector.h"

double clamp(double lo, double hi, double v);
bool solve_quadratic(double a, double b, double c, double &x0, double &x1);
double drand();
Vec3f reflect(const Vec3f &incident, const Vec3f &normal);
bool refract(const Vec3f &incident, const Vec3f &normal, double ni_over_nt, Vec3f &refracted);
double schlick(double cosine, double refractive_index);
double deg2rad(double deg);
