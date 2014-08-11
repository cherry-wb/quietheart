#!/usr/bin/python
ch = 'a'
ascii_code = ord(ch)
print ascii_code

hex_code = "%02x" %ascii_code
print hex_code

chara = chr(ascii_code)
#chara = chr(hex_code) #error
print chara

ascii_code_str = str(ascii_code)
print ascii_code_str

ascii_code_num = int(ascii_code_str)
print ascii_code_num
