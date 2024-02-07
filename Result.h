#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ResultLib {

// Forward declaration of the result class
template <typename ErrorT, typename ResultT = void> class Result;

// If it is empty
template<typename ErrorT>
class Result<ErrorT, void> {
public:
    static Result Ok() {
        Result res;
        res.m_type = OK;
        return res;
    }

    static Result Err() {
        Result res;
        res.m_type = ERR;
        return res;
    }

    static Result Err(ErrorT error) {
        Result res;
        res.m_type = ERR;
        res.m_error = error;
        return res;
    }

    bool is_ok() {
        return this->m_type == OK;
    }

    bool is_err() {
        return this->m_type == ERR;
    }

private:
    Result() = default;
    
    enum Type {
        OK,
        ERR
    };

    Type m_type;
    ErrorT m_error;
}; 

// If it is not empty
template <typename ErrorT, typename ResultT>
class Result {
public:
    static Result Ok() {
        Result res;
        res.m_type = OK;
        return res;
    }

    static Result Ok(ResultT result) {
        Result res;
        res.m_type = OK;
        res.m_data = result;
        return res;
    }

    static Result Err() {
        Result res;
        res.m_type = ERR;
        return res;
    }

    static Result Err(ErrorT error) {
        Result res;
        res.m_type = ERR;
        res.m_error = error;
        return res;
    }

    ResultT unwrap() {
        if (m_type == OK) {
            return m_data;
        } else {
            std::stringstream ss;
            ss << "Unwrapped an error with code: " << m_error;
            throw std::runtime_error(ss.str());
        }
    }

    ResultT except(std::string message) {
        if (m_type == OK) {
            return m_data;
        } else {
            throw std::runtime_error(message);
        }
    }

    bool is_ok() {
        return this->m_type == OK;
    }

    bool is_err() {
        return this->m_type == ERR;
    }

private:
    Result() = default;
    
    enum Type {
        OK,
        ERR
    };

    Type m_type;
    ErrorT m_error;
    ResultT m_data;
};

} // namspace ResultLib
