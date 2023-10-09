#pragma once

//include all shapes
#include "CubeShape.h"
#include "CylinderShape.h"
#include "ConeShape.h"
#include "PlaneShape.h"
#include "PyramidShape.h"
#include "SphereShape.h"

template<class T>
class Shape
{
public:
	template<class... Args>
	static T* Create(Args... args) { return new T(args...); };
};
