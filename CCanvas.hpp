#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#include <pthread.h>

using namespace std;

struct CPixel {
	char val;
};

struct PixelsArray {
	CPixel* pixels;
	int x;
	int y;
	int rows;
	int cols;
};

typedef vector<vector<CPixel>> CPixelVector;

class CCanvas {

	public:
		CCanvas(size_t, size_t, char, size_t);
		void init();
//		~CCanvas();
//		void setFrameRate();
		void rect(size_t, size_t, size_t, size_t, char);

		int width;
		int height;
		void draw();
		static void test(CCanvas* self){

			while(true) cout << "TEST: " << self->width;
		}
		CPixelVector getGraphics(){return this->graphics;}

	private:

		static void* bootstrap(void*);
		void coutPixels(CPixelVector);
		CPixelVector makePixels(size_t, size_t, char);
		void sleep(uint32_t);

		char defaultPixelChar;
		CPixelVector graphics;
		size_t frameRate;

};

// --------------------------- IMPLEMENTATIONS -------------------------------//



