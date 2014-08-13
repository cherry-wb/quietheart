#ifndef __MYMACRO_APPEND_H
#define __MYMACRO_APPEND_H
#define PLUGIN_FUNC_DECL(myfunc) \
void plugin_##myfunc();

#define PLUGIN_FUNC_CALL(myfunc)\
do\
{\
plugin_##myfunc();\
}while(0)

#define PLUGIN_FUNC_IMPL(myfunc)\
void plugin_##myfunc()\
{\
	cout<<__PRETTY_FUNCTION__<<endl;\
}
#endif
