#pragma once

#include <exception>
#include <string>

class ImageProcessorException : public std::exception {
public:
    const char* what() const throw() override = 0;
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message = "Parser exception") : msg_(message) {
    }
    const char* what() const throw() override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class ControllerException : public ImageProcessorException {
public:
    explicit ControllerException(const std::string& message = "Controller exception") : msg_(message) {
    }
    const char* what() const throw() override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class BMPException : public ImageProcessorException {
public:
    explicit BMPException(const std::string& message = "BMP exception") : msg_(message) {
    }
    const char* what() const throw() override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class FilterException : public ImageProcessorException {
public:
    explicit FilterException(const std::string& message = "BMP exception") : msg_(message) {
    }
    const char* what() const throw() override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};