#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ResultLib {

class BaseResult {
public:
    static BaseResult Ok() {
        BaseResult res;
        res.m_type = OK;
        return res;
    }

    static BaseResult Err() {
        BaseResult res;
        res.m_type = ERR;
        return res;
    }

    inline bool is_ok() const {
        return this->m_type == OK;
    }

    inline bool is_err() const {
        return this->m_type == ERR;
    }

protected:
    BaseResult() = default;
    
    enum Type {
        OK,
        ERR
    };

    Type m_type;
};

template <typename ErrorT> 
class ResultCode : public BaseResult {
public:
    static ResultCode Ok() {
        ResultCode res;
        res.m_type = OK;
        return res;
    }

    static ResultCode Err() {
        ResultCode res;
        res.m_type = ERR;
        return res;
    }

    static ResultCode Err(ErrorT error) {
        ResultCode res;
        res.m_type = ERR;
        res.m_error = error;
        return res;
    }

    inline ErrorT get_status() const {
        return this->m_error;
    }

protected:
    ResultCode() = default;
    
    ErrorT m_error;
};

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

    inline ErrorT get_status() const {
        return this->m_error;
    }

    inline bool is_ok() const {
        return this->m_type == OK;
    }

    inline bool is_err() const {
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

    ResultT unwrap() const {
        if (m_type == OK) {
            return m_data;
        } else {
            std::stringstream ss;
            ss << "Unwrapped an error with code: " << m_error;
            throw std::runtime_error(ss.str());
        }
    }

    ResultT except(std::string &message) const {
        if (m_type == OK) {
            return m_data;
        } else {
            throw std::runtime_error(message);
        }
    }

    inline ErrorT get_status() const {
        return this->m_error;
    }

    inline bool is_ok() const {
        return this->m_type == OK;
    }

    inline bool is_err() const {
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

} // namespace ResultLib
