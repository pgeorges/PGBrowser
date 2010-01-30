# program name
APPNAME = PGBrowser

# get the operating system
OSNAME = $(shell uname)

#objects and sources
OBJS = main MainApplication 
OBJS += bookmarks/BookmarksContainer
OBJS += network/PersistentCookieJar
OBJS += widgets/AddBookmarkDialog widgets/MenuBar widgets/MainWindow widgets/TabWidget widgets/TabBar widgets/MainToolBar widgets/WebPanel widgets/WebPage
OBJS += widgets/PreferencesDialog widgets/LocationBar widgets/PasswordDialog widgets/BookmarksManagerDialog widgets/BookmarksToolBar

#Qt mocs
MOCS = MainApplication
MOCS += network/PersistentCookieJar
MOCS += widgets/AddBookmarkDialog widgets/MenuBar widgets/MainWindow widgets/TabWidget widgets/TabBar widgets/MainToolBar widgets/WebPanel widgets/WebPage
MOCS += widgets/PreferencesDialog widgets/LocationBar widgets/PasswordDialog widgets/BookmarksManagerDialog widgets/BookmarksToolBar

#build/out directories
ICONDIR = icons/
OUTDIR = out/
SRCDIR = src/
ifeq (${OSNAME},Linux)
	BUILDDIR = ${OUTDIR}linux/
endif

RELEASEDIR = ${BUILDDIR}release/

# third party directories
QTSINGLEAPPLICATIONDIR = thirdparty/QtSingleApplication2.6/

# define compile and linker settings for Linux
ifeq (${OSNAME},Linux)
	MOCFLAGS        = -I${QTDIR}include
	CC              = g++
	CFLAGS          = -c -Wall 
	CFLAGS          += -I${QTSINGLEAPPLICATIONDIR}src
	CCOUT           = -o 
	LD              = g++
	LDFLAGS         = -L${QTSINGLEAPPLICATIONDIR}lib/linux-Qt4.5.3
	LDFLAGS        += -lstdc++ -l QtSolutions_SingleApplication-2.6
	LDFLAGS        += -l QtCore -l QtGui -l QtWebKit -l QtNetwork
	LDOUT           = -o 
	OEXT            = .o
	EXECUTABLE      = $(APPNAME)
else
error:
	@echo Error: Unsupported OS
endif

#append the extention to the OBJS and MOCS
EOBJS = $(addprefix $(BUILDDIR),$(addsuffix $(OEXT),$(OBJS)))
SRCS  = $(addprefix $(SRCDIR),$(addsuffix .cpp,$(OBJS)))
EMOCS = $(addprefix $(SRCDIR),$(addsuffix .moc,$(MOCS)))

all: dirs ${EMOCS} ${EXECUTABLE} instruction

dirs:
ifeq (${OSNAME},Linux)
	@mkdir -p ${OUTDIR}
	@mkdir -p ${BUILDDIR}
	@mkdir -p ${BUILDDIR}bookmarks/
	@mkdir -p ${BUILDDIR}network/
	@mkdir -p ${BUILDDIR}widgets/
	@mkdir -p ${RELEASEDIR}
endif

%.moc: %.h
	moc ${MOCFLAGS} -i $< -o $@

${EXECUTABLE}: ${EOBJS}
	${LD} ${LDFLAGS} ${EOBJS} ${LDOUT}${EXECUTABLE}

${BUILDDIR}%${OEXT}: $(SRCDIR)%.cpp
	${CC} ${CFLAGS} $< ${CCOUT}$@

instruction:
	@echo - Executable: ${EXECUTABLE}

clean:
	@rm -rf ${BUILDDIR}
