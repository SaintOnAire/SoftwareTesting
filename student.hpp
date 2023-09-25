#include <string>
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