#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <iosfwd>
#include <iostream>

/// <summary>
/// Class that all exceptions inherit from, and which provides the attribute that stores the Error message.
/// </summary>

class ExcepcionTAD {
public:
    /// <summary>
    /// Default constructor
    /// </summary>
	ExcepcionTAD() {}
    /// <summary>
    /// Overload constructor.    
    /// </summary>
    /// <param name="msg">A message that will be shown in the standard exception as additional information.</param>
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }
    
	friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
	std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
	out << e._msg;
	return out;
}


/// <summary>
/// Macro to declare classes of type exception
/// that inherit from ExcepcionConMessage, to save
/// write the same thing many times ...
/// the overload reuses the msg attribute of exceptions
/// </summary>


#define DECLARE_EXCEPTION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/// <summary>
/// Exception thrown by some stack operations.
/// </summary>
DECLARE_EXCEPTION(EmptyStackException);

/// <summary>
/// Exception thrown by some stack operations.
/// </summary>
DECLARE_EXCEPTION(FullStackException);

/// <summary>
/// Exception thrown by some queue operations.
/// </summary>
DECLARE_EXCEPTION(EmptyQueueException);

/// <summary>
/// Exception thrown by some double queue operations.
/// </summary>
DECLARE_EXCEPTION(EmptyDequeException);

/// <summary>
/// Exception thrown by some list operations.
/// </summary>
DECLARE_EXCEPTION(EmptyListException);

/// <summary>
/// Exception generated by incorrect accesses to the lists(both to an incorrect item numberand to bad handling of iterators).
/// </summary>
DECLARE_EXCEPTION(InvalidAccessException);

/// <summary>
/// Exception generated by operations regarding managing Components
/// </summary>
DECLARE_EXCEPTION(ComponentException);

/// <summary>
/// Exception generated when a pointer to a Object is nullptr
/// </summary>
DECLARE_EXCEPTION(NullptrObjectException);

/// <summary>
/// Exception generated by operations regarding managing GamePad Controllers
/// </summary>
DECLARE_EXCEPTION(GamePadException);

/// <summary>
/// Exception generated by operations regarding managing animator component
/// </summary>
DECLARE_EXCEPTION(AnimatorException);

#endif // EXCEPTIONS_H

