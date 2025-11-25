#include "glad/glad.h"

namespace worldObject {
	namespace VAO {
		extern GLuint triangle;
		extern GLuint square;
		
		struct LayoutSruct {
			int strideOS;
			int ptr;
		};
	}

	namespace Pragram {
		extern GLuint triangle;
		extern GLuint square;
	}
}

class Layout {
public:
	int strideOS;
	int ptr;
	int strindeTexBegning;
};

namespace GlobalTexture {
	extern GLuint smileFace;
}