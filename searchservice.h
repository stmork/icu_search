/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#pragma once

#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include "nameinfo.h"

#include <unicode/tblcoll.h>

class SearchService
{
	icu::RuleBasedCollator * collation = nullptr;

public:
	SearchService();
	virtual ~SearchService();

	size_t search(
		QVector<NameInfo> & infos,
		const QString   &   pattern,
		const bool          all = true);
	bool search(
		const QStringList     &    text,
		const icu::UnicodeString & pattern) const;
	bool search(
		const QVector<icu::UnicodeString> & text,
		const icu::UnicodeString      &     pattern) const;
	bool search(
		const icu::UnicodeString & text,
		const icu::UnicodeString & pattern) const;
};

#endif // SEARCHSERVICE_H
