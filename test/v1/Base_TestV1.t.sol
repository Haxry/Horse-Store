pragma solidity ^0.8.20;

import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
import {Test,console2} from "forge-std/Test.sol";


abstract contract Base_TestV1 is Test{

    HorseStore public horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    

    function testReadValue() public {
        uint256 value = horseStore.readNumberOfHorses();
        console2.log("Value: ", value);
        assertEq(value, 0, "Value should be 0");
    }

    function testWriteValue() public {
        horseStore.updateHorseNumber(777);
        uint256 value = horseStore.readNumberOfHorses();
        console2.log("Value: ", value);
        assertEq(value, 777, "Value should be 777");
    }
}