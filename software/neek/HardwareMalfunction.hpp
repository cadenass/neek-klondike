/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_HARDWARE_MALFUNCTION_HEADER
#define NIOSII_KLONDIKE_HARDWARE_MALFUNCTION_HEADER

#include <exception>
#include <string>

namespace neek {

/*
 * This exception is generated when some hardware error is occurred.
 */
class HardwareMalfunction : public std::exception {
public:

	/*
	 * Creates exception with MESSAGE, which describes error.
	 */
	HardwareMalfunction (const std::string& message);

	~HardwareMalfunction () throw ();

	/*
	 * Returns the message which describes error.
	 */
	std::string message () const;

	/*
	 * Returns a C-style string which describes error.
	 */
	const char * what () const throw();

private:
	std::string message_;
};

}

#endif
