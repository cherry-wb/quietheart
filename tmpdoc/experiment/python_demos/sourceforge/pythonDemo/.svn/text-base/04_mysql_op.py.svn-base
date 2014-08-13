#!/usr/bin/python
#ubuntu 11.10
#*apt-get install mysql-server
#*apt-get install python-mysqldb
#more information:http://mysql-python.sourceforge.net/MySQLdb.html

import MySQLdb

###connect to databases
conn = MySQLdb.connect(host='localhost', user='root', passwd='12345678')

###create database
cursor = conn.cursor()
command = 'create database quietheart;'
cursor.execute(command)
cursor.close()

###select database and create tables(two ways)
cursor = conn.cursor()
conn.select_db('quietheart')
command = 'create table test1(id int, info varchar(50));'
cursor.execute(command)
cursor.close()

cursor = conn.cursor()
command = 'use quietheart;'
cursor.execute(command)
command = 'create table test2(id int, info varchar(50));'
cursor.execute(command)
cursor.close()

###insert values
cursor = conn.cursor()
paramValue = [1,"infor1"]
command = 'insert into test1 values(%s,%s)' #with sequence '%s' must be used.
cursor.execute(command,paramValue)

cursor = conn.cursor()
paramValue = {"id":"2","info":"info2"}
command = 'insert into test1 values(%(id)s,%(info)s)' #with dict '%(key)s' must be used.
cursor.execute(command,paramValue)

cursor = conn.cursor()
paramValues = []
for i in range(20):  
    paramValues.append((i,'record' + str(i)))  
command = 'insert into test2 values(%s,%s)' #with multi executes
cursor.executemany("""insert into test2 values(%s,%s) """,paramValues);  
cursor.close();

###select values
cursor = conn.cursor()
command = 'select * from test2'
count = cursor.execute(command)
print "return %d records." % count

#fetch all record
results = cursor.fetchall() #start from first no matter fetch before.
for r in results:
    print r

#fetch five records.
cursor.scroll(0,mode='absolute') #scroll to offset 0. mode='abaolute'|'relative',default 'relative'.
results = cursor.fetchmany(5)
for r in results:
    print r

#fetch each record.
result = cursor.fetchone(); #cursor start from 5th, because of the previous fetch. 
while result != None:
    print result  
    print 'id:%s, info:%s' % result   
    result = cursor.fetchone();  
    cursor.close();

#select and return dict
dictcursor = conn.cursor(cursorclass=MySQLdb.cursors.DictCursor)
command = 'select * from test2'
dictcursor.execute(command)
result = dictcursor.fetchone();  
print result
dictcursor.close();


#update
cursor = conn.cursor()
command = 'update test1 set info="hi" where id=1;'
count = cursor.execute(command)
cursor.close();


###drop tables and database
cursor = conn.cursor()
command = 'drop table test1;'
cursor.execute(command)
cursor.close()

cursor = conn.cursor()
command = 'drop table test2;'
cursor.execute(command)
cursor.close()

cursor = conn.cursor()
command = 'drop database quietheart;'
cursor.execute(command)
cursor.close()

