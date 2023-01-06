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

#include "./interfaces/subtitle.hpp"

namespace Application {

    namespace ASS {

        class ASSTimestamp: public Application::Interface::Timestamp, public Application::Interface::TimestampOperations<Application::ASS::ASSTimestamp> {

            private:

            std::uint64_t hours;
            std::uint64_t minutes;
            std::uint64_t seconds;
            std::uint64_t centiseconds;

            public:

            // Constructors

            ASSTimestamp();
            ASSTimestamp(std::uint64_t hours, std::uint64_t minutes, std::uint64_t seconds, std::uint64_t centiseconds);
            static ASSTimestamp fromString(std::string inputString);
            static ASSTimestamp fromDuration(std::uint64_t duration);

            // Interface's methods

            virtual void add(Application::ASS::ASSTimestamp inputTimestamp);
            virtual void subtract(Application::ASS::ASSTimestamp inputTimestamp);
            virtual void divideByTimestamp(Application::ASS::ASSTimestamp inputTimestamp);
            virtual void divideByNumber(std::uint64_t inputValue);

            virtual Application::ASS::ASSTimestamp& operator += (Application::ASS::ASSTimestamp const& timestamp);
            virtual Application::ASS::ASSTimestamp operator + (Application::ASS::ASSTimestamp const& timestamp) const;
            virtual Application::ASS::ASSTimestamp& operator -= (Application::ASS::ASSTimestamp const& timestamp);
            virtual Application::ASS::ASSTimestamp operator - (Application::ASS::ASSTimestamp const& timestamp) const;
            virtual Application::ASS::ASSTimestamp& operator /= (Application::ASS::ASSTimestamp const& timestamp);
            virtual Application::ASS::ASSTimestamp operator / (Application::ASS::ASSTimestamp const& timestamp) const;
            virtual Application::ASS::ASSTimestamp& operator /= (std::uint64_t value);
            virtual Application::ASS::ASSTimestamp operator / (std::uint64_t value) const;

            // Setters

            virtual void setDuration(std::uint64_t duration);
            virtual void setHours(std::uint64_t hours);
            virtual void setMinutes(std::uint64_t minutes);
            virtual void setSeconds(std::uint64_t seconds);
            virtual void setCentiseconds(std::uint64_t centiseconds);

            // Getters

            virtual std::string getFormattedString(void) const;
            virtual std::uint64_t getDuration(void) const;
            virtual std::uint64_t getHours(void) const;
            virtual std::uint64_t getMinutes(void) const;
            virtual std::uint64_t getSeconds(void) const;
            virtual std::uint64_t getCentiseconds(void) const;

        };

    }

}