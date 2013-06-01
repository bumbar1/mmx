#ifndef MMX_OPENGL_SHADER_HPP
#define MMX_OPENGL_SHADER_HPP 1

namespace mmx {
	namespace opengl {

		/// Vertex Shader, Fragment Shader
		class Shader {
		public:
			loadFromFile(const std::string& file);
			loadFromFile(const char* file);
			//loadFromString(const std::string& str);
			//loadFromString(const char* str);
			//loadFromMemory(void* ptr, unsigned size);

		private:
		};
		
	}		// ~namespace opengl
}           // ~namespace mmx

#endif     // ~MMX_OPENGL_SHADER_HPP
