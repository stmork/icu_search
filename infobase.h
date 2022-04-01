#ifndef INFOBASE_H
#define INFOBASE_H

#include <QVector>
#include <QCollator>

#include <dcsinfo.h>

class InfoBase
{
	QVector<DcsInfo> infos;
	QCollator        collator;

public:
	explicit InfoBase(const char * iso_code = "de_DE");

	void        sort();
	void        dump(const bool all = true);

	inline operator QVector<DcsInfo> & ()
	{
		return infos;
	}

	bool operator()(const DcsInfo & left, const DcsInfo & right) const;

private:
	QStringList read(const char * filename);
	void        prepare();
};

#endif // INFOBASE_H
