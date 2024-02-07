#include <cstdint>
#include <stdexcept>
#include <string>

// Forward declaration of the result class
template <typename ResultT = void> class Result;

// If it is empty
template<> class Result<void> {
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
}; 

// If it is not empty
template <typename ResultT>
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

    ResultT unwrap() {
        if (m_type == OK) {
            return m_data;
        } else {
            throw std::runtime_error("Unwrapped an error!");
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
    ResultT m_data;
};
