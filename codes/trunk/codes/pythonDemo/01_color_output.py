#!/usr/bin/python
BG_DFG='0'
BG_BLACK='40'
BG_RED='41'
BG_GREEN='42'
BG_BLUE='46'
BG_WHITE='47'

FG_DFG='0'
FG_BLACK='30'
FG_RED='31'
FG_GREEN='32'
FG_BLUE='34'
FG_WHITE='37'

HIGHT_LIGHT='1'
UNDER_LINE='4'
FLASH='5'
NORMAL='22'

def colorStr(origStr, fgColor=FG_WHITE, bgColor=BG_BLACK, cursor=NORMAL):
    prefix = '\033[' + fgColor +';' + bgColor + ';' + cursor + 'm'
    suffix = '\033[0m'
    retStr = prefix + origStr + suffix
    return retStr

myStr = colorStr("hello",FG_RED, BG_BLUE)
print "red,blue: ",myStr
myStr = colorStr("hello",FG_GREEN, BG_BLACK)
print "green,black: ",myStr
myStr = colorStr("hello",FG_RED, BG_WHITE)
print "red,white: ",myStr
myStr = colorStr("hello",FG_WHITE, BG_BLACK)
print "white,black: ",myStr
myStr = colorStr("hello",FG_DFG, BG_DFG, HIGHT_LIGHT)
print "hightlight: ",myStr
