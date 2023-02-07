# File-Management
📒This is a our assignments for File Management and processing using 
<b>C++ programming language</b>

<h2>First assignment: </h2>
Want to store data about Employees and Department. (for simplicity consider any employee belongs to only one department, 
but any department may have more than one employee).
Save the data for employees and department in the following format: delimited fields, length indicator records.
You should write the producers that build the following indexes:<br>
1. Primary index using the Employee_ID (for Employees datafile)<br>
2. Primary index using the Dept_ID (for Department datafile)<br>
3. Secondary index using Dept_ID (for Employee datafile) //Dept _ID is sec. key in Employees datafile<br>
4. Secondary index using Dept_Name (for Department datafile)<br>

### The user can write a query that contains fixed key words 

<h2>Some test cases: </h2>

![image](https://user-images.githubusercontent.com/101058082/217084120-cdfbb7d5-1359-4dcc-80a9-c61e72ee07a4.PNG)<br>
***Test case to show adding a new employee on the right after adding the employee's first 10 characters are the file header, there are 3 characters after the header that are the length indicator record, after that there are employee's data.*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217106443-9f786124-ccc6-4be1-bb50-8be91a6bdf7e.PNG)<br>
***Test case to show search using primary index and binary search.*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217106176-ed23e212-5dd5-4a9c-a676-d2c8a12ad810.PNG)<br>
***Test case to delete employee using linked list.*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217107101-5b8dd8db-17e7-4ec3-837a-c8bc19d061d5.PNG)<br>
***Test case to show search after delete.*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217105766-6a03c2c2-604d-47da-aa6b-af14c247aa74.PNG)<br>
***Test case to show adding a new department.*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217107274-7286aa7d-2972-4dbc-83da-915824677c54.PNG)<br>
***Query writing test.*** <br><br>


<h2>Second assignment: </h2>
Program that create, store and manipulate a set of n fixed-length records as B-tree index 
on a binary file. Each record consists of m descendants (m records IDs and m references to the actual 
records on a data file) + 1 integer to indicate leaf/no leaf status (The first integer of each node, 0→
means a leaf node, 1 → a non-leaf node).

![image](https://user-images.githubusercontent.com/101058082/217287811-a5360e8d-f133-4bf2-ad00-67af1d8492e2.PNG)<br>
***The file at creation time (if number of records = 10 and m= 5).*** <br><br>
![image](https://user-images.githubusercontent.com/101058082/217288138-cc3f9752-8ff9-4d03-9cfb-9a677802f837.PNG)<br>
***The index file after inserting.*** <br><br>