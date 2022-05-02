#include "../inc/MD.h"

#include <iomanip>

MDTable::MDTable(const vector<string> header, size_t indC /* = 2 */) : 
    _colSize(header.size()),
    _header(header),
    _indentation(string(indC, ' '))
{
  for(size_t i=0; i<_header.size(); i++){
    _colSize[i] = _header[i].length();
  }
}


void MDTable::addRow(const vector<string>& row){
    _data.push_back(row);
    for(size_t i=0; i<_header.size(); i++){
      if(_colSize[i] < row[i].length())
        _colSize[i] = row[i].length();
    }
}

std::ostream& operator <<(std::ostream& stream, const MDTable& table) {

  // head
  stream << table._indentation;
  for(size_t i=0; i<table._header.size(); i++){
    stream << (i==0?"":" ") << left << setw(table._colSize[i] + 1) << table._header[i];
  }
  stream << endl;

  //line
  stream << table._indentation << setfill('-');
  for(size_t i=0; i<table._header.size(); i++){
    stream << (i==0?"":" ") << left << setw(table._colSize[i] + 1) << "-";
  }
  stream << endl;
  
  //data
  stream << setfill(' ');
  for(vector<vector<string> >::const_iterator row = table._data.begin(); row != table._data.end(); ++row){
    stream << table._indentation;
    for(size_t i=0; i<table._header.size(); i++){
      stream << (i==0?"":" ") << left << setw(table._colSize[i] + 1) << row->at(i);
    }
    stream << endl;
  }
  stream << endl;
  return stream;
}


