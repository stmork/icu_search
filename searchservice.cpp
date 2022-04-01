/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#include "searchservice.h"

#include <QElapsedTimer>

#include <unicode/unistr.h>
#include <unicode/stsearch.h>
#include <unicode/locid.h>

using namespace icu;

SearchService::SearchService()
{
	Locale      locale;
	UErrorCode  status = U_ZERO_ERROR;

	collation = (RuleBasedCollator *)Collator::createInstance(locale, status);
	collation->setStrength(Collator::PRIMARY);
}

SearchService::~SearchService()
{
	delete collation;
}

size_t SearchService::search(QVector<NameInfo> & infos, const QString & pattern)
{
	const UnicodeString utf_pattern(pattern.utf16());

	QElapsedTimer  elapsed;
	size_t         count  = 0;

	elapsed.start();

	for (NameInfo & info : infos)
	{
		QStringList list;

		list << info.forename;
		list << info.surname;
		list << QString::number(info.flat_no);

		info.found = false;
		for (const QString & text : list)
		{
			info.found |= search(UnicodeString(text.utf16()), utf_pattern);
		}
		if (info.found)
		{
			count++;
		}
	}
	qDebug() << "Search for" << pattern << "took" << elapsed.elapsed() << "ms";
	return count;
}

bool SearchService::search(
	const UnicodeString & text,
	const UnicodeString & pattern) const
{
	UErrorCode     status = U_ZERO_ERROR;
	StringSearch   search(pattern, text, collation, nullptr, status);
	const int      pos = search.first(status);

	return U_SUCCESS(status) && (pos != USEARCH_DONE);
}
