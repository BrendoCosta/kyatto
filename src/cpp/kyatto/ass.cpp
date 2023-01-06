/*
    MIT License

    Copyright (c) 2022 Brendo Costa

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <cmath>
#include <sstream>

#include "ass.hpp"
#include "./utils/string.hpp"

Application::ASS::ASSTimestamp::ASSTimestamp() {

    this->hours        = 0;
    this->minutes      = 0;
    this->seconds      = 0;
    this->centiseconds = 0;
    
}

Application::ASS::ASSTimestamp::ASSTimestamp(std::uint64_t hours, std::uint64_t minutes, std::uint64_t seconds, std::uint64_t centiseconds) {

    this->hours        = hours;
    this->minutes      = minutes;
    this->seconds      = seconds;
    this->centiseconds = centiseconds;
    
}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::fromString(std::string inputString) {

    std::vector<std::string> tokens = Application::Utils::String::split(inputString, "[:.]");
    std::vector<std::uint64_t> values;

    for (std::string& tkn: tokens) {

        values.push_back(std::stoul(tkn));

    }

    return Application::ASS::ASSTimestamp(
        values[0],
        values[1],
        values[2],
        values[3]
    );
    
}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::fromDuration(std::uint64_t duration) {

    return Application::ASS::ASSTimestamp(
        std::floor((duration / (100 * 60 * 60)) % 24),
        std::floor((duration / (100 * 60)) % 60),
        std::floor((duration / 100) % 60),
        std::floor((duration) % 100)
    );

}

void Application::ASS::ASSTimestamp::add(Application::ASS::ASSTimestamp inputTimestamp) {

    this->setDuration(this->getDuration() + inputTimestamp.getDuration());

    return;

};

void Application::ASS::ASSTimestamp::subtract(Application::ASS::ASSTimestamp inputTimestamp) {

    this->setDuration(this->getDuration() - inputTimestamp.getDuration());

    return;

};

void Application::ASS::ASSTimestamp::divideByTimestamp(Application::ASS::ASSTimestamp inputTimestamp) {

    this->setDuration(this->getDuration() / inputTimestamp.getDuration());

    return;

};

void Application::ASS::ASSTimestamp::divideByNumber(std::uint64_t inputValue) {

    this->setDuration(this->getDuration() / inputValue);

    return;
    
};

Application::ASS::ASSTimestamp& Application::ASS::ASSTimestamp::operator += (Application::ASS::ASSTimestamp const& timestamp) {

    this->add(timestamp);

    return *this;

}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::operator + (Application::ASS::ASSTimestamp const& timestamp) const {

    Application::ASS::ASSTimestamp aux = *this;
    aux += timestamp;
    
    return aux;

}

Application::ASS::ASSTimestamp& Application::ASS::ASSTimestamp::operator -= (Application::ASS::ASSTimestamp const& timestamp) {

    this->subtract(timestamp);

    return *this;

}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::operator - (Application::ASS::ASSTimestamp const& timestamp) const {

    Application::ASS::ASSTimestamp aux = *this;
    aux -= timestamp;
    
    return aux;

}

Application::ASS::ASSTimestamp& Application::ASS::ASSTimestamp::operator /= (Application::ASS::ASSTimestamp const& timestamp) {

    this->divideByTimestamp(timestamp);

    return *this;

}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::operator / (Application::ASS::ASSTimestamp const& timestamp) const {

    Application::ASS::ASSTimestamp aux = *this;
    aux /= timestamp;
    
    return aux;

}

Application::ASS::ASSTimestamp& Application::ASS::ASSTimestamp::operator /= (std::uint64_t value) {

    this->divideByNumber(value);

    return *this;

}

Application::ASS::ASSTimestamp Application::ASS::ASSTimestamp::operator / (std::uint64_t value) const {

    Application::ASS::ASSTimestamp aux = *this;
    aux /= value;
    
    return aux;

}

void Application::ASS::ASSTimestamp::setDuration(std::uint64_t duration) {

    this->setHours(std::floor((duration / (100 * 60 * 60)) % 24));
    this->setMinutes(std::floor((duration / (100 * 60)) % 60));
    this->setSeconds(std::floor((duration / 100) % 60));
    this->setCentiseconds(std::floor((duration) % 100));

    return;

}

void Application::ASS::ASSTimestamp::setHours(std::uint64_t hours) { this->hours = hours; };
void Application::ASS::ASSTimestamp::setMinutes(std::uint64_t minutes) { this->minutes = minutes; };
void Application::ASS::ASSTimestamp::setSeconds(std::uint64_t seconds) { this->seconds = seconds; };
void Application::ASS::ASSTimestamp::setCentiseconds(std::uint64_t centiseconds) { this->centiseconds = centiseconds; };

std::string Application::ASS::ASSTimestamp::getFormattedString(void) const {

    std::stringstream stream;

    stream << std::to_string(this->hours);
    stream << std::string(":");
    stream << (this->minutes < 10 ? std::string("0") + std::to_string(this->minutes) : std::to_string(this->minutes));
    stream << std::string(":");
    stream << (this->seconds < 10 ? std::string("0") + std::to_string(this->seconds) : std::to_string(this->seconds));
    stream << std::string(".");
    stream << (this->centiseconds < 10 ? std::string("0") + std::to_string(this->centiseconds) : std::to_string(this->centiseconds));

    return stream.str();

}

std::uint64_t Application::ASS::ASSTimestamp::getDuration(void) const {
    
    return (this->getHours() * 360000) + (this->getMinutes() * 6000) + (this->getSeconds() * 100) + this->getCentiseconds();
    
}

std::uint64_t Application::ASS::ASSTimestamp::getHours(void) const { return this->hours; }
std::uint64_t Application::ASS::ASSTimestamp::getMinutes(void) const { return this->minutes; }
std::uint64_t Application::ASS::ASSTimestamp::getSeconds(void) const { return this->seconds; }
std::uint64_t Application::ASS::ASSTimestamp::getCentiseconds(void) const { return this->centiseconds; }