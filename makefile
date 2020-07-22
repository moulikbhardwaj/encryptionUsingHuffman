all: encode decode

encode: input.txt ./bin/encode.out
	./bin/encode.out

./bin/encode.out: 
	g++ ./src/encode.cpp -o ./bin/encode.out

./bin/decode.out:
	g++ ./src/decode.cpp -o ./bin/decode.out

input.txt:
	@echo "This is a test string, as no input.txt file was found." > input.txt

decode: cypher.txt key.txt ./bin/decode.out
	./bin/decode.out

cypher.txt: encode

key.txt: encode

clean:
	rm -f input.txt
	rm -f output.txt
	rm -f key.txt
	rm -f cypher.txt
	rm -f ./bin/*