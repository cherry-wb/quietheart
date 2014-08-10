#include "include/md5digest.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

void PrintMD5Digest(const string &str, MD5Digest &md5digest)
{
	cout << "MD5Digest(\"" << str << "\") = " << md5digest.digest() << endl;
}

int main(int argc, char *argv[])
{

	//string digest usage:
	char *str = "abc";
	string strDigest = MD5Digest(str).digest();
	cout << "MD5Digest(\""<<str<<"\")="<<strDigest<< endl;

	//file digest usage:
	char *filename = "mytest.txt";
	ifstream ifile(filename);
	string fileDigest = MD5Digest(ifile).digest();
	cout <<"MD5Digest(ifstream(\""<< filename << ")\")="<<fileDigest<< endl;

	/*other api usage:
	we should use MD5Digest::reset() before MD5Digest::update() or the result will unexpected.
	*/
	MD5Digest md5digest;
	md5digest.set("");
	PrintMD5Digest("", md5digest);

	md5digest.set("a");
	PrintMD5Digest("a", md5digest);

	md5digest.set("bc");
	PrintMD5Digest("abc", md5digest);

	ifstream ifile2("mytest.txt");
	md5digest.set(ifile2);
	PrintMD5Digest("ifstream(mytest.txt)", md5digest);

	return EXIT_SUCCESS;
}
