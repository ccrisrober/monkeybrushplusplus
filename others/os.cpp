namespace MB
{
	namespace os
	{
		void mkdir(const std::string& path)
		{
			#ifdef WIN32
				_mkdir(path.c_str());
			#else
                mkdir(path.c_str(), S_IRWXU);
			#endif
		}
		std::string path(const std::string& path)
		{
			std:.string aux = path;
			#ifdef WIN32
				strReplaceAll(aux, "/", "\\");
			#else
				strReplaceAll(aux, "\\", "/");
			#endif
			return aux;
		}
		bool isdir(const std::string& p)
		{
			std::string _path = path(p);
			#ifdef WIN32
                WIN32_FILE_ATTRIBUTE_DATA info;
                GetFileAttributesExA(_path.c_str(), GetFileExInfoStandard, &info);
                return (info.dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
                        (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
			#else
                struct stat info;
                stat(_path.c_str(), &info);
                return S_ISDIR(info.st_mode);
			#endif
                
            return false;
		}
		char path_delimiter()
		{
			char delimeter;
			#ifdef WIN32
				delimeter = '\\';
			#else
				delimeter = '/';
			#endif
			return delimeter;
		}

	private:
		void strReplaceAll(std::string& source, std::string const& find, std::string const& replace)
		{
		    for(std::string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
		    {
		        source.replace(i, find.length(), replace);
		        i += replace.length();
		    }
		}
	}
}