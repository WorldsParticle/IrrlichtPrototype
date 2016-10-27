#ifndef PARAM_HPP
#define PARAM_HPP

#include <string>

namespace gen
{

class Param
{
public:

    enum paramType
    {
        intvalue
    };

    ///
    /// \brief ~Param
    ///
    virtual ~Param() {}

    ///
    /// \brief name getter
    /// \return name
    ///
    inline const std::string &name()
    { return m_name; }

    ///
    /// \brief type getter
    /// \return type
    ///
    inline paramType type()
    { return m_type; }

    inline void setName(const std::string &namee)
    { m_name = namee; }

protected:
    ///
    /// \brief Param default constructor
    /// \param name
    ///
    Param(paramType type, const std::string &name = "") :
        m_type(type),
        m_name(name)
    {}

    paramType   m_type;
    std::string m_name;
};

}

#endif /* PARAM_HPP */
