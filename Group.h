#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

  Group(){

  }
	
  Group( int num_objects ){
	  objects.resize(num_objects);
  }

  ~Group(){
	  for(int i = 0; i < objects.size(); i++)
	  {
		  delete objects[i];
	  }
  }

  virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
	  float t = INFINITY;
	  for(int i = 0; i < objects.size(); i++)
	  {
		  if(objects[i]->intersect(r, h, tmin))
		  {
			  if(h.getT() < t)
			  {
				  t = h.getT();
			  }
		  }
	  }

	  if(t == INFINITY)
	  {
		  return false;
	  }
	  else
	  {
		  return true;
	  }
   }
	
  void addObject( int index , Object3D* obj ){
	  objects[index] = obj;
  }

  int getGroupSize(){ 
	  return objects.size();
  }

 private:
	 vector<Object3D*> objects;
};

#endif
	
