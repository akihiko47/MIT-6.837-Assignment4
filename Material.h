#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
public:
	
 Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
  diffuseColor( d_color),specularColor(s_color), shininess(s)
  {
        	
  }

  virtual ~Material()
    {

    }

  virtual Vector3f getDiffuseColor() const 
  { 
    return  diffuseColor;
  }
    

  Vector3f Shade( const Ray& ray, const Hit& hit,
                  const Vector3f& dirToLight, const Vector3f& lightColor ) {

      Vector3f V = -ray.getDirection().normalized();
      Vector3f L = dirToLight.normalized();
      Vector3f N = hit.getNormal().normalized();

      Vector3f diff = clamp(Vector3f::dot(L, N), 0.0f, 1.0f) * lightColor * diffuseColor;

      Vector3f H = (V + L).normalized();
      Vector3f spec = pow(clamp(Vector3f::dot(H, N), 0.0f, 1.0f), shininess * 2.0f) * specularColor * lightColor;

      return diff + spec;
  }

  void loadTexture(const char * filename){
    t.load(filename);
  }
 protected:
  Vector3f diffuseColor;
  Vector3f specularColor;
  float shininess;
  Texture t;

  float clamp(float x, float a, float b){
      return max(a, min(x, b));
  }
};



#endif // MATERIAL_H
