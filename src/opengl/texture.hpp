#ifndef MMX_OPENGL_TEXTURE_HPP
#define MMX_OPENGL_TEXTURE_HPP 1

namespace mmx {
	namespace opengl {

		class Texture {
		public:
			loadFromFile(const std::string& file);
			loadFromFile(const char* file);
			//loadFromString(const std::string& str);
			//loadFromString(const char* str);
			//loadFromMemory(void* ptr, unsigned size);
		};
		
	}		// ~namespace opengl
}           // ~namespace mmx

#endif     // ~MMX_OPENGL_TEXTURE_HPP
