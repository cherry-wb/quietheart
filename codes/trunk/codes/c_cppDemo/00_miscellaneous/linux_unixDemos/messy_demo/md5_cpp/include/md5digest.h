#ifndef MD5_H
#define MD5_H

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

/* Type define */
typedef unsigned char byte;
typedef unsigned long ulong;


/* MD5Digest declaration. */
class MD5Digest {
public:
	MD5Digest();
	MD5Digest(const void *input, size_t length);
	MD5Digest(const string &str);
	MD5Digest(ifstream &in);
	void set(const void *input, size_t length);
	void set(const string &str);
	void set(ifstream &in);
	string digest();

private:
	void reset();
	void update(const byte *input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const ulong *input, byte *output, size_t length);
	void decode(const byte *input, ulong *output, size_t length);
	string bytesToHexString(const byte *input, size_t length);

	/* class uncopyable */
	MD5Digest(const MD5Digest&);
	MD5Digest& operator=(const MD5Digest&);
private:
	ulong _state[4];	/* state (ABCD) */
	ulong _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const size_t BUFFER_SIZE = 1024;
};

#endif/*MD5Digest_H*/
