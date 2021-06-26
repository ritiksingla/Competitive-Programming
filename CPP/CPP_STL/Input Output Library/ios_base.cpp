template <class Dummy>
class IOSB {
  public:
	enum Dummy_enum {Dummy_enum_val = 1};
	enum _Fmtflags { // formating flags
		_Fmtmask = 0xffff,
		_Fmtzero = 0
	};

	// skip leading whitespace before certain input operations
	static constexpr _Fmtflags skipws     = static_cast<_Fmtflags>(0x0001);
	// flush the output after each output operation
	static constexpr _Fmtflags unitbuf    = static_cast<_Fmtflags>(0x0002);
	// replace certain lowercase letters with their uppercase
	// equivalents in certain output operations
	static constexpr _Fmtflags uppercase  = static_cast<_Fmtflags>(0x0004);
	// generate a prefix indicating the numeric base for integer output
	static constexpr _Fmtflags showbase   = static_cast<_Fmtflags>(0x0008);
	// generate a decimal-point character unconditionally for floating-point number output
	static constexpr _Fmtflags showpoint  = static_cast<_Fmtflags>(0x0010);
	// generate a + character for non-negative numeric
	static constexpr _Fmtflags showpos    = static_cast<_Fmtflags>(0x0020);
	// left adjustment (adds fill characters to the right)
	static constexpr _Fmtflags left       = static_cast<_Fmtflags>(0x0040);
	// right adjustment (adds fill characters to the left)
	static constexpr _Fmtflags right      = static_cast<_Fmtflags>(0x0080);
	// internal adjustment (adds fill characters to the internal designated point)
	static constexpr _Fmtflags internal   = static_cast<_Fmtflags>(0x0100);
	// use decimal base for integer
	static constexpr _Fmtflags dec        = static_cast<_Fmtflags>(0x0200);
	// use octal base for integer
	static constexpr _Fmtflags oct        = static_cast<_Fmtflags>(0x0400);
	// use hexadecimal base for integer
	static constexpr _Fmtflags hex        = static_cast<_Fmtflags>(0x0800);
	// generate floating point types using scientific notation, or hex notation if combined with fixed
	static constexpr _Fmtflags scientific = static_cast<_Fmtflags>(0x1000);
	// generate floating point types using fixed notation, or hex notation if combined with scientific
	static constexpr _Fmtflags fixed      = static_cast<_Fmtflags>(0x2000);
	// insert and extract bool type in alphanumeric format
	static constexpr _Fmtflags boolalpha   = static_cast<_Fmtflags>(0x4000);

	static constexpr _Fmtflags _Stdio      = static_cast<_Fmtflags>(0x8000);
	static constexpr _Fmtflags adjustfield = static_cast<_Fmtflags>(0x01C0); // left | right | internal
	static constexpr _Fmtflags basefield   = static_cast<_Fmtflags>(0x0E00); // dec | oct | hex
	static constexpr _Fmtflags floatfield  = static_cast<_Fmtflags>(0x3000); // scientific | fixed

	enum _Iostate { // constants for stream states
		_Statmask = 0x17
	};

	static constexpr _Iostate goodbit = static_cast<_Iostate>(0x0); // no error
	static constexpr _Iostate eofbit  = static_cast<_Iostate>(0x1); // associated input sequence has reached end-of-file
	static constexpr _Iostate failbit = static_cast<_Iostate>(0x2); // input/output operation failed (formatting or extraction error)
	static constexpr _Iostate badbit  = static_cast<_Iostate>(0x4); // irrecoverable stream error

	enum _Openmode { // constants for file opening options
		_Openmask = 0xff
	};

	static constexpr _Openmode in         = static_cast<_Openmode>(0x01); // open for reading
	static constexpr _Openmode out        = static_cast<_Openmode>(0x02); // open for writing
	static constexpr _Openmode ate        = static_cast<_Openmode>(0x04); // seek to the end of stream immediately after open
	static constexpr _Openmode app        = static_cast<_Openmode>(0x08); // seek to the end of stream before each write
	static constexpr _Openmode trunc      = static_cast<_Openmode>(0x10); // discard the contents of the stream when opening
	static constexpr _Openmode _Nocreate  = static_cast<_Openmode>(0x40);
	static constexpr _Openmode _Noreplace = static_cast<_Openmode>(0x80);
	static constexpr _Openmode binary     = static_cast<_Openmode>(0x20); // open in binary mode

	enum _Seekdir { // constants for file positioning options
		_Seekbeg,
		_Seekcur,
		_Seekend
	};
	static constexpr _Seekdir beg = _Seekbeg; // the beginning of a stream
	static constexpr _Seekdir cur = _Seekcur; // end of the ending of a stream
	static constexpr _Seekdir end = _Seekend; // the current position of stream position indicator
};
class ios_base : public IOSB<int> {
  public:
	using fmtflags = int;
	using iostate  = int;
	using openmode = int;
	using seekdir  = int;

	enum event { // constants for ios events
		erase_event,
		imbue_event,
		copyfmt_event
	};
};