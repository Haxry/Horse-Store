// SPDX-License-Identifier: GPL-3.0-only
pragma solidity ^0.8.20;

interface IHorseStore {
    // 0xcdfead2e
    function updateHorseNumber(uint256 newNumberOfHorses) external ;

    // 0xe026c017
    function readNumberOfHorses() external view returns (uint256);
}