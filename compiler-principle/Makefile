NAME = spl

LLVM_CONFIG = llvm-config

NO_WARNING = -Wno-return-type -Wno-c++11-compat-deprecated-writable-strings -Wno-deprecated-registe -Wno-switch

CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++14 $(NO_WARNING) -O3
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs` lib/libbed.a -lm -lpthread -lrt -ldl -lz -ltinfo

OBJS = parser.o lexer.o utils.o AbsSyntaxTree.o main.o irbuilder.o JsonPart.o
HEADERS = AbsSyntaxTree.h irbuilder.h utils.h parser.hpp

all : $(NAME)

lexer.cpp: lexer.l
	flex -o lexer.cpp lexer.l

parser.cpp: parser.y
	bison -d -o parser.cpp parser.y

%.o: %.cpp $(HEADERS)
	g++ -O3 -c $(CXXFLAGS) -o $@ $< 

lib/rt/libspl.o:
	gcc -O3 -c lib/rt/libspl.c -o lib/rt/libspl.o

$(NAME): $(OBJS) lib/rt/libspl.o
	g++ -O3 -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f ./*.o
	-rm -f ./parser.hpp parser.cpp lexer.cpp
	-rm -f ./*.json
	-rm -f ./*.s
	-rm -f ./*.ll
	-rm -f ./*.bc
	-rm -f ./*.dot

.PHONY: clean-all
clean-all: clean
	-rm -f ./spl
	-rm -f ./lib/rt/libspl.o
