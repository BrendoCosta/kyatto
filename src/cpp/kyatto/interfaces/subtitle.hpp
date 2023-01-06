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

#ifndef INTERFACE_SUBTITLE_HPP_INCLUDED
#define INTERFACE_SUBTITLE_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

namespace Application {

    namespace Interface {

        class SubtitleFormat {

            public:

            virtual std::string getSubtitleFormatName(void) = 0;
            virtual std::string getSubtitleFormatExtension(void) = 0;
            virtual std::string getSubtitleFormatVersion(void) = 0;

        };

        class SubtitleMetadata {

            // TODO

        };

        template <class T>
        class TimestampOperations {

            public:

            virtual void add(T inputTimestamp) {};
            virtual void subtract(T inputTimestamp) = 0;
            virtual void divideByTimestamp(T inputTimestamp) = 0;
            virtual void divideByNumber(std::uint64_t inputValue) = 0;
            
            virtual T& operator += (T const& timestamp) = 0;
            virtual T operator + (T const& timestamp) const = 0;
            virtual T& operator -= (T const& timestamp) = 0;
            virtual T operator - (T const& timestamp) const = 0;
            virtual T& operator /= (T const& timestamp) = 0;
            virtual T operator / (T const& timestamp) const = 0;
            virtual T& operator /= (std::uint64_t value) = 0;
            virtual T operator / (std::uint64_t value) const = 0;

        };

        class Timestamp {

            public:

            virtual void setDuration(std::uint64_t duration) = 0;
            virtual std::string getFormattedString(void) const = 0;
            virtual std::uint64_t getDuration(void) const = 0;

        };

        class SubtitleLine {

            public:

            virtual std::vector<std::string> getText(void) const = 0;
            virtual Timestamp getTimestamp(void) const = 0;

        };

        class SubtitleData {

            public:

            virtual SubtitleFormat getSubtitleFormat(void) const = 0;
            virtual void shiftTo(Timestamp& timestamp) = 0;
            virtual void cut(Timestamp& start, Timestamp& end) = 0;
            virtual void paste(std::vector<SubtitleLine>& lines) = 0;

        };

        class SubtitleDataWithMetadata {

            public:

            virtual SubtitleMetadata getMetadata(void) = 0;

        };

        class SubtitleParser {

            public:

            virtual void importFromBuffer(std::vector<std::string>& inputBuffer) = 0;
            virtual void exportToBuffer(std::vector<std::string>& outputBuffer) = 0;
            virtual void parse(void) = 0;

        };

    }

}

#endif // INTERFACE_SUBTITLE_HPP_INCLUDED