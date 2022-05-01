#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <cstdint>

namespace Sinian
{
	class Texture2D
	{
	public:
		Texture2D(const char *path);
		~Texture2D();

		//øΩ±¥ππ‘Ï
		Texture2D(const Texture2D &t);
		Texture2D &operator=(const Texture2D &t);
		//Texture2D(Texture2D&& t) = delete;		//noexcept;
		//Texture2D& operator=(Texture2D&& t) = delete;		//noexcept;


		uint32_t Id() { return id; };

	protected:
		void TextureFromFile(const char *path);

		uint32_t id;
	};
}

#endif
