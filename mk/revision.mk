
.PHONY: gitTadd
gitTadd:
ifneq ("$(VERSION_FULL)", "")
	git tag -a v$(VERSION_FULL)
endif

.PHONY: gitTaddPush
gitTaddPush:
ifneq ("$(VERSION_FULL)", "")
	git push origin v$(VERSION_FULL)
endif

.PHONY: gitTdel
gitTdel:
ifneq ("$(VERSION_FULL)", "")
	git tag -d v$(VERSION_FULL)
endif

.PHONY: gitTdelPush
gitTdelPush:
ifneq ("$(VERSION_FULL)", "")
	git push --delete origin v$(VERSION_FULL)
endif
