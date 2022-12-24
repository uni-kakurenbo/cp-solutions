/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language Node.js */

function main([S]) {
    if(/^[A-Z][1-9]\d{5,5}[A-Z]$/.test(S)) {
        console.log("Yes")
    }
    else {
        console.log("No")
    }
}

const stdin = require("fs").readFileSync("/dev/stdin", "utf8");
const input = stdin.trim().split("\n").map(i=>i.trim().split(/\s+/).map(i=>isNaN(i)?i:i-0))
main(input);
