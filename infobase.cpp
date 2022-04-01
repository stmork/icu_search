#include "infobase.h"

#include <random>

#include <QFile>
#include <QElapsedTimer>

InfoBase::InfoBase(const char * iso_code)
{
	prepare();

	collator.setLocale(QLocale(iso_code));
	collator.setIgnorePunctuation(true);
	collator.setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
}

void InfoBase::prepare()
{
	const QStringList   forename_list = read("forenames.txt");
	const QStringList   surname_list  = read("surnames.txt");

	std::random_device rd;
	std::mt19937       gen(rd());

	std::uniform_int_distribution<> random_forename(0, forename_list.size() - 1);
	std::uniform_int_distribution<> random_surname( 0, surname_list.size() - 1);

	for (unsigned i = 0; i < 10000; i++)
	{
		DcsInfo info;

		info.forename = forename_list[random_forename(gen)];
		info.surname  = surname_list[random_surname(gen)];
		info.flat_no  = i * 17 % 1001;

		infos << info;
	}
}

QStringList InfoBase::read(const char * filename)
{
	QFile       file(filename);
	QStringList list;

	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);

		while (!in.atEnd())
		{
			const QString & line = in.readLine();

			if (!line.isEmpty())
			{
				list << line;
			}
		}

		file.close();
	}
	return list;
}

void InfoBase::sort()
{
	QElapsedTimer elapsed;

	elapsed.start();
	qInfo() << infos.size() << "elements";
	std::sort(infos.begin(), infos.end(), *this);
	qInfo() << "Sorted in " << elapsed.elapsed() << "ms.";
}

void InfoBase::dump(const bool all)
{
	for (const DcsInfo & info : infos)
	{
		if (info.found || all)
		{
			qDebug() << info;
		}
	}
}

bool InfoBase::operator()(const DcsInfo & left, const DcsInfo & right) const
{
	int result = 0;

	result = collator.compare(left.surname, right.surname);
	if (result == 0)
	{
		result = collator.compare(left.forename, right.forename);
		if (result == 0)
		{
			result = (int)left.flat_no - (int)right.flat_no;
		}
	}
	return result < 0;
}
