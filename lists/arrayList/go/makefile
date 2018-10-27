export GOPATH := /home/`whoami`/Dstructs/lists/arrayList/go
export GOBIN := $(GOPATH)/bin

default:
	@echo "Go Build for path : " $(GOPATH)
	rm -f test
	$(shell cd $(GOPATH)/src/arrayList; go install)
	$(shell cd $(GOPATH)/src/test     ; go install)
	ln -s bin/test test

clean:
	rm test
	rm -rf $(GOPATH)/bin/*
	rm -rf $(GOPATH)/pkg/*
