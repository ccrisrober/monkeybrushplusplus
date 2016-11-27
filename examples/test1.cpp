
#include <mb/mb.h>

using MB::ArgumentParser;
int main(int argc, const char** argv)
{
	ArgumentParser parser = ArgumentParser().description("just an example");

	parser.add_option("-f", "--file").dest("filename")
		.help("write report to FILE").metavar("FILE");
	parser.add_option("-q", "--quiet")
		.action("store_false").dest("verbose").set_default("1")
		.help("don't print status messages to stdout");

	parser.print_help();
	parser.print_version();

	MB::Values options = parser.parse_args(argc, argv);
	std::vector<std::string> args = parser.args();
	if (options.get("verbose"))
		std::cout << options["filename"] << std::endl;
	return 0;
}
