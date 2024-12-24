object "HorseStoreYul" {
    code {
        //Contract Deployment
        datacopy(0,dataoffset("runtime"),datasize("runtime"))
        return(0,datasize("runtime"))
    }

    object "runtime"{
        code {
            //function dispatcher 
            switch selector()
             //updateHorseNumber
            case 0xcdfead2e {
                storeNumber(decodeAsUint(0))
                
            }
             //readNumberOfHorses
            case 0xe026c017 {
                
                returnUint(readNumber())
                
            }

            default {
                revert(0,0)
            }

            function storeNumber(value){
                sstore(0,value)
            }

            function selector() -> s {
                // let s:=calldataload(0)
                // s:=shr(0xe0,s)
                s := div(calldataload(0), 0x100000000000000000000000000000000000000000000000000000000)
               
            }

            function decodeAsUint(offset)-> v{
                let pos:= add(4,mul(offset,0x20))
                if lt(calldatasize(),add(pos,0x20)){
                    revert(0,0)
                }
                v:= calldataload(pos)
            }

            function readNumber() -> v{
                v:= sload(0)
            }

            function returnUint(value){
                mstore(0x00,value)
                return(0,0x20)
            }
        }
    }
}