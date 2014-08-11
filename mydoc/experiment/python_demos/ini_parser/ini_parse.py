#!/usr/bin/python

'''
This module show how to operate the '.ini' config file.
Contents of myfile.cfg
#myfile.cfg
[DEFAULT]
thekey=thevalue0
#the [DEFAULT] section's value can be referenced by %(...)s from other section if it doesn't has.

[Section1]
int=15 ;int value is 15, which can use 'int:15'
bool=true ;internal line comment use ';' best behind a space.
float:3.1415 ;another way of <key>:<value> compare to <key>=<value>
baz=fun
bar=Python
foo=%(bar)s is %(baz)s! ;reference other key from the section, or [DEFAULT]
thekey1=%(thekey)s

[Section2]
thekey=thevalue2
thekey2=%(thekey)s
key21=value21
key22:value22
# comment can use '#' or ';'
'''
import ConfigParser

######create config file
#config = ConfigParser.SafeConfigParser() #no [DEFAULT] section
config = ConfigParser.SafeConfigParser({'thekey': 'thevalue0'}) #give [DEFAULT] section value

#config.add_section('DEFAULT') #compile error, cann't add this section!

config.add_section('Section1')
config.set('Section1', 'int', '15')
config.set('Section1', 'bool', 'true')
config.set('Section1', 'float', '3.1415')
config.set('Section1', 'baz', 'fun')
config.set('Section1', 'bar', 'Python')
config.set('Section1', 'foo', '%(bar)s is %(baz)s!')
config.set('Section1', 'thekey1', '%(thekey)s')

config.add_section('Section2')
config.set('Section2', 'thekey', 'thevalue2')
config.set('Section2', 'thekey2', '%(thekey)s')
config.set('Section2', 'key21', 'value21')
config.set('Section1', 'key22', 'value22')

with open('myfile.cfg', 'wb') as configfile:
    config.write(configfile)

######read config file
config = ConfigParser.SafeConfigParser(
        {'bar': 'Life', 'baz': 'hard'},allow_no_value=True) #give additional default value by code.
config.read('myfile.cfg')
print config.get('Section1', 'foo') # "Python is fun!"
print config.get('Section1', 'thekey1') # "thevalue0" because have no thekey, so use [DEFAULT]
print config.get('Section2', 'thekey2') # "thevalue2" use section thekey not [DEFAULT]

print config.get('Section1', 'foo', 0) # expand:"Python is fun!"
print config.get('Section1', 'foo', 1) # not expand:"%(bar)s is %(baz)s!"

print config.get('Section1', 'foo', 0, {'bar': 'Documentation',
                                        'baz': 'evil'}) #specify default when get.
print config.sections() # return all sections' list, not contain [DEFAULT]
print config.options('Section2') # return Section2 keys' list.
print config.defaults() #return default key:value dict for all section reference.
print config.has_section('Section2') #True
print config.has_option('Section3', 'thekey2') #False

######change config not write to file
config.remove_option('Section1', 'bar')
config.remove_option('Section1', 'baz')
print config.get('Section1', 'foo') # "Life is hard!" remove ,but file not change.

######advanced
def opt_move(config, section1, section2, option):
    try:
        config.set(section2, option, config.get(section1, option, 1))
    except ConfigParser.NoSectionError:
        config.add_section(section2)
        opt_move(config, section1, section2, option)
    else:
        config.remove_option(section1, option)

opt_move(config,'Section1', 'Section2', 'bool')
print config.get('Section2', 'bool') # "true" 
