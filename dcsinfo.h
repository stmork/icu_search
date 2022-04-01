#pragma once

#ifndef DCSINFO_H
#define DCSINFO_H

#include <QDebug>
#include <QString>

struct DcsInfo
{
	QString  forename;
	QString  surname;
	unsigned flat_no = 0;
	bool     found   = false;
};

QDebug operator<< (QDebug d, const DcsInfo & info);

#endif // DCSINFO_H
