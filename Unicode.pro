QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
	infobase.cpp \
	main.cpp \
	nameinfo.cpp \
	searchservice.cpp

LIBS += -licudata -licui18n -licuuc

HEADERS += \
	infobase.h \
	nameinfo.h \
	searchservice.h

#####################################################################
#
# Extra targets.
#
#####################################################################

QMAKE_EXTRA_TARGETS += astyle cppcheck

astyle.commands = astyle *.cpp *.h

cppcheck.commands = cppcheck\
	--enable=style,warning,performance,portability\
	--inline-suppr\
	--suppress=unusedStructMember\
	--suppress=useStlAlgorithm\
	--suppress=noCopyConstructor\
	--suppress=noOperatorEq\
	-I$$[QT_INSTALL_HEADERS]\
	--language=c++ --std=c++14\
	--library=qt\
	--xml-version=2 --force -q -j 3\
	*.cpp *.h \
	2>cppcheck.xml

QMAKE_CLEAN += cppcheck.xml valgrind*.xml *test-*-results.xml *.deb *.qch
