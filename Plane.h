#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
		m_normal = normal;
		m_d = d;
	}
	~Plane(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		if(Vector3f::dot(r.getDirection(), m_normal) == 0)
		{
			return false;
		} else {
			Vector3f p0 = m_normal * m_d;
			float t = Vector3f::dot(p0 - r.getOrigin(), m_normal) / Vector3f::dot(r.getDirection(), m_normal);

			if(t < tmin || t > h.getT())
			{
				return false;
			}

			h.set(t, material, m_normal);
			return true;
		}
	}

protected:
	Vector3f m_normal;
	float m_d;
};
#endif //PLANE_H
		

