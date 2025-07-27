-- Dropping tables if they exist
DROP TABLE IF EXISTS StudentDetails;
DROP TABLE IF EXISTS SubjectDetails;
DROP TABLE IF EXISTS MarksheetDetails;
GO

-- Creating StudentDetails table
CREATE TABLE StudentDetails (
    RollNo INT NOT NULL,
    StudentName VARCHAR(100),
    PRIMARY KEY (RollNo)
);

-- Creating SubjectDetails table
CREATE TABLE SubjectDetails (
    SubjectId INT NOT NULL,
    SubjectName VARCHAR(100),
    PRIMARY KEY (SubjectId)
);

-- Creating MarksheetDetails table
CREATE TABLE MarksheetDetails (
    RollNo INT NOT NULL,
    SubjectId INT NOT NULL,
    Marks FLOAT,
    FOREIGN KEY (RollNo) REFERENCES StudentDetails(RollNo),
    FOREIGN KEY (SubjectId) REFERENCES SubjectDetails(SubjectId)
);
--Inserting Data into Tables
-- Inserting students
INSERT INTO StudentDetails (RollNo, StudentName) VALUES
(1, 'SARFRAJ'),
(2, 'UDIT'),
(3, 'SOHEAL');

-- Inserting subjects
INSERT INTO SubjectDetails (SubjectId, SubjectName) VALUES
(101, 'MATHS'),
(102, 'C++'),
(103, 'DSA');

-- Inserting marks
INSERT INTO MarksheetDetails (RollNo, SubjectId, Marks) VALUES
(1, 101, 88),
(1, 102, 78),
(1, 103, 92),
(2, 101, 82),
(2, 102, 88),
(3, 101, 90),
(3, 103, 86);
