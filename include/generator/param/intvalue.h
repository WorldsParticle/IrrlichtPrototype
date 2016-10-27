#ifndef INTVALUE_HPP
#define INTVALUE_HPP

#include "param.h"

namespace gen
{

class IntValue : public Param
{
public:

    ///
    /// \brief IntValue default constructor
    /// \param name
    ///
    IntValue(const std::string &namee = "") :
        Param(intvalue, namee),
        m_minValue(0),
        m_maxValue(100),
        m_value(0)
    {}

    ///
    /// \brief ~IntValue
    ///
    virtual ~IntValue() {}

    ///
    /// \brief setMinValue
    ///
    inline  void    setMinValue(int minValuee)
    { m_minValue = minValuee; }

    ///
    /// \brief setMaxValue
    ///
    inline  void    setMaxValue(int maxValuee)
    { m_maxValue = maxValuee; }

    ///
    /// \brief setValue
    ///
    inline  void    setValue(int valuee)
    { m_value = valuee; }

    ///
    /// \brief minValue getter
    ///
    inline int      minValue()
    { return m_minValue; }

    ///
    /// \brief minValue getter
    ///
    inline int      maxValue()
    { return m_maxValue; }

    ///
    /// \brief minValue getter
    ///
    inline int      value()
    { return m_value; }


private:
    int     m_minValue;
    int     m_maxValue;
    int     m_value;
};

}

#endif /* PARAM_HPP */
