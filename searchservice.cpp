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
	Locale      locale(Locale::getGerman());
	UErrorCode  status = U_ZERO_ERROR;

	collation = (RuleBasedCollator *)Collator::createInstance(locale, status);
	collation->setStrength(Collator::PRIMARY);
}

SearchService::~SearchService()
{
	delete collation;
}

size_t SearchService::search(
	QVector<NameInfo> & infos,
	const QString   &   pattern,
	const bool          all)
{
	const UnicodeString utf_pattern(pattern.utf16());

	QElapsedTimer  elapsed;
	size_t         count  = 0;

	elapsed.start();

	for (NameInfo & info : infos)
	{
		if (info.found || all)
		{
			QVector<UnicodeString> list;

			list << UnicodeString(info.forename.utf16());
			list << UnicodeString(info.surname.utf16());
			list << UnicodeString((info.forename + " " + info.surname).utf16());
			list << UnicodeString(QString::number(info.flat_no).utf16());

			info.found = search(list, utf_pattern);
			if (info.found)
			{
				count++;
			}
		}
	}

	qInfo().noquote() << "Search for" << pattern << "took" << elapsed.elapsed() << "ms and found" << count << "items";
	return count;
}

bool SearchService::search(
	const QStringList  &  text_list,
	const UnicodeString & pattern) const
{
	return std::any_of(
			text_list.begin(), text_list.end(),
			[this, pattern](const QString & text)
	{
		return search(UnicodeString(text.utf16()), pattern);
	});
}

bool SearchService::search(
	const QVector<UnicodeString> & text_list,
	const UnicodeString      &     pattern) const
{
	return std::any_of(
			text_list.begin(), text_list.end(),
			[this, pattern](const UnicodeString & text)
	{
		return search(text, pattern);
	});
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
