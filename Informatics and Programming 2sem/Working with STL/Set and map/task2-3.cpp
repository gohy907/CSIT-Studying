//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <map>
//#include <set>
//
//std::string tolowerString(std::string str) {
//	for (int i = 0; i < str.size(); ++i) {
//		str[i] = tolower(str[i]);
//	}
//	return str;
//}
//
//int main() {
//	std::ifstream in("input.txt");
//	std::string splitters = ".?!";
//	std::set<std::string> words;
//	std::map<std::string, bool> wordsMap;
//	wordsMap["test"];
//	std::vector<std::string> stc;
//	while (in.peek() != EOF) {
//		std::string str;
//		in >> str;
//		
//		char end = str[str.size() - 1];
//		if (splitters.find(end) != std::string::npos) {
//			std::string str1 = str.substr(0, str.size() - 1);
//			words.insert(str1);
//			stc.push_back(str1);
//			for (std::vector<std::string>::iterator it = stc.begin(); it != stc.end(); ++it) {
//				std::string tmp = tolowerString(*it);
//				if (end == '.' || (wordsMap.count(tmp) && !wordsMap[tmp])) wordsMap[tmp] = false;
//				else wordsMap[tmp] = true;
//			}
//			stc.clear();
//		}
//		else {
//			words.insert(str);
//			stc.push_back(str);
//		}
//	}
//
//	for (std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
//		if (wordsMap[tolowerString(*it)]) std::cout << *it << std::endl;
//	}
//}
//
