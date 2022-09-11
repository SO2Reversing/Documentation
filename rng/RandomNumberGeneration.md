# Random Number Generation 

The RNG algorithm has 2 main parts, an array of 55 (0x37) generated numbers
and an index into that array.
Everytime a random number is used, the index into that array increments, when the index reaches the end of that array a new set of random numbers is generated.

information for RNG is stored in memory addresses:
0x8002b464 - 0x8002b544

The index is stored at 0x8002b464

The 55 Random numbers stored from
0x8002b468 - 0x8002b544
However the first value at 0x8002b468 is always 0, and is never used as the index starts at 1

Everytime a random number is computed the index increments, when the index reaches 56 a new set of numbers is calculated.

The 55 numbers are seeded with the seedRand() function, using a seed value of 0x4e421714.

There are many points in the code where a random number is requested but not used, its likely this is to increase the randomness of the generator.
As this will cause the generator to increment and refresh in a less predictable way.

## Random Number Usage

In the game there are two main ways the rng is used, with the functions randMod and randBig.

#### randMod - 800104d4
This function exists outside of the overlays at memory address - 800104d4

randMod will return a number between 0 and the argument passed to the function.

E.g.
randMod(10) - returns a number between 0 and 10
randMod(50) - returns a number between 0 and 50

#### randBig - 800103b4
This function exists outside of the overlays at memory address - 800103b4

randBig will return a random number between 0 and 32,767 (the max of a signed 32bit integer)

## Pseudo C Code

https://github.com/SO2Reversing/Documentation/blob/1e9c844068d6a50e0e00c01c34d0fa975fb8cc72/rng/seedRand.pseudo.c#L1-L22

https://github.com/SO2Reversing/Documentation/blob/1e9c844068d6a50e0e00c01c34d0fa975fb8cc72/rng/refresh_randnums.pseudo.c#L1-L29

https://github.com/SO2Reversing/Documentation/blob/1e9c844068d6a50e0e00c01c34d0fa975fb8cc72/rng/randnum.pseudo.c#L1-L10

https://github.com/SO2Reversing/Documentation/blob/1e9c844068d6a50e0e00c01c34d0fa975fb8cc72/rng/randMod.pseudo.c#L1-L17

https://github.com/SO2Reversing/Documentation/blob/1e9c844068d6a50e0e00c01c34d0fa975fb8cc72/rng/randBig.pseudo.c#L1-L8
