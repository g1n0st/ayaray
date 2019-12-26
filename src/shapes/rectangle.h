#ifndef AYA_RECTANGLE_H
#define AYA_RECTANGLE_H

#include "../core/shape.h"

namespace Aya {
	/**@brief Rectangle class inherits Shape base class and represents a rectangle*/
	class Rectangle : public Shape {
	public:
		/**@brief the length of three vertical sides */
		float m_x, m_y, m_z;

	public:
		Rectangle(const Transform *O2W, const Transform *W2O, const float &x, const float &y, const float &z);
		~Rectangle();

		virtual BBox objectBound() const;
		virtual bool intersect(const Ray &ray, float *hit_t, SurfaceInteraction *si) const;
	};
}

#endif