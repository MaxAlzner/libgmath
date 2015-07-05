#ifndef ENCODE_H
#define ENCODE_H

#include <string.h>

typedef struct Encoded2Bytes
{

	inline Encoded2Bytes() : full(0) {}
	inline Encoded2Bytes(const unsigned __int16 x) : full(x) {}
	inline ~Encoded2Bytes() {}

	inline operator unsigned __int16() const { return this->full; }

	union
	{
		unsigned __int8 bytes[2];
		unsigned __int16 full;
	};

} Encoded2Bytes;

typedef struct Encoded4Bytes
{

	inline Encoded4Bytes() : full(0) {}
	inline Encoded4Bytes(const unsigned __int32 x) : full(x) {}
	inline ~Encoded4Bytes() {}

	inline operator unsigned __int32() const { return this->full; }

	union
	{
		unsigned __int8 bytes[4];
		unsigned __int16 words[2];
		unsigned __int32 full;
	};

} Encoded4Bytes;

typedef struct Encoded8Bytes
{

	inline Encoded8Bytes() : full(0) {}
	inline Encoded8Bytes(const unsigned __int64 x) : full(x) {}
	inline ~Encoded8Bytes() {}

	inline operator unsigned __int64() const { return this->full; }

	union
	{
		unsigned __int8 bytes[8];
		unsigned __int16 words[4];
		unsigned __int32 dwords[2];
		unsigned __int64 full;
	};

} Encoded8Bytes;

typedef struct Encoded16Bytes
{

	inline Encoded16Bytes() { memset(this, 0, sizeof(Encoded16Bytes)); }
	inline ~Encoded16Bytes() {}

	union
	{
		unsigned __int8 bytes[16];
		unsigned __int16 words[8];
		unsigned __int32 dwords[4];
		unsigned __int64 qwords[2];
	};

} Encoded16Bytes;

typedef struct Encoded32Bytes
{

	inline Encoded32Bytes() { memset(this, 0, sizeof(Encoded32Bytes)); }
	inline ~Encoded32Bytes() {}

	union
	{
		unsigned __int8 bytes[32];
		unsigned __int16 words[16];
		unsigned __int32 dwords[8];
		unsigned __int64 qwords[4];
	};

} Encoded32Bytes;

typedef struct Encoded64Bytes
{

	inline Encoded64Bytes() { memset(this, 0, sizeof(Encoded64Bytes)); }
	inline ~Encoded64Bytes() {}

	union
	{
		unsigned __int8 bytes[64];
		unsigned __int16 words[32];
		unsigned __int32 dwords[16];
		unsigned __int64 qwords[8];
	};

} Encoded64Bytes;

typedef struct Encoded128Bytes
{

	inline Encoded128Bytes() { memset(this, 0, sizeof(Encoded128Bytes)); }
	inline ~Encoded128Bytes() {}

	union
	{
		unsigned __int8 bytes[128];
		unsigned __int16 words[64];
		unsigned __int32 dwords[32];
		unsigned __int64 qwords[16];
	};

} Encoded128Bytes;

typedef struct Encoded256Bytes
{

	inline Encoded256Bytes() { memset(this, 0, sizeof(Encoded256Bytes)); }
	inline ~Encoded256Bytes() {}

	union
	{
		unsigned __int8 bytes[256];
		unsigned __int16 words[128];
		unsigned __int32 dwords[64];
		unsigned __int64 qwords[32];
	};

} Encoded256Bytes;

inline Encoded2Bytes EncodeByte(const unsigned __int8 c0, const unsigned __int8 c1)
{
	Encoded2Bytes b;
	b.bytes[0] = c0;
	b.bytes[1] = c1;
	return b;
}
inline Encoded4Bytes EncodeByte(const unsigned __int8 c0, const unsigned __int8 c1, const unsigned __int8 c2, const unsigned __int8 c3)
{
	Encoded4Bytes b;
	b.bytes[0] = c0;
	b.bytes[1] = c1;
	b.bytes[2] = c2;
	b.bytes[3] = c3;
	return b;
}

inline Encoded4Bytes EncodeWord(const unsigned __int16 c0, const unsigned __int16 c1)
{
	Encoded4Bytes b;
	b.words[0] = c0;
	b.words[1] = c1;
	return b;
}
inline Encoded8Bytes EncodeWord(const unsigned __int16 c0, const unsigned __int16 c1, const unsigned __int16 c2, const unsigned __int16 c3)
{
	Encoded8Bytes b;
	b.words[0] = c0;
	b.words[1] = c1;
	b.words[2] = c2;
	b.words[3] = c3;
	return b;
}
inline Encoded4Bytes EncodeWord(const Encoded2Bytes& b0, const Encoded2Bytes& b1)
{
	Encoded4Bytes b;
	b.words[0] = b0.full;
	b.words[1] = b1.full;
	return b;
}
inline Encoded8Bytes EncodeWord(const Encoded2Bytes& b0, const Encoded2Bytes& b1, const Encoded2Bytes& b2, const Encoded2Bytes& b3)
{
	Encoded8Bytes b;
	b.words[0] = b0.full;
	b.words[1] = b1.full;
	b.words[2] = b2.full;
	b.words[3] = b3.full;
	return b;
}

inline Encoded8Bytes EncodeDWord(const unsigned __int32 c0, const unsigned __int32 c1)
{
	Encoded8Bytes b;
	b.dwords[0] = c0;
	b.dwords[1] = c1;
	return b;
}
inline Encoded16Bytes EncodeDWord(const unsigned __int32 c0, const unsigned __int32 c1, const unsigned __int32 c2, const unsigned __int32 c3)
{
	Encoded16Bytes b;
	b.dwords[0] = c0;
	b.dwords[1] = c1;
	b.dwords[2] = c2;
	b.dwords[3] = c3;
	return b;
}
inline Encoded32Bytes EncodeDWord(const unsigned __int32 c0, const unsigned __int32 c1, const unsigned __int32 c2, const unsigned __int32 c3, const unsigned __int32 c4, const unsigned __int32 c5, const unsigned __int32 c6, const unsigned __int32 c7)
{
	Encoded32Bytes b;
	b.dwords[0] = c0;
	b.dwords[1] = c1;
	b.dwords[2] = c2;
	b.dwords[3] = c3;
	b.dwords[4] = c4;
	b.dwords[5] = c5;
	b.dwords[6] = c6;
	b.dwords[7] = c7;
	return b;
}
inline Encoded8Bytes EncodeDWord(const Encoded4Bytes& b0, const Encoded4Bytes& b1)
{
	Encoded8Bytes b;
	b.dwords[0] = b0.full;
	b.dwords[1] = b1.full;
	return b;
}
inline Encoded16Bytes EncodeDWord(const Encoded4Bytes& b0, const Encoded4Bytes& b1, const Encoded4Bytes& b2, const Encoded4Bytes& b3)
{
	Encoded16Bytes b;
	b.dwords[0] = b0.full;
	b.dwords[1] = b1.full;
	b.dwords[2] = b2.full;
	b.dwords[3] = b3.full;
	return b;
}

inline Encoded16Bytes EncodeQWord(const unsigned __int64 c0, const unsigned __int64 c1)
{
	Encoded16Bytes b;
	b.qwords[0] = c0;
	b.qwords[1] = c1;
	return b;
}
inline Encoded32Bytes EncodeQWord(const unsigned __int64 c0, const unsigned __int64 c1, const unsigned __int64 c2, const unsigned __int64 c3)
{
	Encoded32Bytes b;
	b.qwords[0] = c0;
	b.qwords[1] = c1;
	b.qwords[2] = c2;
	b.qwords[3] = c3;
	return b;
}
inline Encoded16Bytes EncodeQWord(const Encoded8Bytes& b0, const Encoded8Bytes& b1)
{
	Encoded16Bytes b;
	b.qwords[0] = b0.full;
	b.qwords[1] = b1.full;
	return b;
}
inline Encoded32Bytes EncodeQWord(const Encoded8Bytes& b0, const Encoded8Bytes& b1, const Encoded8Bytes& b2, const Encoded8Bytes& b3)
{
	Encoded32Bytes b;
	b.dwords[0] = b0.dwords[0];
	b.dwords[1] = b0.dwords[1];
	b.dwords[2] = b1.dwords[0];
	b.dwords[3] = b1.dwords[1];
	b.dwords[4] = b2.dwords[0];
	b.dwords[5] = b2.dwords[1];
	b.dwords[6] = b3.dwords[0];
	b.dwords[7] = b3.dwords[1];
	return b;
}

typedef struct Encoded3Bytes
{

	inline Encoded3Bytes() : byte0(0), byte1(0), byte2(0) {}
	inline Encoded3Bytes(const Encoded4Bytes& dword) : byte0(dword.bytes[0]), byte1(dword.bytes[1]), byte2(dword.bytes[2]) {}
	inline ~Encoded3Bytes() {}

	inline operator Encoded4Bytes() const { return EncodeByte(this->byte0, this->byte1, this->byte2, 0x00); }

	union
	{
		unsigned __int8 bytes[3];
		struct
		{
			unsigned __int8 byte0;
			unsigned __int8 byte1;
			unsigned __int8 byte2;
		};
	};

} Encoded3Bytes;

typedef Encoded2Bytes EncodedWord;
typedef Encoded4Bytes EncodedDoubleWord;
typedef Encoded8Bytes EncodedQuadWord;

typedef Encoded2Bytes EncodedShort;
typedef Encoded4Bytes EncodedInt;

#endif