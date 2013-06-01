#ifndef MMX_OPENGL_CONTEXT_HPP
#define MMX_OPENGL_CONTEXT_HPP 1

#if defined( _WIN32 )
#	include <windows.h>
#	include <gl/gl.h>
//#	include <gl/glew.h>
#	include <gl/glext.h>
#	include <gl/glu.h>
//#	include <gl/wglew.h>
#elif defined( __linux__ )
#	error "Not for Linux (yet)."
#else
#	error "Unknown platform."
#endif

typedef HGLRC HANDLE_RENDER_CONTEXT;
typedef HDC   HANDLE_DEVICE_CONTEXT;
typedef HWND  HANDLE_WINDOW;

typedef unsigned int  uint;
typedef unsigned long ulong;

// http://www.swiftless.com/tutorials/opengl4/1-opengl-window.html
// g++ main.cpp context.cpp -lopengl32 -lglu32 -lglew32 -mwindows

namespace mmx {
	namespace opengl {

		class Context {
		public:
			Context();                       // Default constructor
			Context(HANDLE_WINDOW hwnd);     // Constructor for creating our context given a hwnd

			~Context();                      // Destructor for cleaning up our application
			
			bool create(HANDLE_WINDOW hwnd); // Creation of our OpenGL 3.x context
			void setupScene();               // All scene information can be setup here
			void resize(int w, int h);       // Method to get our window width and height on resize
			void render();                   // Render scene (display method from previous OpenGL tutorials)

		protected:
			HANDLE_RENDER_CONTEXT 	hrc;
			HANDLE_DEVICE_CONTEXT 	hdc;
			HANDLE_WINDOW			hwindow;
			
		private:
			uint window_width;
			uint window_height;
		};
		
	}		// ~namespace opengl
}           // ~namespace mmx

#endif	    // ~MMX_OPENGL_CONTEXT_HPP
