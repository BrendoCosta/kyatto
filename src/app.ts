import * as KyattoCoreASS from "@kyatto/ass";

let a: KyattoCoreASS.ASSTimestamp = KyattoCoreASS.ASSTimestamp.fromString("1:00:00.00");
a.divideByNumber(4);
console.log(a.toFormattedString());