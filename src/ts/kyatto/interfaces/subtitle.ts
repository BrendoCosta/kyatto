/*
    MIT License

    Copyright (c) 2021 Brendo Costa

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

/**
 * SSA = "Sub Station Alpha",
 * ASS = "Advanced Sub Station Alpha",
 * SRT = "SubRip Text"
*/
    
export interface SubtitleFormat {

    formatName: string;
    formatExtension: string;
    formatVersion: string;

}

export interface Timestamp {

    add(inputTimestamp: Timestamp): void;
    subtract(inputTimestamp: Timestamp): void;
    divideByTimestamp(inputTimestamp: Timestamp): void;
    divideByNumber(inputValue: number): void;
    toFormattedString(): string;

}

export interface SubtitleLine {

    getData(): ArrayBuffer;
    getTimestamp(): Timestamp;

}

export interface SubtitleData {

    getSubtitleFormat(): string;
    getSubtitleFormatVersion(): string;
    getSubtitleFormatExtension(): string;
    shiftTo(timestamp: Timestamp): void;
    cut(start: Timestamp, end: Timestamp): void;
    paste(lines: Array<SubtitleLine>): void;

}

export interface SubtitleMetadata { }
export interface SubtitleDataWithMetadata {

    getMetadata(): SubtitleMetadata;

}

export interface SubtitleParser {

    importFromBuffer(buffer: ArrayBuffer): void;
    exportToBuffer(): ArrayBuffer;
    parse(): void;

}