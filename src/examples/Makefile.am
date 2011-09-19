
INCLUDES = -I$(top_srcdir)/src/ctxdata -I$(top_srcdir)/include -I../ctxdata

if BUILD_MONITOR
monitor_programs = noisedemo squaredemo mysquaredemo
if HAVE_LIBSNDFILE1
sndfile_programs = sndfiledemo simple_sndfiledemo
endif

endif

noinst_PROGRAMS = cd_list_test $(monitor_programs) $(sndfile_programs)

EXTRA_DIST = 909_cl.wav 1052.wav

REMIX_LIBS = ../ctxdata/libctxdata.la ../libremix/libremix.la ../ctxdata/libctxdata.la -ldl

cd_list_test_SOURCES = cd_list_test.c
cd_list_test_LDADD = ../ctxdata/libctxdata.la

noisedemo_SOURCES = noisedemo.c
noisedemo_LDADD = $(REMIX_LIBS)

squaredemo_SOURCES = squaredemo.c
squaredemo_LDADD = $(REMIX_LIBS)

mysquaredemo_SOURCES = simple_squaredemo.c
mysquaredemo_LDADD = $(REMIX_LIBS)

sndfiledemo_CFLAGS = -DSAMPLEDIR=\"$(srcdir)\"
sndfiledemo_SOURCES = sndfiledemo.c
sndfiledemo_LDADD = $(REMIX_LIBS) @SNDFILE_LIBS@

simple_sndfiledemo_CFLAGS = -DSAMPLEDIR=\"$(srcdir)\"
simple_sndfiledemo_SOURCES = simple_sndfiledemo.c
simple_sndfiledemo_LDADD = $(REMIX_LIBS) @SNDFILE_LIBS@
