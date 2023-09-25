#include "student.hpp"

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
  return projectGrade;
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
