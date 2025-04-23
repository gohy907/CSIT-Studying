#include <cctype>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

int prior(std::string token) {
  if (token == "+" || token == "-") {
    return 1;
  }
  if (token == "*" || token == "/") {
    return 2;
  }
  return 0;
}

std::vector<std::string> tokenize(std::string s) {
  std::vector<std::string> tokens;
  std::string current;
  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (isspace(c)) {
      if (!current.empty()) {
        tokens.push_back(current);
        current.clear();
      }
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
      if (!current.empty()) {
        tokens.push_back(current);
        current.clear();
      }
      std::string c1 = "";
      c1 += c;
      tokens.push_back(c1);
    } else {
      current += c;
    }
  }
  if (!current.empty()) {
    tokens.push_back(current);
  }
  return tokens;
}
std::vector<std::string> infixToPrefixHelper(std::vector<std::string> tokens,
                                             int start, int end) {
  if (start > end) {
    return {};
  }
  if (start == end) {
    return {tokens[start]};
  }

  bool hasOuterParentheses = false;
  if (tokens[start] == "(" && tokens[end] == ")") {
    int balance = 1;
    for (int i = start + 1; i <= end - 1; ++i) {
      if (tokens[i] == "(") {
        balance++;
      } else if (tokens[i] == ")") {
        balance--;
      }
      if (balance == 0) {
        break;
      }
    }
    if (balance == 1) {
      hasOuterParentheses = true;
      start++;
      end--;
    }
  }

  int minPriority = INT_MAX;
  int splitIndex = -1;
  int balance = 0;
  for (int i = start; i <= end; ++i) {
    std::string token = tokens[i];
    if (token == "(")
      balance++;
    else if (token == ")")
      balance--;
    else if (balance == 0) {
      int priority = prior(token);
      if (priority == 0) {
        continue;
      }
      if (priority <= minPriority) {
        minPriority = priority;
        splitIndex = i;
      }
    }
  }

  if (splitIndex != -1) {
    std::vector<std::string> left =
        infixToPrefixHelper(tokens, start, splitIndex - 1);
    std::vector<std::string> right =
        infixToPrefixHelper(tokens, splitIndex + 1, end);
    std::vector<std::string> result = {tokens[splitIndex]};
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
  }

  return infixToPrefixHelper(tokens, start, end);
}

std::string infixToPrefix(std::string in) {
  std::vector<std::string> tokens = tokenize(in);
  if (tokens.empty()) {
    return "";
  }
  std::vector<std::string> prefixTokens =
      infixToPrefixHelper(tokens, 0, tokens.size() - 1);

  std::string result;
  for (int i = 0; i < prefixTokens.size(); ++i) {
    std::string token = prefixTokens[i];
    result += token;
  }
  return result;
}

int main() {
  std::string in;
  std::cin >> in;
  std::cout << infixToPrefix(in) << std::endl;
}
