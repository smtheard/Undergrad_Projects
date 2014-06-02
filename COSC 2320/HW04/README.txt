Stefan Theard PSID: 1208198

Time Complexity (hw04)

This program computes time complexity of either intersection or union of two given input files.

The way I came up with the constant I multiply big-oh notation of union/intersection is by plotting 15 data points (these
range from 1 to 10,000 in values of n) of the big-oh notation, and comparing that by plotting 15 data points of the 
program running the T(n) actual. I then took the average of the conversion from big-oh to T(n) actual and used this as my 
constant.

For union this came out to be ~5.00 and intersection it came out to be ~3.95

I'm not a great technical writer and this readme might not fully explain how I came up with my constants
if it does not, please contact me so I can meet with someone and explain it in person. I am very certain that it
is a valid way to compute them and it does hold properly through all of my tests, tightening the bound as n gets larger.
