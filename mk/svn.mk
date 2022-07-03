export PJ_BUILDNO = $(shell date "+%s")
export PJ_BUILDDATE = $(shell date "+%Y%m%d%H%M%S")
export PJ_REVISION = $(shell git log --oneline 2>/dev/null | cut -d' ' -f1 | head -n1)

ifeq ("$(PJ_REVISION)", "")
	export PJ_REVISION = $(shell svn info 2>/dev/null | grep Revision | cut -d' ' -f2)
endif

ifeq ("$(PJ_REVISION)", "")
	PJ_REVISION = 0000
endif
