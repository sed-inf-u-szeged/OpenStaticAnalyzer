
#ifndef RulHandlerException_H_
#define RulHandlerException_H_

#include <string>
#include <Exception.h>

namespace columbus {

namespace rul {

class RulHandlerException : public columbus::Exception {
public:
  RulHandlerException(const std::string &location, const std::string &message) : Exception(location, message) {}

  virtual const std::string getClassName() const
  {
    return "columbus::rul::RulHandlerException";
  }
};

} // namespace rul

} // namespace columbus

#endif /* RulHandlerException_H_ */
