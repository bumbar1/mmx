#include "context.hpp"

namespace opengl {

	Context::Context() {}
	
	Context::Context(HANDLE_WINDOW hwnd) {
	
	}
	
	Context::~Context() {
		wglMakeCurrent(hdc, 0);  // remove the rendering context from our device context  
		wglDeleteContext(hrc);   // delete our rendering context  
		  
		ReleaseDC(hwindow, hdc); // release the device context from our window  
	}

	
	bool Context::create(HANDLE_WINDOW hwnd) {
		hwindow = hwnd;
  
		hdc = GetDC(hwindow); // Get the device context for our window  
		
		PIXELFORMATDESCRIPTOR pfd;
		
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD
		
		return true;
	}
}		// ~namespace opengl
