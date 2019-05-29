# [Inheritance]The Person, Student, Employee...

# The Person, Student, Employee, Faculty and Staff Class

# Description
<p>Design a class named <strong>Person</strong> and its two derived classes named <strong>Student</strong> and <strong>Employee</strong>. Make <strong>Faculty</strong> and <strong>Staff</strong> derived classes of <strong>Employee</strong>.<br />
Person class has the following member:<br />
&nbsp; string name;<br />
&nbsp; string address;<br />
&nbsp; string phoneNumber;<br />
&nbsp; string email;<br />
Student class has the following member:<br />
&nbsp; enum class_status{frssman,sophomore,junior,senior};&nbsp; <br />
&nbsp; class_status status;<br />
Employee class has the following member:<br />
&nbsp; string office;<br />
&nbsp; int salary;<br />
&nbsp; MyDate dateHired;<br />
Faculty class has the following member:<br />
&nbsp; string officeHours;<br />
&nbsp; int rank;<br />
Staff class has the following member:<br />
&nbsp; string title;<br />
MyDate class contains the following member: <br />
&nbsp; int year;<br />
&nbsp; int month;<br />
&nbsp; int day;<br />
<br />
Override the toString function in each class to display the class name.<br />
For example, in Employee class:<br />
string toString()<br />
{<br />
&nbsp; return &quot;Employee&quot;;<br />
}</p>
<p>Make sure that the following code: <br />
&nbsp; void f(Person &amp;p)<br />
&nbsp; {<br />
&nbsp;&nbsp;&nbsp; cout &lt;&lt; p.toString() &lt;&lt; endl;<br />
&nbsp; }</p>
<p>&nbsp; Person person;<br />
&nbsp; Student student;<br />
&nbsp; Employee employee;<br />
&nbsp; Faculty faculty;<br />
&nbsp; Staff staff;<br />
&nbsp; f(person);<br />
&nbsp; f(student);<br />
&nbsp; f(employee);<br />
&nbsp; f(faculty);<br />
&nbsp; f(staff);<br />
<br />
output:<br />
&nbsp; Person<br />
&nbsp; Student<br />
&nbsp; Employee<br />
&nbsp; Faculty<br />
&nbsp; Staff<br />
&nbsp;&nbsp;</p>

# Input


# Output


# Sample_Input
```

```

# Sample_Ouput
```

```

# Hint


