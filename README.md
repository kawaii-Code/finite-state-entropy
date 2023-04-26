# Finite State Entropy Encoder/Decoder

A data encoder/decoder based on the Finite State Entropy algorithm.
Made for the discrete math course at my university (Hello, Kirill Vladimirovich!!!)

## Example

```console
./fse -e
3
a:5 b:2 c:1
abcaabaa

Encoding string 'abcaabaa'...
Encoded: 00101101111, last state: 2
```

## Building

To build the program from source, you can run the make command from the project root:
```console
make
```

## Running

The program requires one of the arguments `-e` or `-d`. `-e` is for encoding the
input data, `-d` is for decoding.

### Encoding

To encode data, launch the program with `-e` option.
Then specify the number of different symbols in the input, 
(for `aabcbb` it will be *3*) then input the symbols 
themselves and the times they appear in the string in format 
'symbol':'frequency' (for `aabcbb`: *a:2 b:3 c:1*)
After that, input the string that needs to be encoded. 
```bash
./fse -e
3
a:2 b:3 c:1
aabcbb

Encoding string 'aabcbb'...
Encoded: 00001110, last state: 6
```

### Decoding

To decode the data, launch the program with `-d` option.
Specify everything that was needed for encoding + the last
state of the encoder (that is needed for decoding).
```bash
./fse -d
3
a:2 b:3 c:1
00001110
6

Decoding string '00001110'...
Decoded: aabcbb
```

## Useful links

[Wiki page](https://en.wikipedia.org/wiki/Entropy_coding)

[Russian article on Habr](https://habr.com/ru/companies/playrix/articles/324116/)
