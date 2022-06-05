#ifndef UTILS_H
#define UTILS_H
#include <string>
using std::string;
//dsiable warning 4996 for the codecvt lib as it is marked deprecated, but there is actually no alternative so uhh
#pragma warning (push)
#pragma warning (disable:4996) 
#include <codecvt>
#include <locale>
#include <filesystem> // C++17#
namespace util {

	inline std::wstring s_to_ws(const string& str) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	inline string ws_to_s(const std::wstring& wstr) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	inline string extension(const string& path) {
		namespace fs = std::filesystem; {
			fs::path filePath = path;
			if (filePath.has_extension()) {
				//get extension without the dot, as per stl standard the extension() returns with a dot!
				return filePath.extension().string().substr(1);
			}
			else {
				return string();
			}
		}
	}
#pragma warning (pop) //enable 4996 deprecated again

	inline string read_file_to_string(const string& path) {
		//vars we need, filesize and result strign
		struct stat sb {};
		std::wstring res;

		//get fd and check for error
		FILE* input_file;
		fopen_s(&input_file, path.c_str(), "r");
		if (input_file == nullptr) {
			perror("File doesn't exist");
		}
		else {
			//get size
			stat(path.c_str(), &sb);
			res.resize(sb.st_size);
			//read in file contents
			fread_s(const_cast<wchar_t*>(res.data()), sb.st_size, sb.st_size, 1, input_file);
			//close again
			fclose(input_file);
		}

		return ws_to_s(res);
	}

	template <class T> void SafeRelease(T** ppT) {
		if (*ppT) {
			(*ppT)->Release();
			*ppT = NULL;
		}
	}
}

#endif // !UTILS_H
