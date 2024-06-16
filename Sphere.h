#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere() : Object3D(material)
	{ 
		m_center = Vector3f::ZERO;
		m_radius = 1;
	}

	Sphere( Vector3f center , float radius , Material* material ) : Object3D(material)
	{
		m_center = center;
		m_radius = radius;
	}
	
	~Sphere()
	{

	}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		Vector3f Ro = r.getOrigin() - m_center;

		float a = Vector3f::dot(r.getDirection(), r.getDirection());
		float b = 2.0 * Vector3f::dot(r.getDirection(), Ro);
		float c = Vector3f::dot(Ro, Ro) - m_radius * m_radius;

		float disc = b * b - 4.0 * a * c;

		if(disc < 0)
		{
			return false;
		}

		float t0 = (-b + std::sqrtf(disc)) / (2.0 * a);
		float t1 = (-b - std::sqrtf(disc)) / (2.0 * a);

		if (t0 < tmin && t1 < tmin) {
			return false;
		} else {
			if (t0 < t1) {
				if(t0 > h.getT())
				{
					return false;
				}
				Vector3f n = r.getOrigin() + t0 * r.getDirection() - m_center;
				h.set(t0, material, n);
				return true;
			} else {
				if(t1 > h.getT())
				{
					return false;
				}
				Vector3f n = r.getOrigin() + t1 * r.getDirection() - m_center;
				h.set(t1, material, n);
				return true;
			}
		}

	}

protected:
	Vector3f m_center;
	float m_radius;
};


#endif
