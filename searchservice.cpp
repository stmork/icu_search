#include "searchservice.h"

#include <QElapsedTimer>
#include <QLocale>

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

size_t SearchService::search(QVector<DcsInfo> & infos, const QString & pattern)
{
	const UnicodeString utf_pattern(pattern.utf16());

	QElapsedTimer  elapsed;
	UErrorCode     status = U_ZERO_ERROR;
	size_t         count  = 0;

	elapsed.start();

	for (DcsInfo & info : infos)
	{
		QStringList list;

		list << info.forename;
		list << info.surname;
		list << QString::number(info.flat_no);

		info.found = false;
		for (const QString & text : list)
		{
			const UnicodeString utf_search(text.utf16());
			StringSearch        search(utf_pattern, utf_search, collation, nullptr, status);
			const int           pos = search.first(status);

			info.found |= U_SUCCESS(status) && (pos != USEARCH_DONE);
		}
		if (info.found)
		{
			count++;
		}
	}
	qDebug() << "Search for" << pattern << "took" << elapsed.elapsed() << "ms";
	return count;
}
