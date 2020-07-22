all: encode decode

encode: ./bin/encode.out
	@if $$(! test -f input.txt); \
	then \
		printf "This is a test string, as no input.txt file was found." > input.txt; \
		printf "" > cypher.txt; \
		printf "" > key.txt; \
	fi
	./bin/encode.out

./bin/encode.out: 
	g++ ./src/encode.cpp -o ./bin/encode.out

./bin/decode.out:
	g++ ./src/decode.cpp -o ./bin/decode.out

decode: ./bin/decode.out
	@if $$(! test -f cypher.txt); \
	then \
		echo "Error: cypher.txt not found"; \
		exit 1; \
	fi
	@if $$(! test -f key.txt); \
	then \
		echo "Error: key.txt not found"; \
		exit 1; \
	fi
	./bin/decode.out

clean:
	rm -f input.txt
	rm -f output.txt
	rm -f key.txt
	rm -f cypher.txt
	rm -f ./bin/*