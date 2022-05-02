#ifndef _MD_H_
#define _MD_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class MDTable {
private:
  vector<size_t> _colSize;
  vector<string> _header;
  vector<vector<string> > _data;

  string _indentation;
public:
  MDTable(const vector<string> header, size_t indC = 2);

  void addRow(const vector<string>& row);

  friend std::ostream& operator<< (std::ostream& stream, const MDTable& table);
};

#endif

