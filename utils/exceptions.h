//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_EXCEPTIONS_H
#define UPRUN_EXCEPTIONS_H

#include <stdexcept>


namespace game {
    namespace error {
        class basicError : public std::exception {
        public:
            basicError() = default;

            basicError(const std::string &err) : strErr(err) {}

            virtual ~basicError() noexcept = default;

            const char *what() const noexcept override {
                return strErr.c_str();
            }

        private:
            std::string strErr;
        };

        class configFileReadError : public basicError {
        public:
            configFileReadError(const std::string &err) : basicError(err) {}
        };

        class textureNotFound : public basicError {
        public:
            textureNotFound(const std::string &err) : basicError(err) {}
        };

        class fontNotFound : public basicError {
        public:
            fontNotFound(const std::string &err) : basicError(err) {}
        };

    }
}


#endif //UPRUN_EXCEPTIONS_H
