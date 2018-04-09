#include "Point.h"

#include "Triangle.h"

#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <nanovg.h>

#include <array>

Point::Point(const glm::vec2& position, float size)
	: pos{ position }
	, size{ size }
{
}

Point::~Point()
{
}

void Point::draw(NVGcontext* vg) const
{
	nvgFillColor(vg, nvgRGBA(255, 50, 0, 128));
	nvgStrokeColor(vg, nvgRGBA(255, 50, 0, 255));

	nvgBeginPath(vg);
	nvgMoveTo(vg, pos.x - size, pos.y - size);
	nvgLineTo(vg, pos.x - size, pos.y + size);
	nvgLineTo(vg, pos.x + size, pos.y + size);
	nvgLineTo(vg, pos.x + size, pos.y - size);
	nvgLineTo(vg, pos.x - size, pos.y - size);
	nvgFill(vg);
	nvgStroke(vg);
}

bool Point::inside(const Triangle& tri) const
{
	std::array<glm::vec2, 3> dirsToVerts;
	for (size_t i = 0; i < tri.vertices.size(); ++i) {
		dirsToVerts[i] = glm::normalize(tri.vertices[i] - this->pos);
	}

	float angleSum = 0;
	for (size_t i = 0; i < dirsToVerts.size(); ++i) {
		angleSum += glm::abs(glm::acos(glm::dot(dirsToVerts[i], dirsToVerts[(i + 1) % 3])));
	}

	if (glm::abs(angleSum - 2 * glm::pi<float>()) < 0.001f)
		return true;
	else
		return false;
}
