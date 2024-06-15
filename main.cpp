#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>


using namespace std;

#include <algorithm>

float clamp(float x, float a, float b){
    return max(a, min(x, b));
}

float smoothstep(float edge0, float edge1, float x){
    // Scale, bias and saturate x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
    //SceneParser parser = SceneParser(;
    // Fill in your implementation here.

    // This loop loops over each of the input arguments.
    // argNum is initialized to 1 because the first
    // "argument" provided to the program is actually the
    // name of the executable (in our case, "a4").
    for( int argNum = 1; argNum < argc; ++argNum )
    {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
	
    // First, parse the scene using SceneParser.
    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.

    SceneParser parser(argv[2]);

    int size_x = std::stoi(argv[4]);
    int size_y = std::stoi(argv[5]);
    Image image(size_x, size_y);

    for(int i = 0; i < size_x; i++)
    {
        for(int j = 0; j < size_y; j++)
        {
            Ray ray = parser.getCamera()->generateRay(Vector2f((float)i / size_x * 2 - 1, (float)j / size_y * 2 - 1));
            Hit hit;

            bool result = parser.getGroup()->intersect(ray, hit, parser.getCamera()->getTMin());
            if(result)
            {
                //float depth = hit.getT();
                //depth = smoothstep(8.0, 10.0, depth);

                Vector3f p = ray.getOrigin() + ray.getDirection() * hit.getT();
                Vector3f pixelColor(0.0f);

                for (int l = 0; l < parser.getNumLights(); l++)
                {
                    Light* light = parser.getLight(l);

                    Vector3f lightColor;
                    float lightDist;
                    Vector3f L;
                    light->getIllumination(p, L, lightColor, lightDist);

                    pixelColor += hit.getMaterial()->Shade(ray, hit, L, lightColor);
                }

                pixelColor += parser.getAmbientLight();

                image.SetPixel(i, j, pixelColor);
            } else {
                image.SetPixel(i, j, parser.getBackgroundColor());
            }
        }
    }

    image.SaveImage(argv[7]);
    return 0;
}

