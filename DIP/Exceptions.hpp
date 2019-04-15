#ifndef _DIP_Exceptions_hpp_
#define _DIP_Exceptions_hpp_

#include <string>
#include <stdexcept>

#define CAR(first, ...) first
#define DEF(name, ...) \
	struct name : __VA_ARGS__ { \
		name(string w) : CAR(__VA_ARGS__)(w) {}; \
		name(): CAR(__VA_ARGS__)("") {}; \
	}

namespace DIP {
	namespace Exception {
		using std::string;
		using std::exception;
		using std::logic_error;
		using std::runtime_error;

		struct Base : exception {
			string whatarg;
			Base(string w) : whatarg(w) {};
		};

		DEF(LogicError, logic_error);
		DEF(RuntimeError, runtime_error);
		DEF(IOError, RuntimeError);
		DEF(UnknownColorFormatError, IOError);
		DEF(NotImplemented, Base, LogicError);
	};
};

#undef DEF
#undef CAR

#endif
