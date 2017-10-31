/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#ifndef _COLUMBUS_EXCEPTION_H_
#define _COLUMBUS_EXCEPTION_H_

#include <string>

#define COLUMBUS_STRINGIFY(x) #x
#define COLUMBUS_TOSTRING(x) COLUMBUS_STRINGIFY(x)
#define COLUMBUS_LOCATION __FILE__ ":" COLUMBUS_TOSTRING(__LINE__)

namespace columbus {

/** 
* Class for exception handling, with location and error message.
*/  
class Exception {
public:
  /** 
  * Requires error message and location parameters.
  *
  * \param location the place where the error is occured
  * \param message errormessage
  */  
  Exception(const std::string &location, const std::string &message) : loc(location), msg(message) {}
  /**
  * Destructor.
  */  
  virtual ~Exception() {}
  /** 
  * Returns a readable string of the error.
  * \return exception class name, location of the error and te error message as string
  */  
  const std::string toString() const  {return getClassName() + "@" + getLocation() + ": " + getMessage();}
  /** 
  * Returns the class of exception.
  */  
  virtual const std::string getClassName() const  {return "columbus::Exception";}
  /** 
  * Returns the location of the error.
  * \return location of error
  */  
  const std::string& getLocation() const  {return loc;}
  /** 
  * Returns the message of the error.
  */  
  const std::string& getMessage() const  {return msg;}
private:
  std::string loc;
  std::string msg;
};

class IOException: public Exception {
  public:
    IOException(const std::string &location, const std::string &message) : Exception(location, message) {
    }
    
    virtual const std::string getClassName() const {
      return "columbus::IOException";
    }
};

}

#endif

