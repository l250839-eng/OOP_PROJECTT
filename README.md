# 🏫 Academic Office Replacement System

## 📌 Overview
A terminal-based Academic Management System built using C++ and OOP principles. It replaces manual academic processes with an automated, file-based system.

---

## 🎯 Features
- Student, Teacher, and Course management
- Multiple student types (Regular, Scholarship, Exchange)
- Polymorphic grading system (Exam, Quiz, Assignment)
- Smart registration with capacity & conflict checking
- Teacher feedback system (rating + comments)
- Scheduling system with venue allocation
- File-based database for data persistence

---

## 🧱 Core Components
- **AcademicEntity**: Base class for all users  
- **Student / Teacher**: Derived user types  
- **Course**: Core, Elective, Lab courses  
- **Assessment**: Exam, Quiz, Assignment  
- **DatabaseManager**: Handles file I/O  
- **Scheduler**: Manages time slots & venues  

---

## 📁 Data Files
- Students.txt  
- Teachers.txt  
- Courses.txt  
- Venues.txt  
- sections.txt  
- assessments.txt  
- weightages.txt  

---

## 🛠️ Tech Stack
- C++
- OOP (Inheritance, Polymorphism, Abstraction)
- File Handling (TXT/CSV)
- STL

---

## 🚀 Goal
To simulate a real academic office system with automation, persistence, and smart scheduling.
