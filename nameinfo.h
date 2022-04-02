/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#pragma once

#ifndef NAMEINFO_H
#define NAMEINFO_H

#include <QDebug>
#include <QString>

struct NameInfo
{
	QString  forename;
	QString  surname;
	unsigned flat_no = 0;
	bool     found   = false;
};

QDebug operator<< (QDebug d, const NameInfo & info);

#endif // NAMEINFO_H
