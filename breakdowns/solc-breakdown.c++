// 0x6080604052348015600e575f5ffd5b5060a580601a5f395ff3fe6080604052348015600e575f5ffd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f5ffd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f5ffd5b503591905056fea26469706673582212205195f778937459724ab2b54de17a11b5567264079222a7fa75a99745b5ce83ad64736f6c634300081c0033


//Contract Creation Code   
PUSH1 0x80       //[0x80]
PUSH1 0x40       //[0x40,0x80]
MSTORE           //[]     //Memory 0x40->0x80

CALLVALUE        //[msg.value]
DUP1             //[msg.value,msg.value]
ISZERO           //[msg.value==0, msg.value]
PUSH1 0x0e       //[0x0e,msg.value==0, msg.value]
JUMPI            //[msg.value]
//if we dont jump 
PUSH0       //[0x0,msg.value]
PUSH0        //[0x0,0x0,msg.value]
REVERT       //[msg.value]
//if we jump
//jump dest if msg.value ==0
//stick the runtime code onchain 
JUMPDEST     //[msg.value]
POP          //[]
PUSH1 0xa5    //[0xa5]
DUP1          //[0xa5,0xa5]
PUSH1 0x1a     //[0x1a,0xa5,0xa5]
PUSH0          //[0x0,0x1a,0xa5,0xa5]
CODECOPY       //[0xa5]    Memory -> Runtime code
PUSH0           //[0x0,0xa5]
RETURN          //[]
INVALID          //[]


//Runtime Code

//free memory pointer 
PUSH1 0x80     //[0x80]
PUSH1 0x40      //[0x40,0x80]
MSTORE          //[]    //memory -> 0x40->0x80


 //in our contract there is no payable function so we  need to check for msg.value 
CALLVALUE        //[msg.value]
DUP1             //[msg.value,msg.value]
ISZERO           //[msg.value==0, msg.value]
PUSH1 0x0e        //[0x0e,msg.value==0, msg.value]
JUMPI             //[msg.value]
//if we dont jump
PUSH0          //[0x0,msg.value]
PUSH0         //[0x0,0x0,msg.value]
REVERT        //[msg.value]

//if we jump ie if msg.value==0
//check if there is enough calldata for function selector 
JUMPDEST        //[msg.value]
POP             //[]
PUSH1 0x04       //[0x04]
CALLDATASIZE     //[calldatasize,0x04]
LT               //[calldatasize<0x04]
PUSH1 0x30        //[0x30,calldatasize<0x04]
JUMPI             //[]
//matching the function selectors ie the function dispatcher
PUSH0             //[0x0]
CALLDATALOAD       //[calldata]
PUSH1 0xe0          //[0xe0,calldata]
SHR                 //[function selector]
DUP1                //[function selector,function selector]
PUSH4 0xcdfead2e    //[0xcdfead2e,function selector,function selector]
EQ                  //[function selector==0xcdfead2e, function selector]
PUSH1 0x34          //[0x34,function selector==0xcdfead2e, function selector]
JUMPI          //[function selector]

//if the function selector does not match then execute this code  ie the check for the readnumberofhorses function
DUP1            //[function selector,function selector]
PUSH4 0xe026c017  //[0xe026c017,function selector,function selector]
EQ                //[function selector==0xe026c017, function selector]
PUSH1 0x45     //[0x45,function selector==0xe026c017, function selector]
JUMPI           //[function selector]

//if the function selector is not correct then revert
JUMPDEST   //[]
PUSH0       //[0x0]
PUSH0       //[0x0,0x0]
REVERT       //[]

//jump destination for function selector 0xcdfead2e ie the updateHorseNumber function dest 1
JUMPDEST           //[function selector]
PUSH1 0x43         //[0x43,function selector]
PUSH1 0x3f         //[0x3f,0x43,function selector]
CALLDATASIZE        //[calldatasize,0x3f,0x43,function selector]
PUSH1 0x04          //[0x04,calldatasize,0x3f,0x43,function selector]
PUSH1 0x59         //[0x59,0x04,calldatasize,0x3f,0x43,function selector]
JUMP               //[0x04,calldatasize,0x3f,0x43,function selector]

//jump dest 4 for updateHorseNumber function
JUMPDEST  //[calldata,0x43,function selector]
PUSH0     //[0x0,calldata,0x43,function selector]
SSTORE    //[0x43,function selector]
JUMP       //[function selector]
//jump dest 5 for updateHorseNumber function

//jump dest 5 for updateHorseNumber function
JUMPDEST     //[function selector]
STOP        //[function selector]


//dest 1 for readNumberOfHorses function
JUMPDEST    //[function selector]
PUSH0       //[0x0,function selector]
SLOAD       //[numberofhorses,function selector]
PUSH1 0x40   //[0x40,numberofhorses,function selector]
MLOAD        //[0x80,numberofhorses,function selector]
SWAP1        //[numberofhorses,0x80,function selector]
DUP2        //[0x80,numberofhorses,0x80,function selector]
MSTORE      //[0x80,function selector] //memory 0x80->numberofhorses
PUSH1 0x20  //[0x20,0x80,function selector]
ADD         //[0xa0,function selector]
PUSH1 0x40   //[0x40,0xa0,function selector]
MLOAD        //[0x80,0xa0,function selector] 
DUP1         //[0x80,0x80,0xa0,function selector]
SWAP2        //[0xa0,0x80,0x80,function selector]
SUB           //[0x20,0x80,function selector]
SWAP1         //[0x80,0x20,function selector]
RETURN         //[function selector ]  //return numberofhorses ie ox20 bytes at memory location 0x80

//jump dest 2 for updateHorseNumber function
JUMPDEST        //[0x04,calldatasize,0x3f,0x43,function selector]
PUSH0         //[0x0,0x04,calldatasize,0x3f,0x43,function selector]
PUSH1 0x20  //[0x20,0x0,0x04,calldatasize,0x3f,0x43,function selector]
DUP3   //[0x04,0x20,0x0,0x04,calldatasize,0x3f,0x43,function selector]
DUP5 //[calldatasize,0x04,0x20,0x0,0x04,calldatasize,0x3f,0x43,function selector]
SUB  //[calldatasize-0x04,0x20,0x0,0x04,calldatasize,0x3f,0x43,function selector]
SLT  //[calldatasize-0x04<0x20,0x0,0x04,calldatasize,0x3f,0x43,function selector]
ISZERO  //[calldatasize-0x04<0x20 ==true,0x0,0x04,calldatasize,0x3f,0x43,function selector] ie [morecalldatathanselector,0x0,0x04,calldatasize,0x3f,0x43,function selector]
PUSH1 0x68 //[0x68,morecalldatathanselector,0x0,0x04,calldatasize,0x3f,0x43,function selector]
JUMPI   //[0x0,0x04,calldatasize,0x3f,0x43,function selector]
//we are going to jump to dest3 if there is more calldata than the function selector 

PUSH0  //[0x0,0x0,0x04,calldatasize,0x3f,0x43,function selector]
PUSH0 //[0x0,0x0,0x0,0x04,calldatasize,0x3f,0x43,function selector]
REVERT //[]

//jump dest 3 for updateHorseNumber function
JUMPDEST    //[0x0,0x04,calldatasize,0x3f,0x43,function selector]
POP         //[0x04,calldatasize,0x3f,0x43,function selector]
//since the offset is 4 the function selector will be ignored 
CALLDATALOAD   //[calldata,calldatasize,0x3f,0x43,function selector]
SWAP2        //[0x3f,calldatasize,calldata,0x43,function selector]
SWAP1      //[calldatasize,0x3f,calldata,0x43,function selector]
POP        //[0x3f,calldata,0x43,function selector]
JUMP    //[calldata,0x43,function selector]
//jump to dest4 for updateHorseNumber function

// MetaData 
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
MLOAD
SWAP6
INVALID
PUSH25 0x937459724ab2b54de17a11b5567264079222a7fa75a99745b5
INVALID
DUP4
INVALID
PUSH5 0x736f6c6343
STOP
ADDMOD
SHR
STOP
CALLER