lib=protobuf

all:writer reader

CXXFLAGS = -g -std=c++11 -lpthread

reader: reader.o message.pb.o
	g++ $(CXXFLAGS) -o reader reader.o message.pb.o -l$(lib)
writer: writer.o message.pb.o
	g++ $(CXXFLAGS) -o writer writer.o message.pb.o -l$(lib)

writer.o: writer.cpp
	g++ $(CXXFLAGS) -c writer.cpp -l$(lib)
reader.o: reader.cpp
	g++ $(CXXFLAGS) -c reader.cpp -l$(lib)
message.pb.o: message.pb.cc
	g++ $(CXXFLAGS) -c message.pb.cc -l$(lib)

clean:
	rm writer reader reader.o writer.o message.pb.o
