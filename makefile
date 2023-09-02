.SILENT: # Disable echo of commands
ifneq ("$(wildcard .env)","")
    include .env
endif

###############
#  VARIABLES  #
###############

DOCKER_IMAGE_NAME:=penguin-express
SHELL:=/bin/bash

export

all: install test

################
# NPM COMMANDS #
################

.PHONY : install
install :
	npm install
	npm run test

.PHONY: test
test:
	npm run test

.PHONY: coverage
coverage:
	npm run coverage

.PHONY: lint
lint:
	npm run lint

.PHONY: fix
fix:
	npm run fix

.PHONY: build
build: install
	npm run build

################
#  DOCKER CMD  #
################

.PHONY: docker-build
docker-build:
	docker build -t $(DOCKER_IMAGE_NAME) .

.PHONY: docker-run
docker-run:
	docker run -it --rm -p 3000:3000 $(DOCKER_IMAGE_NAME)

.PHONY: docker-push
docker-push:
	docker push $(DOCKER_IMAGE_NAME)

.PHONY: docker-build-run
docker-build-run: docker-build docker-run

.PHONY: docker-build-push
docker-build-push: docker-build docker-push
