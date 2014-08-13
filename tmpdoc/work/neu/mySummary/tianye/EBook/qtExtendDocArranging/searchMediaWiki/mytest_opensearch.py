#!/usr/bin/python
#Search "mytest" maximum count is 2.
import query
params = {
	'action'    :'opensearch',
	'search'    :'mytest',
	'limit'     :'5',
	'rvlimit'   :'2',
	'rvprop'    :'user|timestamp|content',
}

print query.GetData(params, encodeTitle = False)
