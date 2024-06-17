#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& _a, const Vector3f& _b, const Vector3f& _c, Material* m):Object3D(m){
          hasTex = false;
		  a = _a;
		  b = _b;
		  c = _c;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
		Matrix3f A(a.x() - b.x(), a.x() - c.x(), ray.getDirection().x(),
				   a.y() - b.y(), a.y() - c.y(), ray.getDirection().y(),
				   a.z() - b.z(), a.z() - c.z(), ray.getDirection().z());

		float beta = Matrix3f::determinant3x3(a.x() - ray.getOrigin().x(), a.x() - c.x(), ray.getDirection().x(),
											  a.y() - ray.getOrigin().y(), a.y() - c.y(), ray.getDirection().y(),
											  a.z() - ray.getOrigin().z(), a.z() - c.z(), ray.getDirection().z()) / A.determinant();

		float gamma = Matrix3f::determinant3x3(a.x() - b.x(), a.x() - ray.getOrigin().x(), ray.getDirection().x(),
											   a.y() - b.y(), a.y() - ray.getOrigin().y(), ray.getDirection().y(),
											   a.z() - b.z(), a.z() - ray.getOrigin().z(), ray.getDirection().z()) / A.determinant();

		float t = Matrix3f::determinant3x3(a.x() - b.x(), a.x() - c.x(), a.x() - ray.getOrigin().x(),
										   a.y() - b.y(), a.y() - c.y(), a.y() - ray.getOrigin().y(),
										   a.z() - b.z(), a.z() - c.z(), a.z() - ray.getOrigin().z()) / A.determinant();

		float alpha = 1.0f - beta - gamma;

		if(alpha >= 0 && beta >= 0 && gamma >= 0)
		{
			if(t > tmin && t < hit.getT())
			{
				//Vector3f normal = alpha * normals[0] + beta * normals[1] + gamma * normals[2];
				Vector3f normal = Vector3f::cross(b - a, c - a);

				hit.set(t, material, normal);
				hit.setTexCoord(alpha * texCoords[0] + beta * texCoords[1] + gamma * texCoords[2]);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}

		
	}
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:

private:
	Vector3f a;
	Vector3f b;
	Vector3f c;
};

#endif //TRIANGLE_H
