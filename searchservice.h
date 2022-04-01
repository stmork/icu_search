#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include "dcsinfo.h"

#include <unicode/tblcoll.h>

class SearchService
{
	icu::RuleBasedCollator * collation = nullptr;

public:
	SearchService();
	virtual ~SearchService();

	size_t search(QVector<DcsInfo> & infos, const QString & pattern);
};

#endif // SEARCHSERVICE_H
