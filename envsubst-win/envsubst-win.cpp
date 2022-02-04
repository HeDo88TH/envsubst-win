
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

// Credit https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
std::string ltrim(const std::string& s, const std::string& chars)
{
	const size_t start = s.find_first_not_of(chars);
	return start == std::string::npos ? "" : s.substr(start);
}

std::string rtrim(const std::string& s, const std::string& chars)
{
	const size_t end = s.find_last_not_of(chars);
	return end == std::string::npos ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s, const std::string& chars) {
	return rtrim(ltrim(s, chars), chars);
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
		const auto value = trim(env.substr(pos + 1), "\"");

#ifdef _DEBUG
		std::cout << key << " = \"" << value << '\"' << std::endl;
#endif

		const auto findstr = "$" + key;
				
		ReplaceStringInPlace(content, findstr, value);
		
	}

	std::ofstream out(dest);
	out << content;
	out.close();
	
	return EXIT_SUCCESS;

}