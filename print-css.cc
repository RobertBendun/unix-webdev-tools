/*
  MIT License

  Copyright (c) 2019 Robert Bendun

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

auto trim(std::string &s) -> std::string&
{
  auto const isSpace = [](char c) { return std::isspace(static_cast<int>(c)); };

  auto const whitespaceAtFront = std::find_if_not(s.begin(), s.end(), isSpace);
  s.erase(std::begin(s), whitespaceAtFront);

  auto const whitespaceAtBack = std::find_if_not(s.rbegin(), s.rend(), isSpace).base();
  s.erase(whitespaceAtBack, std::end(s));
  
  return s;
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "syntax: " << argv[0] << " <file-to-make-greppable|->\n";
    return 1;
  }

  std::ifstream file;
  auto &stream = [&]() -> std::istream&
  {
    if (argv[1] == std::string("-"))
      return std::cin;
    else {
      file.open(argv[1]);
      return file;
    }
  }();

  if (&file == &stream && !file.is_open()) {
    std::cerr << "Unable to open file: " << argv[1] << '\n';
    return 2;
  }

  for (std::string selector; std::getline(stream, selector, '{'); ) {
    trim(selector);

    // handle @import statements
    auto it = std::find(std::begin(selector), std::end(selector), ';');
    if (it != std::end(selector)) {
      std::cout << std::string(std::begin(selector), it) << ";\n";
      selector.erase(std::begin(selector), std::next(it));
      trim(selector);
    }

    while (true) {
      std::string declaration; 
      char c;
      while ((c = stream.get()) != std::char_traits<char>::eof() && c != '}' && c != ';')
        declaration += c;

      if (trim(declaration).size() == 0)
        break;

      std::cout << selector << " { " << declaration << "; }\n";
      if (c == '}' || c == std::char_traits<char>::eof())
        break;
    }
  }

  if (file.is_open())
    file.close();
}
