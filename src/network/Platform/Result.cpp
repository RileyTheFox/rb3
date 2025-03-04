#include "Platform/Result.h"

namespace Quazal {

    qResult::qResult() : m_iReturnCode(0x80010001), m_cszFilename(__FILE__), m_iLineNumber(0x14) {

    }

    qResult::qResult(const int& i) : m_iReturnCode(i), m_cszFilename(__FILE__), m_iLineNumber(0x1B) {

    }

    bool qResult::Equals(const int& i) const { return m_iReturnCode == i; }

    bool qResult::Equals(const bool& b) const {
        return (m_iReturnCode == 0) == b;
    }

    qResult::operator bool() const {
        return m_iReturnCode == 0;
    }

    qResult& qResult::operator=(const int& i){
        m_iReturnCode = i;
        m_cszFilename = __FILE__;
        m_iLineNumber = 0x59;
    }

    qResult& qResult::operator=(const qResult& q){
        m_iReturnCode = q.m_iReturnCode;
        m_cszFilename = q.m_cszFilename;
        m_iLineNumber = q.m_iLineNumber;
    }

    void qResult::Trace(unsigned int) const {}

}
