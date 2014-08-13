#!/usr/bin/python
#Search "mytest" in the title/text,maximum return count is 5.
import query
params = {
	'action'    :'query',
	'list'		:'search',
	'srwhat'    :'title',
	#'srwhat'    :'text',
	'srsearch'  :'*fix*',
	'srlimit'   :'5',
}

print query.GetData(params, encodeTitle = False)
