#include <iostream>
#include <regex>
#include <map>

std::map<std::string, std::string> resources;

std::string replace(std::string str, std::string& from, std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return str;
	str.replace(start_pos, from.length(), to);
	return str;
}
std::vector<std::string> split(const std::string& input, const std::string& regex) {
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(regex);
	std::sregex_token_iterator
		first{ input.begin(), input.end(), re, -1 },
		last;
	return{ first, last };
}

std::string _processImports(const std::string source)
{
	std::regex rgx("#import<(.+)>(\[(.*)\])*(\((.*)\))*");
	std::smatch match;
	std::string str = source;
	while(std::regex_search(str, match, rgx))
	{
		std::string includeFile = match[1];
		std::string content = resources[includeFile];
		for (const auto& m : match)
		{
			std::cout << "match: " << m << '\n';
		}
		if (match.size() > 4)
		{
			auto splits = split(match[5].str(), ",");
			for (unsigned int idx = 0, size = splits.size();
				idx < size; ++idx) {
				auto sp = split(splits[idx], "=");
				// content = replace() content = content.replace(new RegExp(sp[0], "g"), sp[1]);
			}
		}
		if (match.size() > 2)
		{
			/*auto idxStr = match[3].str();
			if (idxStr.indexOf("..") != = -1) {
				let idxSplits = idxStr.split("..");
				let min = parseInt(idxSplits[0]);
				let max = parseInt(idxSplits[1]);
				let srcContent = content.slice(0);
				content = "";
				if (isNaN(max)) {
					max = min;
				}
				for (let i = min; i <= max; i++) {
					content += srcContent.replace(/ \{N\} / g, i + "") + "\n";
				}
			}
			else {
				content = content.replace(/ \{N\} / g, idxStr);
			}*/
		}
		
		str = replace(str, match[0].str(), _processImports(content));
	}
	return str;
}

int main()
{
	resources["hola"] = "Hola chicos";
	resources["light"] = "vec3 light_{N}";
	resources["fogFragment"] = "color.rgb = fog * color.rgb + (1.0 - fog) * vFogColor;";
	resources["adios"] = "Adios chicos";
	const std::string source =
		"#version 330 core\n"
		"void main() {\n"
		"	#import<hola>\n"
		"	gl_Position = vec4(1.0);\n"
		"	#import<light>[0..3]\n"
		"	#import<adios>\n"
		"import<fogFragment>(color=finalColor)\n"
		"}\n";
	std::string finalSource = _processImports(source);
	std::cout << finalSource << std::endl;
	char a;
	std::cin >> a;
	return 0;
}