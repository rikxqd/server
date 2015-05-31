#ifndef _INTEGER_H_
#define _INTEGER_H_

#pragma once

#ifdef WIN32
typedef signed char			int8;
typedef signed short			int16;
typedef signed int				int32;
typedef signed __int64			int64;
typedef unsigned char			uint8;
typedef unsigned short			uint16;
typedef unsigned int			uint32;
typedef unsigned __int64		uint64;
#elif UNIX
typedef signed char			int8;
typedef signed short			int16;
typedef signed int				int32;
typedef signed long long		int64;
typedef unsigned char			uint8;
typedef unsigned short			uint16;
typedef unsigned int			uint32;
typedef unsigned long long	uint64;
#endif

#define MAX_INT8			0x7F
#define MIN_INT8			0x80

#define MAX_INT16		0x7FFF
#define MIN_INT16			0x8000

#define MAX_INT32		0x7FFFFFFF
#define MIN_INT32			0x80000000

#define MAX_INT64		0x7FFFFFFFFFFFFFFF
#define MIN_INT64			0x8000000000000000

#define MAX_UINT8		0xFF
#define MIN_UINT8		0x00

#define MAX_UINT16		0xFFFF
#define MIN_UINT16		0x0000

#define MAX_UINT32		0xFFFFFFFF
#define MIN_UINT32		0x00000000

#define MAX_UINT64		0xFFFFFFFFFFFFFFFF
#define MIN_UINT64		0x0000000000000000

#define UINT64_INC_OVER_FLOW(UI64_0, UI64_1) ((UI64_0&MAX_UINT64) > (MAX_UINT64&~(UI64_1)))
#define UINT32_INC_OVER_FLOW(UI32_0, UI32_1) ((UI32_0&MAX_UINT32) > (MAX_UINT32&~(UI32_1)))
#define UINT32_DEC_OVER_FLOW(UI32_0, UI32_1) ((UI32_0&MAX_UINT32) < (MAX_UINT32&UI32_1))
#define UINT16_INC_OVER_FLOW(UI16_0, UI16_1) ((UI16_0&MAX_UINT16) > (MAX_UINT16&~(UI16_1)))
#define UINT16_DEC_OVER_FLOW(UI16_0, UI16_1) ((UI16_0&MAX_UINT16) < (MAX_UINT16&UI16_1))
#define UINT8_INC_OVER_FLOW(UI8_0, UI8_1) ((UI8_0&MAX_UINT8) > (MAX_UINT8&~(UI8_1)))
#define UINT8_DEC_OVER_FLOW(UI8_0, UI8_1) ((UI8_0&MAX_UINT8) < (MAX_UINT8&UI8_1))

union B4
{
public:
	uint32	_ui32;
	int32		_i32;
	int8		_i8[4];
	uint8		_ui8[4];
	int16		_i16[2];
	uint16	_ui16[2];

public:

	B4() :_ui32(0) {}
	B4(uint32 ui32) :_ui32(ui32) {}
	B4(uint16 ui16_0, uint16 ui16_1) { _ui16[0] = ui16_0; _ui16[1] = ui16_1; }

	operator uint32() const { return _ui32; }

	void FromLong(long l) { _i32 = static_cast<int32>(l); }
	long ToLong() { return static_cast<long>(_i32); }
	void FromULong(unsigned long ul) { _ui32 = static_cast<uint32>(ul); }
	unsigned long ToULong() { return static_cast<long>(_ui32); }

	void operator	+=	(uint32 ui32) { _ui32 += ui32; }
	void operator	-=	(uint32 ui32) { _ui32 -= ui32; }
	void operator	*=	(uint32 ui32) { _ui32 *= ui32; }
	void operator	/=	(uint32 ui32) { _ui32 /= ui32; }
	void operator	%=	(uint32 ui32) { _ui32 %= ui32; }
	void operator	+=	(B4 b4) { _ui32 += b4.UI32(); }
	void operator	-=	(B4 b4) { _ui32 -= b4.UI32(); }
	void operator	*=	(B4 b4) { _ui32 *= b4.UI32(); }
	void operator	/=	(B4 b4) { _ui32 /= b4.UI32(); }
	void operator	%=	(B4 b4) { _ui32 %= b4.UI32(); }
	void operator	++	() { ++_ui32; }
	void operator	--	() { --_ui32; }

	void Inc() { ++_ui32; }
	void Dec() { --_ui32; }

	bool IsZero() { return 0 == _ui32; }
	bool IsMaxUI32() { return MAX_UINT32 == _ui32; }
	bool IsMaxI32() { return MAX_INT32 == _i32; }
	void SetZero() { _ui32 = 0; }
	void SetMaxUI32() { _ui32 = MAX_UINT32; }
	void SetMaxI32() { _i32 = MAX_INT32; }

	int8&			I8_0() { return _i8[0]; }
	int8&			I8_1() { return _i8[1]; }
	int8&			I8_2() { return _i8[2]; }
	int8&			I8_3() { return _i8[3]; }
	uint8&			UI8_0() { return _ui8[0]; }
	uint8&			UI8_1() { return _ui8[1]; }
	uint8&			UI8_2() { return _ui8[2]; }
	uint8&			UI8_3() { return _ui8[3]; }
	int16&			I16_0() { return _i16[0]; }
	int16&			I16_1() { return _i16[1]; }
	uint16&		UI16_0() { return _ui16[0]; }
	uint16&		UI16_1() { return _ui16[1]; }
	int32&			I32() { return _i32; }
	uint32&		UI32() { return _ui32; }
	long			L32() { return static_cast<long>(_i32); }
	unsigned long	UL32() { return static_cast<unsigned long>(_ui32); }
};

union B8
{
private:
	uint64		_ui64;
	int64		_i64;
	int8			_i8[8];
	uint8		_ui8[8];
	int16		_i16[4];
	uint16		_ui16[4];
	int32		_i32[2];
	uint32		_ui32[2];
public:

	B8() : _ui64(0) { _ui64 = 0; }
	B8(B4 b4) : _ui64(b4.UI32()){}
	B8(B4 b4_0, B4 b4_1) { _ui32[0] = b4_0; _ui32[1] = b4_1; }
	B8(int32 i32) : _i64(i32) {}
	B8(uint32 ui32) :_ui64(ui32) {}
	B8(long l) { _i64 = static_cast<int32>(l); }
	B8(unsigned long ul) { _ui64 = static_cast<uint32>(ul); }
	B8(int64 i64) : _i64(i64) {}
	B8(uint64 ui64) : _ui64(ui64) {}

	operator uint64() const { return _ui64; }

	int8&		I8_0() { return _i8[0]; }
	int8&		I8_1() { return _i8[1]; }
	int8&		I8_2() { return _i8[2]; }
	int8&		I8_3() { return _i8[3]; }
	int8&		I8_4() { return _i8[4]; }
	int8&		I8_5() { return _i8[5]; }
	int8&		I8_6() { return _i8[6]; }
	int8&		I8_7() { return _i8[7]; }
	uint8&		UI8_0() { return _ui8[0]; }
	uint8&		UI8_1() { return _ui8[1]; }
	uint8&		UI8_2() { return _ui8[2]; }
	uint8&		UI8_3() { return _ui8[3]; }
	uint8&		UI8_4() { return _ui8[4]; }
	uint8&		UI8_5() { return _ui8[5]; }
	uint8&		UI8_6() { return _ui8[6]; }
	uint8&		UI8_7() { return _ui8[7]; }
	int16&		I16_0() { return _i16[0]; }
	int16&		I16_1() { return _i16[1]; }
	int16&		I16_2() { return _i16[2]; }
	int16&		I16_3() { return _i16[3]; }
	uint16&	UI16_0() { return _ui16[0]; }
	uint16&	UI16_1() { return _ui16[1]; }
	uint16&	UI16_2() { return _ui16[2]; }
	uint16&	UI16_3() { return _ui16[3]; }
	int32&		I32_0() { return _i32[0]; }
	int32&		I32_1() { return _i32[1]; }
	uint32&	UI32_0() { return _ui32[0]; }
	uint32&	UI32_1() { return _ui32[1]; }
	int64&		I64() { return _i64; }
	uint64&	UI64() { return _ui64; }

	void operator	++	() { ++_ui64; }
	void operator	--	() { --_ui64; }
};

#define ITER_UI8(_idx, _max) for(uint8 _idx = 0; _idx < _max; ++_idx)
#define ITER_UI16(_idx, _max) for(uint16 _idx = 0; _idx < _max; ++_idx)
#define ITER_UI32(_idx, _max) for(uint32 _idx = 0; _idx < _max; ++_idx)
#define ITER_B4(_idx, _max) for(B4 _idx = 0; _idx < _max; ++_idx)

#endif//_INTEGER_H_
