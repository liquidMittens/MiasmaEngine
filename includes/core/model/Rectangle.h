#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <vector>

namespace Rectangle
{
	class Rectangle
	{
	private:
		float l;
		float w;
		float h;
	public:
		
		Rectangle(float l, float w, float h) :
			l(l),
			w(w),
			h(h)
		{

		}

		//x,y,z,r,g,b,s,t
		std::vector<float> vertices = { {
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom
			 l, -w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

			 l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-l,  w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

			-l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //top
			 l, -w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-l,  w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						 
			-l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //left
			-l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
						 
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						
			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //right
			 l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
						
			 l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						 
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //back
			 l, -w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 l, -w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						
			 l, -w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-l, -w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-l, -w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
						 
			-l,  w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, //front
			 l,  w, -h, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						 
			 l,  w,  h, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-l,  w,  h, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-l,  w, -h, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
		} };
	};


}

#endif
