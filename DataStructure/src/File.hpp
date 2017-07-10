//attention：写完一个out文件务必flush()
//attention：如果强行想要关闭当前文件，就用智能指针只向这个类，让它自己析构

#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <string>
#include <iostream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
//using std::cin;
//using std::cout;

namespace sjtu {
	//const string endl = string("\n");
	class AscllInput {
		ifstream file;
		void close() {
			file.close();
		}
	public:
		AscllInput(const string &str): file(str) {}
		friend AscllInput &operator >> (AscllInput &in, int &obj) {
			in.file >> obj;
			return in;
		}
		friend AscllInput &operator >> (AscllInput &in, double &obj) {
			in.file >> obj;
			return in;
		}
		friend AscllInput &operator >> (AscllInput &in, bool &obj) {
			in.file >> obj;
			return in;
		}
		friend AscllInput &operator >> (AscllInput &in, string &obj) {
			in.file >> obj;
			return in;
		}
		/*friend AscllInput &operator >> (AscllInput &in, char *str) {
			//out.file << str;
			in.file >> str;
			return in;
		}*/
		void reopen(const string &str) {
			close();
			file = (ifstream)str;
		}
		~AscllInput() {
			close();
		}
	};
	
	class AscllOutput {
		ofstream file;
		void close() {
			file.close();
		}
	public:
		AscllOutput(const string &str): file(str) {}
		friend AscllOutput &operator << (AscllOutput &out, const int &obj) {
//std::cerr << "out int" << std::endl;
			out.file << obj;
			return out;
		}
		friend AscllOutput &operator << (AscllOutput &out, const double &obj) {
//std::cerr << "out double" << std::endl;
			out.file << obj;
			return out;
		}
		friend AscllOutput &operator << (AscllOutput &out, const bool &obj) {
//std::cerr << "out bool" << std::endl;
			out.file << obj;
			return out;
		}
		friend AscllOutput &operator << (AscllOutput &out, const string &obj) {
//std::cerr << "out string" << std::endl;
			out.file << obj;
			return out;
		}
		/*friend AscllOutput &operator << (AscllOutput &out, char *str) {
			out.file << str;
			return out;
		}//尽量避免输出char
		friend AscllOutput &operator << (AscllOutput &out, const char *str) {
			out.file << str;
			return out;
		}*/
		void flush() {
			file.flush();
		}
		void reopen(const string &str) {
			flush();
			close();
			file = (ofstream)str;
		}
		~AscllOutput() {
			flush();
			close();
		}
	};

	class BinaryInput {
		ifstream file;
		void close() {
			file.close();
		}
	public:
		BinaryInput(const string &str): file(str, std::ios::binary) {
		}
		friend BinaryInput &operator >> (BinaryInput &in, int &obj) {
			in.file.read((char *)(&obj), sizeof(obj));
			return in;
		}
		friend BinaryInput &operator >> (BinaryInput &in, double &obj) {
			in.file.read((char *)(&obj), sizeof(obj));
			return in;
		}
		friend BinaryInput &operator >> (BinaryInput &in, bool &obj) {
			in.file.read((char *)(&obj), sizeof(obj));
			return in;
		}
		friend BinaryInput &operator >> (BinaryInput &in, string &obj) {
			int size;
			char ch;
			in.file.read((char *)(&size), sizeof(size));
			obj = "";
			for (; size; --size) {
				in.file.read((char *)(&ch), sizeof(ch));
				obj = obj + ch;
			}
			return in;
		}
		/*friend BinaryInput &operator >> (BinaryInput &in, char *str) {
			//out.file << str;
			in.file.read((char *)(&str), sizeof(str));
			return in;
		}*/
		void reopen(const string &str) {
			close();
			file = ifstream(str, std::ios::binary);
		}
		~BinaryInput() {
			close();
		}
	};
	
	class BinaryOutput {
		ofstream file;
		void close() {
			file.close();
		}
	public:
		BinaryOutput(const string &str): file(str, std::ios::binary) {}
		friend BinaryOutput &operator << (BinaryOutput &out, const int &obj) {
//std::cerr << "out int" << std::endl;
			out.file.write((char *)(&obj), sizeof(obj));
			return out;
		}
		friend BinaryOutput &operator << (BinaryOutput &out, const double &obj) {
//std::cerr << "out double" << std::endl;
			out.file.write((char *)(&obj), sizeof(obj));
			return out;
		}
		friend BinaryOutput &operator << (BinaryOutput &out, const bool &obj) {
//std::cerr << "out bool" << std::endl;
			out.file.write((char *)(&obj), sizeof(obj));
			return out;
		}
		friend BinaryOutput &operator << (BinaryOutput &out, const string &obj) {
//std::cerr << "out string" << std::endl;
			int size = obj.size();
			out.file.write((char *)(&size), sizeof(size));
			out.file.write((obj.c_str()), sizeof(char) * obj.size());
			return out;
		}
		/*friend BinaryOutput &operator << (BinaryOutput &out, const char *&obj) {
			out.file.write((char *)(&obj), sizeof(obj));
			return out;
		}//尽量避免输出char*/
		/*friend BinaryOutput &operator << (BinaryOutput &out, const (const char *)&obj) {
			out.file.write((char *)(&obj), sizeof(obj));
			return out;
		}*/
		void flush() {
			file.flush();
		}
		void reopen(const string &str) {
			flush();
			close();
			file = ofstream(str, std::ios::binary);
		}
		~BinaryOutput() {
			flush();
			close();
		}
	};
	
	
}

#endif
