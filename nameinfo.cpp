/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#include "nameinfo.h"

QDebug operator<<(QDebug d, const NameInfo & info)
{
	d.nospace();
	d << info.surname << ", " << info.forename << ":" << info.flat_no;

	return d;
}
