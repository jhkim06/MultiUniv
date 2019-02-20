all: CommonTools DataFormats  AnalyzerTools Analyzers Archive

CommonTools::
	(cd CommonTools; make)
	(mvexist.sh CommonTools/src/CommonTools_Dict_rdict.pcm lib/)

DataFormats::
	(cd DataFormats; make)
	(mvexist.sh DataFormats/src/DataFormats_Dict_rdict.pcm lib/)

AnalyzerTools::
	(cd AnalyzerTools; make)
	(mvexist.sh AnalyzerTools/src/AnalyzerTools_Dict_rdict.pcm lib/)

Analyzers::
	(cd Analyzers; make)
	(mvexist.sh Analyzers/src/Analyzers_Dict_rdict.pcm lib/)

Archive::
	(tar -zcf lib/CommonPyTools.tar.gz CommonPyTools)
	(tar -zcf lib/CommonTools.tar.gz CommonTools)
	(tar -zcf lib/DataFormats.tar.gz DataFormats)
	(tar -zcf lib/AnalyzerTools.tar.gz AnalyzerTools)
	(tar -zcf lib/Analyzers.tar.gz Analyzers)

clean::
	(cd CommonTools; make clean)
	(cd DataFormats; make clean)
	(cd AnalyzerTools; make clean)
	(cd Analyzers; make clean)

distclean::
	(cd CommonTools; make distclean)
	(cd DataFormats; make distclean)
	(cd AnalyzerTools; make distclean)
	(cd Analyzers; make distclean)
