#pragma once
#include "BufferGeometry.h"

namespace Sinian
{
	class PlaneGeometry :
		public BufferGeometry
	{
	public:
		PlaneGeometry(double width = 1.0, double height = 1.0);
	};
}

