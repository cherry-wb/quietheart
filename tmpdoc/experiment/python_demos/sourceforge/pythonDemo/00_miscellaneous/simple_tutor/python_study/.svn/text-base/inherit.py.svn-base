#!/usr/bin/python
# Filename: inherit.py

class SchoolMember:
	'''Represents any school member.'''
	def __init__(self, name, age):
		self.name = name
		self.age = age
		print '(Initialized SchoolMember: %s)' % self.name
	
	def tell(self):
		'''Tell my details.'''
		print 'Name : "%s" Age: "%s"' % (self.name, self.age),

class Teacher(SchoolMember):
	'''Respresents a teacher.'''
	def __init__(self, name, age, salary):
		SchoolMember.__init__(self, name, age)
		self.salary = salary
		print '(Initialized Teacher: %s)' % self.name
	
	def tell(self):
		SchoolMember.tell(self)
		print 'Salary: "%d"' % self.salary#"%d"have nothing just put""to the number

class Student(SchoolMember):
	'''Represents a student.'''
	def __init__(self, name, age, marks):
		SchoolMember.__init__(self, name, age)
		self.marks = marks
		print('Initialized Student: %s*********s***') % self.name
		#print('Initialized Student: "%s"*********s***') % self.name#ok?this output the result 'Initialized Student: "Swaroop"*********s***'

	def tell(self):
		SchoolMember.tell(self)
		print 'Marks: "%d***********d***"' %self.marks
		#print 'Marks: %d***********d***' %self.marks#ok?this output the results:' Marks: 75***********d***'

t = Teacher('Mrs. Shrividya', 40, 30000)
s = Student('Swaroop', 22, 75)

print #prints a blank line

members = [t, s ]
for member in members:
	member.tell()#works for both Teachers and Students
