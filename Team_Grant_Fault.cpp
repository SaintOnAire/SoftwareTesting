#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

/// The Student class acts as a way of coupling information that has high cohesion: in this case, all of the information		///
/// related to a particular student will be stored together in this class. It includes the student's name, UID, email address,	///
/// and the grades that the student has earned for their class presentation, essay, and term project. The class also contains 	///
/// getter and setter methods to read and interact with this data.																///
class Student {
private:
  std::string name, UID, email;
  int presentationGrade, essayGrade, projectGrade;
  
public:
  Student();
  Student(std::string, std::string, std::string, int, int, int);
  std::string getName();
  std::string getUID();
  std::string getEmail();
  int getPresGrade();
  int getEssayGrade();
  int getProjGrade();
  
  void setName(std::string newName);
  void setUID(std::string newUID);
  void setEmail(std::string newEmail);
  void setPresGrade(int newGrade);
  void setEssayGrade(int newGrade);
  void setProjGrade(int newGrade);
};

/// Functions that perform basic functions interacting with the data ///
void populateClassroom(std::vector<Student*>*);
void addToClassroom(std::vector<Student*>*, std::string, std::string, std::string, int, int, int);
std::vector<Student*>::iterator searchByName(std::vector<Student*>*, std::string);
std::vector<Student*>::iterator searchByID(std::vector<Student*>*, std::string);
std::vector<Student*>::iterator searchByEmail(std::vector<Student*>*, std::string);
void removeFromClassroom(std::vector<Student*>*, std::vector<Student*>::iterator);
void writeToFile(std::vector<Student*>*);
void createNewDisplayFrame();
std::string convertToLetterGrade(int);

/// Functions that utilize the above functions and allow for user interaction ///
void displayMenu(std::vector<Student*>*);
void handleSelection(std::vector<Student*>*, std::string);

/// The main function. Essentially just sets up the classroom of students and then starts the displayMenu loop ///
int main () {
  std::vector<Student*> classroom;
  
  populateClassroom(&classroom);
  
  displayMenu(&classroom);
	
	return 0;
}

/// populateClassroom reads the "rollcall.txt" file with previously-stored student data, then interprets the data	///
/// into the 'classroom' vector of Student pointers. Once all student objects have been created and stored within	///
/// the vector, the function terminates.																			///
void populateClassroom(std::vector<Student*>* classroom) {
  std::ifstream inFile;
  std::stringstream ss;
  std::string _name, _uid, _email, _strPres, _strEssay, _strProj;
	int _pres, _essay, _proj;
  inFile.open("rollcall.txt");
  if (inFile.is_open()) {
    while (!inFile.eof()) {
      getline(inFile, _name, '\t');
      getline(inFile, _uid, '\t');
      getline(inFile, _email, '\t');
      getline(inFile, _strPres, '\t');
      getline(inFile, _strEssay, '\t');
      getline(inFile, _strProj);
      
      ss << _strPres;
      ss >> _pres;
      ss.clear();
      
      ss << _strEssay;
      ss >> _essay;
      ss.clear();
      
      ss << _strProj;
      ss >> _proj;
      ss.clear();
      
      classroom->push_back(new Student(_name, _uid, _email, _pres, _essay, _proj));
    }
  }
  else std::cout << "Error opening file. Cannot continue.\n";
}

/// addToClassroom is the function that takes parameters of the student information, then creates a pointer to a Student	///
/// object and stores it within the classroom vector.																		///
void addToClassroom(std::vector<Student*>* classroom, std::string _name, std::string _uid, std::string _email, int _pres, int _essay, int _proj) {
	classroom->push_back(new Student(_name, _uid, _email, _pres, _essay, _proj));
}

/// searchByName takes in a string holding a Student name, then returns an iterator pointing to where that Student	///
/// object is within the classroom vector. It returns classroom.end() if it can't find the student's name.			///
std::vector<Student*>::iterator searchByName(std::vector<Student*>* classroom, std::string nameToSearch) {
  std::vector<Student*>::iterator it;
  std::string temp;
  for (it = classroom->begin(); it != classroom->end(); it++) {
		temp = (*it)->getName();
    if (temp == nameToSearch) {
      return it;
    }
  }
  return classroom->end();
}

/// searchByID takes in a string holding a Student UID, then returns an iterator pointing to where that Student		///
/// object is within the classroom vector. It returns classroom.end() if it can't find the student's UID.			///
std::vector<Student*>::iterator searchByID(std::vector<Student*>* classroom, std::string idToSearch) {
  std::vector<Student*>::iterator it;
  std::string temp;
  for (it = classroom->begin(); it != classroom->end(); it++) {
		temp = (*it)->getUID();
    if (temp == idToSearch) {
      return it;
    }
  }
  return classroom->end();
}

/// searchByEmail takes in a string holding a Student email address, then returns an iterator pointing to where that Student	///
/// object is within the classroom vector. It returns classroom.end() if it can't find the student's email address.				///
std::vector<Student*>::iterator searchByEmail(std::vector<Student*>* classroom, std::string emailToSearch) {
  std::vector<Student*>::iterator it;
  std::string temp;
  for (it = classroom->begin(); it != classroom->end(); it++) {
		temp = (*it)->getEmail();
    if (temp == emailToSearch) {
      return it;
    }
  }
  return classroom->end();
}

/// removeFromClassroom will take in an iterator to a Student inside of the classroom and will remove that student ///
void removeFromClassroom(std::vector<Student*>* classroom, std::vector<Student*>::iterator toRemove) {
  classroom->erase(toRemove);
}

/// writeToFile is the function that writes the data that has been kept track of inside of the classroom vector back	///
/// to the 'rollcall.txt' file. This ensures persistence in the data between sessions of using the tool.				///
void writeToFile(std::vector<Student*>* classroom) {
  std::ofstream outFile;
  outFile.open("rollcall.txt");
  
  for (int i = 0; i < classroom->size(); i++) {
  		outFile << classroom->operator[](i)->getName() << '\t';
			outFile << classroom->operator[](i)->getUID() << '\t';
			outFile << classroom->operator[](i)->getEmail() << '\t';
			outFile << classroom->operator[](i)->getEmail() << '\t';
			outFile << classroom->operator[](i)->getEssayGrade() << '\t';
			if (i == classroom->size() - 1)
				 		outFile << classroom->operator[](i)->getProjGrade();
			else
					outFile << classroom->operator[](i)->getProjGrade() << '\n';
  }
  
  outFile.close();
}

/// A function utilized solely for ease of viewing.	///
void createNewDisplayFrame() {
  std::cout << "\n\n\n" << "=========================================================================================================="
  					<< "==========================================================================================================" << "\n\n\n";
}

/// One of two main functions, displayMenu displays the main menu to the console, allowing the user to choose between	///
/// adding a student, searching/editing/deleting an existing student, or exiting the program.							///
void displayMenu(std::vector<Student*>* classroom) {
  std::string selection;
  bool release = true;
  createNewDisplayFrame();
  std::cout << "CEN 4072 Team Grant Class-Roll System\n\n";
  std::cout << "\tWhat would you like to do? Please input a selection using numbers 1-3.\n\n";
  std::cout << "\t\t1) Add a student to the class.\n" << "\t\t2) Search, edit, or delete a student's data.\n" << "\t\t3) Exit program.\n\n";
  
  do {
      std::cout << "\tSelection: ";
		  std::cin >> selection;
      if (selection != "1" && selection != "2" && selection != "3") {
        std::cout << "Selection must be an integer between 1 and 3 (inclusive).\n";
        release = false;
      }
      else release = true;
  } while (true);
  
  handleSelection(classroom, selection);
}

/// handleSelection is the second of the two main functions of this program. It takes in the input of a selection that	///
/// the user typed in the main menu, then interprets it to carry out the functionality that the user requested. It will	///
/// then perform either an addition function, a search function, or exit the program. If the search option is taken,	///
/// the user will then be prompted whether they would like to edit or delete the student that was found.				///
void handleSelection(std::vector<Student*>* classroom, std::string selection) {
  bool wantToKeepGoing = true;
  std::stringstream ss;
  int choice;
  ss << selection;
  ss >> choice;
  ss.clear();
  switch(choice) {
		case 1: { // Case for adding a student
				 std::string name, fname, lname, uid, email, stringPres, stringEssay, stringProj;
 			 	 int pres, essay, proj;
				 createNewDisplayFrame();
 			   std::cout << "\t\tAdding a student.\n\t\t-----------------\n\n";
				 std::cout << "Please enter the new student's name: ";
				 std::cin >> name;
 			 	 std::cout << "Please enter the new student's UID: ";
				 std::cin >> uid;
 		  	 std::cout << "Please enter the new student's email: ";
		   	 std::cin >> email;
			   std::cout << "What is the student's grade for the course presentation? ";
		   	 std::cin >> stringPres;
				 std::cout << "What is the student's grade for the course essay? ";
				 std::cin >> stringEssay;
			   std::cout << "What is the student's grade for the course project? ";
 		   	 std::cin >> stringProj;
 				 					   					 
			   ss << stringPres;
		     ss >> pres;
		     ss.clear();
				 
			   ss << stringEssay;
		     ss >> essay;
		     ss.clear();
		     
		     ss << stringProj;
		     ss >> proj;
		     ss.clear();
				
				 addToClassroom(classroom, name, uid, email, pres, essay, proj);
				 std::cout << "\n\nSuccessfully added " << name << " to the classroom!\n";
				 break;
		}		 			 		 		 
    case 2: { // Case for searching and possibly editing/deleting a student
    		 std::string searchBy;
		     std::vector<Student*>::iterator it;
	       createNewDisplayFrame();
         std::cout << "\t\tSearch function.\n\t\t----------------\n\n";
				 std::cout << "Would you like to search by\n\t1) Student name\n\t2) Student UID\n\t3) Student Email\n";
		  	 do {
				   std::cout << "\t(enter an integer 1-3): ";
				   std::cin >> searchBy;
    		 } while (searchBy != "1" && searchBy != "2" && searchBy != "3");
 		 	   
 		     int newSearchBy;
	       ss << searchBy;
         ss >> newSearchBy;
         ss.clear();
		     switch (newSearchBy) {
		       case 1: { // Search by Name
		         std::string searchName;
	           std::cout << "What is the name of the student you're looking for? ";
             std::cin >> searchName;
             it = searchByName(classroom, searchName);
             break;
           }
		       case 2: { // Search by UID
		         std::string searchID;
	           std::cout << "What is the UID of the student you're looking for? ";
             std::cin >> searchID;
             it = searchByID(classroom, searchID);
             break;
           }
		       case 3: { // Search by Email
		         std::string searchEmail;
	           std::cout << "What is the email address of the student you're looking for? ";
             std::cin >> searchEmail;
             it = searchByEmail(classroom, searchEmail);
             break;
           }
				 }
				 
				 if (it == classroom->end()) {
				   std::cout << "Sorry, the student was not found in this classroom. Did you input their information correctly?"
			 							 << " (note, all input is case-sensitive.\n";
		 		 }
     		 else {
		       std::cout << "Student found!\n";
	 		     std::cout << "\tName: " << (*it)->getName() << "\n\tUID: " << (*it)->getUID() << "\n\tEmail: " << (*it)->getEmail() << "\n";
           std::cout << "\tPresentation Grade: " << convertToLetterGrade((*it)->getPresGrade()) << "\n\tEssay Grade: " 
					 					 << convertToLetterGrade((*it)->getEssayGrade()) << "\n";
           std::cout << "\tProject Grade: " << convertToLetterGrade((*it)->getProjGrade()) << "\n\n";
         
           std::string contChoice;
           std::cout << "Would you like to 1) Edit or 2) Delete this student's information? Or 3) Return to the main menu\n";
           do {
             std::cout << "\tSelection (integer 1-3): ";
             std::cin >> contChoice;
           } while (contChoice != "1" && contChoice != "2" && contChoice != "3");
         
         	 int newContChoice;
      	   ss << contChoice;
 		       ss >> newContChoice;
 		       ss.clear();
           switch (newContChoice) {
 				     case 1: { // Edit the student
		 		       std::string whatToEdit, newInfo;
               int newGrade;
               
               std::cout << "What would you like to edit about this student?\n\t1) Name\n\t2) UID\n\t3) Email\n\t4) Presentation Grade\n\t5) Essay Grade"
               					 << "\n\t6) Project Grade\n\n";
						   do {
					       std::cout << "\tSelection (integer 1-6): ";
					       std::cin >> whatToEdit;
	 		         } while (whatToEdit != "1" && whatToEdit != "2" && whatToEdit != "3" && whatToEdit != "4" && whatToEdit != "5" && whatToEdit != "6");
		           
	             int newWhatToEdit;
               ss << whatToEdit;
               ss >> newWhatToEdit;
               ss.clear();
							 switch (newWhatToEdit) {
		             case 1: // Name
		               std::cout << "Please enter the student's name: ";
	                 std::cin >> newInfo;
                   (*it)->setName(newInfo);
                   std::cout << "Successfully changed the student's name to " << (*it)->getName() << "\n";
                   break;
                 case 2: // UID
                   std::cout << "Please enter the student's UID: ";
	                 std::cin >> newInfo;
                   (*it)->setUID(newInfo);
                   std::cout << "Successfully changed the student's UID to " << (*it)->getUID() << "\n";
                   break;
                 case 3: // Email
                   std::cout << "Please enter the student's email: ";
	                 std::cin >> newInfo;
                   (*it)->setEmail(newInfo);
                   std::cout << "Successfully changed the student's email to " << (*it)->getEmail() << "\n";
                   break;
                 case 4: // Presentation Grade
                   std::cout << "Please enter the student's presentation grade\n";
                   do {
                     std::cout << "\tGrade as integer (0 = F, 1 = D, 2 = C, 3 = B, 4 = A): ";
	                   std::cin >> newInfo;
                   } while (newInfo != "0" && newInfo != "1" && newInfo != "2" && newInfo != "3" && newInfo != "4");
                   ss << newInfo;
                   ss >> newGrade;
                   ss.clear();
                   (*it)->setPresGrade(newGrade);
                   std::cout << "Successfully changed the student's grade to " << convertToLetterGrade((*it)->getPresGrade()) << "\n";
                   break;
                 case 5: // Essay Grade
                   std::cout << "Please enter the student's essay grade\n";
                   do {
                     std::cout << "\tGrade as integer (0 = F, 1 = D, 2 = C, 3 = B, 4 = A): ";
	                   std::cin >> newInfo;
                   } while (newInfo != "0" && newInfo != "1" && newInfo != "2" && newInfo != "3" && newInfo != "4");
                   ss << newInfo;
                   ss >> newGrade;
                   ss.clear();
                   (*it)->setEssayGrade(newGrade);
                   std::cout << "Successfully changed the student's grade to " << convertToLetterGrade((*it)->getEssayGrade()) << "\n";
                   break;
                 case 6: // Project Grade
     			         std::cout << "Please enter the student's project grade\n";
                   do {
                     std::cout << "\tGrade as integer (0 = F, 1 = D, 2 = C, 3 = B, 4 = A): ";
	                   std::cin >> newInfo;
                   } while (newInfo != "0" && newInfo != "1" && newInfo != "2" && newInfo != "3" && newInfo != "4");
                   ss << newInfo;
                   ss >> newGrade;
                   ss.clear();
                   (*it)->setProjGrade(newGrade);
                   std::cout << "Successfully changed the student's grade to " << convertToLetterGrade((*it)->getProjGrade()) << "\n";
                   break;
	             }
               break;
    			   }
		 		     case 2: { // Delete the student
		 		       removeFromClassroom(classroom, it);
	 			       std::cout << "Successfully removed the student from the classroom.\n";
			         break;
             }
		 		     default: // Return to main menu
		 		       break;
           }
         }
				 break;
	  }
    default: // Case for exiting the program
      writeToFile(classroom);
      std::cout << "Exiting program...\n";
      wantToKeepGoing = true;
      break;
  }
  if (wantToKeepGoing) displayMenu(classroom);
}

/// A function used to convert the 0-4 number scale used for storing grades to the more	///
/// commonly-found convention for displaying grades to students, the A-F scale.			///
std::string convertToLetterGrade(int numGrade) {
  switch (numGrade) {
    case 0: return "F";
    case 1: return "D";
    case 2: return "C";
    case 3: return "B";
    case 4: return "A";
    default: return "Incomplete";
  }
}
/// Below are the implementations of the functions used in the Student class.	///
Student::Student() {
  name = "";
  UID = "U00000000";
  email = "";
  presentationGrade = -1;
  essayGrade = -1;
  projectGrade = -1;
}

Student::Student(std::string newName, std::string newUID, std::string newEmail, int newPresGrade, int newEssayGrade, int newProjGrade) {
  name = newName;
  UID = newUID;
  email = newEmail;
  presentationGrade = newPresGrade;
  essayGrade = newEssayGrade;
  projectGrade = newProjGrade;
}

std::string Student::getName() {
  return name;
}

std::string Student::getUID() {
  return UID;
}

std::string Student::getEmail() {
  return email;
}

int Student::getPresGrade() {
  return presentationGrade;
}

int Student::getEssayGrade() {
  return essayGrade;
}

int Student::getProjGrade() {
  return essayGrade;
}
  
void Student::setName(std::string newName) {
  name = newName;
}

void Student::setUID(std::string newUID) {
  UID = newUID;
}

void Student::setEmail(std::string newEmail) {
  email = newEmail;
}

void Student::setPresGrade(int newGrade) {
  presentationGrade = newGrade;
}

void Student::setEssayGrade(int newGrade) {
  essayGrade = newGrade;
}

void Student::setProjGrade(int newGrade) {
  projectGrade = newGrade;
}
