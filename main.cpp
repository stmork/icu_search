/*
 * Copyright (C) Steffen Andreas Mork 2022.
 * MIT license - see LICENSE file.
 */

#include <QDebug>

#include <unicode/unistr.h>

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

	service.search(infos, "e");

	for (int i = 1; i < argc; i++)
	{
		service.search(infos, argv[i]);
		infos.dump(false);
	}
}
