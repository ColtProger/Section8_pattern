#include <fstream>
int main(int argc, char** argv)
{
	std::ofstream fout("C:\\Users\\data.txt"); // открыли файл C:\data.txt на запись
	fout << "Hello \n";
}