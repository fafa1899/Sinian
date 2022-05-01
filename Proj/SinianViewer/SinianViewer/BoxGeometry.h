#pragma once
#include "BufferGeometry.h"

namespace Sinian
{
	class BoxGeometry :
		public BufferGeometry
	{
	public:
		BoxGeometry(double width = 1.0, double height = 1.0, double depth = 1.0);
	};
}



