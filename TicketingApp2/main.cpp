#include "Classes.h"
using namespace std;

//tests
void deconstructorTest() {
	LocSeats deconstructThis("adress0", "named", 43, 2, 2);
	LocSeats copy(deconstructThis);
	cout << copy.getNoRows();
	cout << endl << copy.getArrSeats()[0][0]->getType();
	copy.addElementToArray();
	//LocSeats copycopy(copy);
	LocSeats copycopy(*LocSeats::getVectLoc()[0]);
	cout << copycopy.getNoRows();
	cout << endl << LocSeats::getVectLoc()[0]->getAddress();
	copy.removeElementFromArray();
	//cout << endl << copycopy.getArrSeats()[0][0]->getType();
	cout << endl; // << Location::getVectLoc()[3]->getAddress();
}
//end of tests
//
//


int main() {
	srand(time(0));
	
	//tests
	
	LocSeats no;
	LocSeats ls("adressd", "named", 43);
	cout << ls.getAddress();

	LocSeats ls2(ls);
	//cout << endl << ls2.getAddress();
	//ls2.addElementToArray();
	//cout << endl << LocSeats::getVectLoc()[0]->getAddress();

	//LocSeats ls3("adress0", "named", 43, 2, 2);
	//cout << endl << ls3.getArrSeats()[0][0]->getType();
	deconstructorTest();


	//end of tests
	//
	//
}