#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
  Transform(){}

    Transform( const Matrix4f& m, Object3D* obj ):o(obj){
        o = obj;
        matrix = m;
    }

  ~Transform(){
  }

    virtual bool intersect( const Ray& r , Hit& h , float tmin){
        Vector4f origin = Vector4f(r.getOrigin(), 1.0f);
        Vector4f direction = Vector4f(r.getDirection(), 0.0f);

        Vector3f newOrigin = (matrix.inverse() * origin).xyz();
        Vector3f newDirection = (matrix.inverse() * direction).xyz();

        Ray newRay(newOrigin, newDirection);

        return o->intersect( newRay , h , tmin);

        Vector3f newNormal = (matrix.inverse().transposed() * Vector4f(h.getNormal(), 0.0f)).xyz().normalized();

        h.set(h.getT(), h.getMaterial(), newNormal);
    }

 protected:
  Object3D* o; //un-transformed object	
  Matrix4f matrix;
};

#endif //TRANSFORM_H
