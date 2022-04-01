#include "dcsinfo.h"

QDebug operator<<(QDebug d, const DcsInfo & info)
{
	d << info.surname << ", " << info.forename << ":" << info.flat_no;

	return d;
}
