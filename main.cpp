
#include "CCanvas.hpp"


using namespace std;

int main(){


	CCanvas cvs(40, 20, ' ', 20);

	cvs.rect(10u, 5u, 10u, 10u, 'O');
	cvs.init();
	cvs.rect(0, 0, 4, 8, '!');
	while(true);

	return 0;
}
