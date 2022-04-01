#include <random>
#include <vector>
#include <set>

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QElapsedTimer>
#include <QCollator>

#include <unicode/unistr.h>
#include <unicode/stsearch.h>
#include <unicode/locid.h>

#include "infobase.h"
#include "searchservice.h"

using namespace icu;

int main(int argc, char * argv[])
{
	const QString       name = "Steffen A. Mork";
	const UnicodeString unicode(name.utf16());
	const QString       output((QChar *)unicode.getBuffer(), unicode.length());

	qInfo() << output << (name == output);

	InfoBase      infos;
	SearchService service;

	infos.sort();
	infos.dump();

	service.search(infos, "e");

	for (int i = 1; i < argc; i++)
	{
		service.search(infos, argv[i]);
		infos.dump(false);
	}
}
