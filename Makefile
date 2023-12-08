build:
	gcc src/*.c -o bin/Game -Wall -Wextra -O1

run:
	@make build
	@bin/Game