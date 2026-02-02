# Parser
Language parser project based on ANTLRv4. Contains ANTLR4 format language grammar, parser source files and CMake build configs.

## Prepare environment
It's recommended to build project on Unix-like OS.
Install Java (version 11 or higher). You can use [OpenJDK](https://openjdk.org/install/).
In Visual Studio Code IDE you can use [ANTLR extension](https://marketplace.visualstudio.com/items?itemName=mike-lischke.vscode-antlr4)
for working with ANTLR g4 files.

# Generate parser source files from grammar using ANTLR
```sh
./gen_parser.sh
```

## Build parser
From parser folder root:
```sh
mkdir build
cd build
cmake ..
make
```
