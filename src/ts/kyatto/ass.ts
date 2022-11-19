/** @module ASS */
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

import * as SubtitleInterface from "./interfaces/subtitle";

/*
 * @class module:ASS.ASSTimestamp
 * @access public
 * @name ASSTimestamp
 * @classdesc Not a real class but an interface. Etc...
*/
export class ASSTimestamp implements SubtitleInterface.Timestamp {

    private hours: number = 0;
    private minutes: number = 0;
    private seconds: number = 0;
    private centiseconds: number = 0;

    /**
     * Creates a new ASSTimestamp object with given values.
     * @access public
     * @constructor
     * @param {number} hours Hours
     * @param {number} minutes Minutes
     * @param {number} seconds Seconds
     * @param {number} centiseconds Centiseconds
    */
    public constructor(hours: number, minutes: number, seconds: number, centiseconds: number) {

        this.hours        = hours;
        this.minutes      = minutes;
        this.seconds      = seconds;
        this.centiseconds = centiseconds;

    }

    /**
     * @access public
     * @name fromString
     * @method module:ASS.ASSTimestamp#fromString
     * @static
     * @description Creates an ASSTimestamp object from an timestamp string input in ASS format.
     * @param {string} inputString HH:MM:SS.CS formatted string 
     * @returns {ASSTimestamp} ASSTimestamp object
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public static fromString(inputString: string): ASSTimestamp {

        let inputTimestamp: Array<number> = [];

        inputString.split(/[:.]/).map((value: string) => { inputTimestamp.push(Number(value)); });

        return new ASSTimestamp(
            inputTimestamp[0],
            inputTimestamp[1],
            inputTimestamp[2],
            inputTimestamp[3],
        );

    }

    /**
     * @access public
     * @name fromDuration
     * @method module:ASS.ASSTimestamp#fromDuration
     * @static
     * @description Creates an ASSTimestamp object for a given centisecond duration input. It should be noted that this function rounds the input down to the previous closest integer. 
     * @param {number} duration - An integer duration in centiseconds
     * @returns {ASSTimestamp} ASSTimestamp object
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public static fromDuration(duration: number): ASSTimestamp {

        return new ASSTimestamp(
            Math.floor((duration / (100 * 60 * 60)) % 24),
            Math.floor((duration / (100 * 60)) % 60),
            Math.floor((duration / 100) % 60),
            Math.floor((duration) % 100),
        );

    }

    /**
     * @access public
     * @name getDuration
     * @method module:ASS.ASSTimestamp#getDuration
     * @description Returns the timestamp's duration in centiseconds.
     * @returns {number} Timestamp's duration in centiseconds
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public getDuration(): number {

        return (this.getHours() * 360000) + (this.getMinutes() * 6000) + (this.getSeconds() * 100) + this.getCentiseconds();

    }

    /**
     * @access public
     * @name setDuration
     * @method module:ASS.ASSTimestamp#setDuration
     * @description Sets the timestamp's duration based on the given centiseconds input. It should be noted that this function rounds the input down to the previous closest integer. 
     * @param {number} duration An integer representing the duration in centiseconds
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public setDuration(duration: number): void {

        this.setHours(Math.floor((duration / (100 * 60 * 60)) % 24));
        this.setMinutes(Math.floor((duration / (100 * 60)) % 60));
        this.setSeconds(Math.floor((duration / 100) % 60));
        this.setCentiseconds(Math.floor((duration) % 100));

    }

    /**
     * @access public
     * @name add
     * @method module:ASS.ASSTimestamp#add
     * @description Sums the input timestamp's duration to the current timestamp's duration.
     * @param {ASSTimestamp} inputTimestamp An ASSTimestamp object
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public add(inputTimestamp: ASSTimestamp): void {

        this.setDuration(this.getDuration() + inputTimestamp.getDuration());
        
    }

    /**
     * @access public
     * @name subtract
     * @method module:ASS.ASSTimestamp#subtract
     * @description Subtracts the input timestamp's duration from the current timestamp's duration.
     * @param {ASSTimestamp} inputTimestamp An ASSTimestamp object
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public subtract(inputTimestamp: ASSTimestamp): void {

        this.setDuration(this.getDuration() - inputTimestamp.getDuration());

    }

    /**
     * @access public
     * @name divideByTimestamp
     * @method module:ASS.ASSTimestamp#divideByTimestamp
     * @description Divides the current timestamp's duration by the input timestamp's duration.
     * @param {ASSTimestamp} inputTimestamp An ASSTimestamp object
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public divideByTimestamp(inputTimestamp: ASSTimestamp): void {

        this.setDuration(this.getDuration() / inputTimestamp.getDuration());

    }

    /**
     * @access public
     * @name divideByNumber
     * @method module:ASS.ASSTimestamp#divideByNumber
     * @description Divides the current timestamp's duration by the input number.
     * @param {number} inputValue An arbitrary number
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public divideByNumber(inputValue: number): void {

        this.setDuration(this.getDuration() / inputValue);

    }

    /**
     * @access public
     * @name toFormattedString
     * @method module:ASS.ASSTimestamp#toFormattedString
     * @description Returns a string representing the current timestamp's duration in ASS format.
     * @returns {string} HH:MM:SS.CS formatted string representing the current timestamp's duration
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public toFormattedString(): string {

        let timestamp: string = `${this.getHours()}:${("0" + this.getMinutes()).slice(-2)}:${("0" + this.getSeconds()).slice(-2)}.${("0" + this.getCentiseconds()).slice(-2)}`;
        
        return timestamp;
        
    }

    // Get

    /**
     * @access public
     * @name getHours
     * @method module:ASS.ASSTimestamp#getHours
     * @returns {number}
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public getHours(): number { return this.hours; }

    /**
     * @access public
     * @name getMinutes
     * @method module:ASS.ASSTimestamp#getMinutes
     * @returns {number}
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public getMinutes(): number { return this.minutes; }

    /**
     * @access public
     * @name getSeconds
     * @method module:ASS.ASSTimestamp#getSeconds
     * @returns {number}
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public getSeconds(): number { return this.seconds; }

    /**
     * @access public
     * @name getCentiseconds
     * @method module:ASS.ASSTimestamp#getCentiseconds
     * @returns {number}
     * @author Brendo Costa <brendocosta@id.uff.br>
     * @since -
    */
    public getCentiseconds(): number { return this.centiseconds; }

    // Set

    public setHours(value: number): void { this.hours = value; }
    public setMinutes(value: number): void { this.minutes = value; }
    public setSeconds(value: number): void { this.seconds = value; }
    public setCentiseconds(value: number): void { this.centiseconds = value; }

}

