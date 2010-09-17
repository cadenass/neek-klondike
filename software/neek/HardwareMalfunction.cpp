/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "HardwareMalfunction.hpp"

namespace neek {

HardwareMalfunction::HardwareMalfunction (const std::string& message)
		: message_ (message) {
}

HardwareMalfunction::~HardwareMalfunction () throw () {
}

std::string HardwareMalfunction::message () const {
	return message_;
}

const char * HardwareMalfunction::what () const throw() {
	return message_.c_str ();
}

}
