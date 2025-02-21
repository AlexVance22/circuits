# Circuit Board Simulator

## File Type .chip
NOT and NAND are implemented as primitives, AND, OR, NOR, XOR are provided as example files available in `circlib/res/`.
Begin with dependencies (do not specify NOT or NAND), followed by chip ID and number of io ports:
```
import {deps:num} {dep:string}*
{name:string} {inputs:num} {outputs:num}
```
The following rows specify how the chip inputs are wired to the internals. Each row in order corresponds to an input on the overall chip and declares how many subchips that wire goes to, the name of the subchip and the port index on the subchip.
```
{splits:num} ({subchip:string} {port:num})+
```
The next line declares the number of subchips in the circuit `{subchips:num}` after which we begin declaring the subchips. You begin with the name of the subchip followed by its type. You can only declare a subchip of a type you have imported, NAND or NOT.
```
{name:string} {type:string}
```
What follows is a list of where the outputs of the subchip plug in to, analogous to how we did circuit inputs:
```
{splits:num} ({subchip:string} {port:num})+
```
In this case however, it is valid to specify `{splits:num} _ {port:num}` in reference to a circuit output port as opposed to a further subchip.

