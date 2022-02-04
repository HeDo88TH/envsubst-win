
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

// Credit https://stackoverflow.com/a/14678800
void ReplaceStringInPlace(std::string& subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

int main(int argc, char* argv[], char* envp[])
{

	if (argc != 3)
	{
		std::cout << "Usage: envsubst-win.exe templatefile destfile" << std::endl;
		return EXIT_FAILURE;
	}

	const auto source = fs::path(argv[1]);
	const auto dest = fs::path(argv[2]);
	
	if (!exists(source))
	{
		std::cout << "Cannot find source file '" << source << '\'' << std::endl;
		return EXIT_FAILURE;
	}

	if (exists(dest)) fs::remove(dest);

	std::ifstream input(source);
	std::string content((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));
	input.close();

	int index = 0;
	while (envp[index]) {

		const auto env = std::string(envp[index++]);

		const auto pos = env.find('=');
		const auto key = env.substr(0, pos);
		const auto value = env.substr(pos + 1);

#ifdef DEBUG
		std::cout << key << " = " << value << std::endl;
#endif

		const auto findstr = "$" + key;
				
		ReplaceStringInPlace(content, findstr, value);
		
	}

	std::ofstream out(dest);
	out << content;
	out.close();
	
	return EXIT_SUCCESS;

}