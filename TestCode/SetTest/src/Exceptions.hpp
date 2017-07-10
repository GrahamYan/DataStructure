#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

namespace sjtu {

	class Exception {
		std::string detail;
	public:
		Exception():detail() {}
		Exception(const std::string &rhs): detail(rhs) {}
		Exception(const Exception &ec) : detail(ec.detail) {}
	};
	
	class TrainNotExist: public Exception {
	};
	
	class DateNotExist: public Exception {
	};
	
	class StationNotFound: public Exception {
	};
	
	class UserNotExist: public Exception {
	};
	
	class WrongPassword: public Exception {
	};
	
	class TicketsNotEnough: public Exception {
	};
	
	class NotAdmin: public Exception {
	};
	
	class IndexOutOfBound: public Exception {
	};

	class InvalidIterator: public Exception {
	};
	
	class MoneyNotEnough: public Exception {
	};
}

#endif
