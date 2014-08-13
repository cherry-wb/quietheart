/*程序功能:编写一个简单的支持多语言的程序。
 *
 * */
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define _(STRING)    gettext(STRING)

int main(void)
{
  setlocale( LC_ALL, "" );
  bindtextdomain( "hello", "/usr/share/locale" );
  textdomain( "hello" );
  printf(_( "Hello, world!\n" ));
  exit(0);
}

