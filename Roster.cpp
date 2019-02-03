#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return numStudents; // stub
}

Student Roster::getStudentAt(int index) const { 
  return *(students[index]); 
}

std::string Roster::toString() const {
  std::string result = "{\n";
  for (int i = 0; i < (numStudents - 1); i++) {
	result += (getStudentAt(i)).toString();
	result += ",\n";
  }
  result += (getStudentAt(numStudents-1)).toString();
  result += "\n}\n";
  return result;

}

void Roster::sortByPerm() {
	for (int i = numStudents; i > 0; i--) {
		sortByPermHelper(i);
	}
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
	int maxIndex;
	maxIndex = 0;
	int maxPerm;
	maxPerm = (*(students[0])).getPerm();
	for (int i = 0; i < k; i++) {
		if ((*(students[i])).getPerm() > maxPerm) {
			maxIndex = i;
			maxPerm = (*(students[i])).getPerm(); 
		}
	}
	return maxIndex;
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]


  int im = indexOfMaxPermAmongFirstKStudents(k);
  Student* p1;
  p1 = students[im];
  students[im] = students[k-1];
  students[k-1] = p1;
  // now swap the pointers between index im and index k-1

  // THIS IS STILL A STUB !!!
  
}
