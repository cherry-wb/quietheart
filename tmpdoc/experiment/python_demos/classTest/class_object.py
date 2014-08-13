#!/usr/bin/python
#@classmethod
#def set_instance(cls,obj):
#	''' set the factory object instance.
#
#		'''
#		FactoryScenario.obj = obj 

class My:
	def __init__(self):
		pass
	
#	def get_instance(self):
#		one_instance = 1

	def set_obj(self,obj):
		self.m_obj = obj

	def my_print(self):
		print self.m_obj

class My2:
	obj = 1
	def __init__(self):
		pass
	def get_instance():
		return obj
	
	def set_obj(obj):
		My2.obj=obj

class SubMy(My):
	sm_obj = 5
	sm_dict = {"1":"a"}
	def __init__(self):
		My.__init__(self)

class SubSubMy(SubMy):
	sm_obj = 6
	sm_dict = {"2":"b"}
#*We can see the class and object info.
print "======class info======"
print "type(My):", type(My) #type(My): <type 'classobj'>
print "My.__bases__:",My.__bases__ #My.__bases__: ()
print "dir(My):", dir(My) #dir(My): ['__doc__', '__init__', '__module__', 'my_print', 'set_obj']
print "type(My).__name__:",type(My).__name__ #type(My).__name__: classobj
print "dir(SubMy):", dir(SubMy) #dir(SubMy): ['__doc__', '__init__', '__module__', 'my_print', 'set_obj', 'sm_obj']
print "SubMy.__bases__:",SubMy.__bases__ #SubMy.__bases__: (<class __main__.My at 0x7f4b84b0c050>,)
print
print "======object info======"
my = SubMy()
print "type(my):", type(my) #type(my): <type 'instance'>
print "my.__class__:", my.__class__ #my.__class__: __main__.SubMy
print "my.__class__.__name__:", my.__class__.__name__ #my.__class__.__name__: SubMy


#*We can change the object member type dynamically.
my.set_obj(2)
print my.m_obj.__class__
print my.m_obj.__class__.__name__
my.my_print()

my.set_obj("hello")
print my.m_obj.__class__
my.my_print()


#*We can also change the class member type dynamically.
my2=My2()
print My2.obj
My2.obj=2
if (isinstance(My2.obj, int)):
	print My2.obj
else:
	print "My2.obj is not 'int'"
My2.obj = my
if (isinstance(My2.obj, My)):
	print "My2.obj is My:",
	my.my_print()
else:
	print "My2.obj is not 'My'"

if (isinstance(My2.obj, SubMy)):
	print "My2.obj is SubMy:",
	my.my_print()
else:
	print "My2.obj is not 'SubMy'"

if (hasattr(SubMy,"sm_obj")):
	print "have sm_obj"
else:
	print "not have sm_obj"

my2.ooo = "test add member."
print my2.ooo

print "=============="
#exec "xx =  " + my.__class__.__name__ + ".sm_obj"
exec "classObj = " + my.__class__.__name__
print my.__class__.sm_obj

print hasattr(SubSubMy,"sm_obj")
print SubSubMy.sm_dict
print my.sm_obj
print my.sm_obj
print my.sm_obj
print my.sm_obj
subsubmy = SubSubMy()
print subsubmy.sm_obj
