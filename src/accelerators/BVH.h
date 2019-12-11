#ifndef AYA_BVH_H
#define AYA_BVH_H

#include <algorithm>

#include "../core/primitive.h"

namespace Aya {
	class BVHNode{
	public:
		BVHNode *l_l, *r_l;
		BBox m_box;

		BVHNode() {
			l_l = r_l = NULL;
			m_box = BBox();
		}
		virtual inline bool intersect(const Ray &ray, SurfaceInteraction * si, bool &is_leaf) const {
			is_leaf = false;
			return m_box.intersect(ray);
		}
		inline void unity() {
			m_box = l_l->m_box;
			m_box.unity(r_l->m_box);
		}
	};
	class BVHLeaf : public BVHNode {
	public:
		SharedPtr<Primitive> m_prim;

		BVHLeaf() {
			l_l = r_l = NULL;
			m_box = BBox();
		}
		BVHLeaf(const SharedPtr<Primitive> &prim) {
			m_prim = prim;
			m_box = m_prim->worldBound();
		}
		virtual inline bool intersect(const Ray &ray, SurfaceInteraction * si, bool &is_leaf) const {
			is_leaf = true;
			return m_prim->intersect(ray, si);
		}
	};

	class BVHAccel : public Accelerator {
	public:
		std::vector<SharedPtr<Primitive> > m_prims;
		BVHNode *m_root;
	public:
		BVHAccel() {
			m_root = NULL;
		}

		virtual void construct(std::vector<SharedPtr<Primitive> > prims);
		virtual BBox worldBound() const;
		virtual bool canIntersect() {
			return false;
		}
		virtual bool intersect(const Ray &ray, SurfaceInteraction *si) const;

	private:
		bool intersect(BVHNode *node, const Ray &ray, SurfaceInteraction *si) const;
		void construct(BVHNode **node, const int &L, const int &R);
	};
}

#endif