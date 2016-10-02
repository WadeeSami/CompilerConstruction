#include <iostream>
#include "scanner.h"
using namespace std;


int main() {
	//cout << "wadee";
	FileDescriptor *fd = new FileDescriptor("example.txt");
   // cout << "wadee0";
	SCANNER scanner(fd);
	/*fd->GetCurrLine();
	for (int i = 0; i < 20; i++) {
		cout << fd->GetChar();
	}
	cout << endl;*/
	TOKEN * t = NULL;
	while (fd->GetCurrLine()) {
		while ((t = scanner.Scan()) != NULL) {
			//cout << t->str_ptr ;
			cout << t->type << endl;
		}
	}
		
	
	
	int x = 0;
	cin >> x;
	return 0;
}