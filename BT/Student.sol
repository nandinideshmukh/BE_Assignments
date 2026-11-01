
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract StudentData {

    // Structure to store student information
    struct Student {
        uint256 id;
        string name;
        uint256 age;
        string course;
    }

    // Array to store student records
    Student[] public students;

    // Counter for student IDs
    uint256 public studentCount;

    // Function to add a student
    function addStudent(
        string memory _name,
        uint256 _age,
        string memory _course
    ) public {
        studentCount++;

        students.push(
            Student(studentCount, _name, _age, _course)
        );
    }

    // Function to retrieve student details
    function getStudent(uint256 _index)
        public
        view
        returns (
            uint256,
            string memory,
            uint256,
            string memory
        )
    {
        require(_index < students.length, "Invalid student index");

        Student memory s = students[_index];

        return (s.id, s.name, s.age, s.course);
    }

    // Function to get total number of students
    function getStudentCount() public view returns (uint256) {
        return students.length;
    }
}
