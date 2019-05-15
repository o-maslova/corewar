# Corewar
This is the team project of 3 people:

[Aleksandr Bulakh](https://github.com/lownhay) - team lead

[Anton Galaykovskiy](https://github.com/CharlesWin)

[Aleksandra Maslova](https://github.com/o-maslova)


## What is Corewar?
* Corewar is a very peculiar game. It’s about bringing “players” together around a “virtual machine”, which will load some “champions” who will fight against one another with the support of “processes”, with the objective being for these champions to stay “alive”.

* The processes are executed sequentially within the same virtual machine and memory space. They can therefore, among other things, write and rewrite on top of each others so to corrupt one another, force the others to execute instructions that can damage them.

* The game ends when all the processes are dead. The winner is the last player reported to be “alive”.

---
## This project is consist of:
### The assembler
This is the program that will compile champions and translate them from the language they wrote in (assembly language) into “Bytecode”. Bytecode is a machine code, which will be directly interpreted by the virtual machine.

### The virtual machine
It’s the “arena” in which your champions will be executed. It offers various functions, all of which will be useful for the battle of the champions.

### The champion
The bot which is wrote in Bytecode and it can write bits and pieces of Corewar ASM.

# To launch the program you should:
1. Compile the project - **make**.
2. Translate bot's assembly's code to bytecode - **./asm BotX.s** (or any other bot from *'champs'* directory.
3. **./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...**

> **-dump nbr_cycles**
at the end of nbr\_cycles of executions, dump the memory on the standard output and quit the game.

> **-n number**
sets the number of the next player. If non-existent, the player will have the next available number in the order of the parameters. The last player will have the first process in the order of execution.

*You can also use flag **-v** after executable file to visualize the battle.*

#### For example:
		./corewar -v -n 2 ./BotX.cor ./BotX.cor

### DON'T RUSH AT THE END OF THE GAME.
### PRESS 'SPACE' AND SEE THE MAGIC :)

![Alt-picture](https://github.com/o-maslova/corewar/blob/master/corewar.png "corewar")