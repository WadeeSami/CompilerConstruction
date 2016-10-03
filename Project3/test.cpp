#include <iostream>
#include "scanner.h"
using namespace std;


int main() {
	FileDescriptor *fd = new FileDescriptor("example.txt");

	SCANNER scanner(fd);
	TOKEN * t = NULL;
	int i = 0;
	while (fd->GetCurrLine()!=NULL) {
		while ((t = scanner.Scan()) != NULL) {
			//cout << t->str_ptr ;
			cout <<++i<<"\t" << t->type << endl;
		}
	}
		
	int x = 0;
	cin >> x;
	return 0;
}