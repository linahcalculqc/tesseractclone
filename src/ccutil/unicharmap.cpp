///////////////////////////////////////////////////////////////////////
// File:        unicharmap.cpp
// Description: Unicode character/ligature to integer id class.
// Author:      Thomas Kielbus
//
// (C) Copyright 2006, Google Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////

#include "unicharmap.h"

#include <tesseract/unichar.h>

#include <cassert>

namespace tesseract {

// Search the given unichar representation in the tree, using length characters
// from it maximum. Each character in the string is interpreted as an index in
// an array of nodes.
UNICHAR_ID UNICHARMAP::unichar_to_id(const char* const unichar_repr,
                                     int length) const {
  assert(*unichar_repr != '\0');
  assert(length > 0 && length <= UNICHAR_LEN);

  std::string s{ unichar_repr,unichar_repr + length };
  auto i = find(s);
  if (i == end())
    return INVALID_UNICHAR_ID;
  return i->second;
}

// Search the given unichar representation in the tree, creating the possibly
// missing nodes. Once the right place has been found, insert the given id and
// update the inserted flag to keep track of the insert. Each character in the
// string is interpreted as an index in an array of nodes.
void UNICHARMAP::insert(const char* const unichar_repr, UNICHAR_ID id) {
  const char* current_char = unichar_repr;
  if (*current_char == '\0') return;

  std::string s{ unichar_repr };
  operator[](s) = id;
}

// Search the given unichar representation in the tree, using length characters
// from it maximum. Each character in the string is interpreted as an index in
// an array of nodes. Stop once the tree does not have anymore nodes or once we
// found the right unichar_repr.
bool UNICHARMAP::contains(const char* const unichar_repr,
                          int length) const {
  if (unichar_repr == nullptr || *unichar_repr == '\0') return false;
  if (length <= 0 || length > UNICHAR_LEN) return false;
  int index = 0;
  if (unichar_repr[index] == '\0') return false;
  std::string s{ unichar_repr,unichar_repr + length };
  return find(s) != end();
}

// Return the minimum number of characters that must be used from this string
// to obtain a match in the UNICHARMAP.
int UNICHARMAP::minmatch(const char* const unichar_repr) const {
  std::string s{ unichar_repr };
  std::string s2;
  s2.reserve(s.size());
  do {
      s2.push_back(s[s2.size()]);
      if (find(s2) != end())
          return s2.size();
  } while (s2.size() != s.size());


  /*UNICHARMAP_NODE* current_nodes = nodes;

  while (current_nodes != nullptr && *current_char != '\0') {
    if (current_nodes[static_cast<unsigned char>(*current_char)].id >= 0)
      return current_char + 1 - unichar_repr;
    current_nodes =
        current_nodes[static_cast<unsigned char>(*current_char)].children;
    ++current_char;
  }*/

  return 0;
}

} // namespace tesseract

