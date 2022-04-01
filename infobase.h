/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#pragma once

#ifndef INFOBASE_H
#define INFOBASE_H

#include <QVector>
#include <QCollator>

#include "nameinfo.h"

class InfoBase
{
	QVector<NameInfo> infos;
	QCollator         collator;

public:
	explicit InfoBase(const char * iso_code = "de_DE");

	void        sort();
	void        dump(const bool all = true);

	inline operator QVector<NameInfo> & () noexcept
	{
		return infos;
	}

	inline operator const QVector<NameInfo> & () const noexcept
	{
		return infos;
	}

	bool operator()(const NameInfo & left, const NameInfo & right) const;

private:
	QStringList read(const char * filename);
	void        prepare();
};

#endif // INFOBASE_H
