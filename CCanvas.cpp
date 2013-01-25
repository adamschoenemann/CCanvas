
#include "CCanvas.hpp"

using namespace std;

void CCanvas::rect(size_t x, size_t y, size_t W, size_t H, char val){
	CPixel pxl = {val};
	pthread_mutex_t mut;
	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);

	for(int r = y; r < y+H; r++){
		for(int c = x; c < x+W; c++){
			this->graphics[r][c] = pxl;
		}
	}

	pthread_mutex_unlock(&mut);
}


CCanvas::CCanvas(size_t W, size_t H, char ch = ' ', size_t FR = 30):
	width(W), height(H), defaultPixelChar(ch),
	frameRate(1000/FR), graphics(makePixels(W, H, ch))
{
	cout << "CCanvas initialized" << endl;
	cout << "width: " << width << endl;
	CPixelVector pxls = this->makePixels(width, height, defaultPixelChar);
	this->graphics = pxls;
//	this->init();
}

void CCanvas::draw(){
	system("CLS");
	this->coutPixels(this->graphics);
}

void* CCanvas::bootstrap(void* ctx){
	cout << "Bootstrapped";
	CCanvas* self = static_cast<CCanvas*>(ctx);

	while(true){
		self->draw();
		self->sleep(self->frameRate);
	}

}

void *print_width(void* ctx){
	CCanvas* self = static_cast<CCanvas*>(ctx);
	while(true) cout << "PRINT_WIDTH: " << self->width << endl;
}

void CCanvas::init(){


	int ret;
	void* ret_join;
	pthread_t drawThread;

	ret = pthread_create(&drawThread, NULL, CCanvas::bootstrap, this);
	pthread_detach(drawThread);
//	ret = pthread_join(drawThread, &ret_join);

}

void CCanvas::coutPixels(CPixelVector pxls){
	uint32_t R = pxls.size();
	uint32_t C = pxls[0].size();

	for(CPixelVector::size_type r = 0; r < R; r++){
		for(CPixelVector::size_type c = 0; c < C; c++){
			cout << pxls[r][c].val;
		}
		cout << endl;
	}


}


CPixelVector CCanvas::makePixels(size_t W, size_t H, char ch){
	CPixelVector pxls;
	pxls.resize(H);

	vector<CPixel> row;
	CPixel pxl = {ch};
	row.assign(W, pxl);

	for(CPixelVector::size_type r = 0; r < H; r++){
		pxls[r] = row;
	}

//	}
	return pxls;
}

void CCanvas::sleep(uint32_t dur){
	clock_t goal = dur + clock();
	while(goal > clock());
}
